"""Authors: Tasdique Chowdhury, Liam Guedez, Vlad Shostak

  This program gets readings from a GPS device, which is attached to a bicycle,
  displays the position of the rider every second, and calculates the distance
  traveled.
"""
from geopy.distance import great_circle
import serial
import pynmea2
from datetime import datetime
import mysql.connector
from mysql.connector import errorcode
import time

print("Executed!")
time.sleep(60)

cnx = mysql.connector.connect(user='db_admin', password ='capstone',
                              host='capstone-bikes.cphpxguj45gw.us-east-1.rds.amazonaws.com',
                              database='Capstone_Bike_Shop')
cursor = cnx.cursor()
print("Connected to database...")

bikeID = 1
GGApat = " | Lat: {0:s} {1:s} | Lon: {2:s} {3:s} | Alt: {4:.4f} {5:s}"

'''
    PARSE THE GPS AND OBTAINED THE DATA OF A SINGLE MESSAGE FROM THE GPS
'''
def parseGPS(rawGpsData):
    
    msg_ = ""

    if rawGpsData.find('GGA') > 0:
        # msg is a Model that stores the parsed gps data
        msg_ = pynmea3.parse(rawGpsData) # parse raw gps coordinates
        #msg = pynmea3.parse('$GNGGA,140816.00,,,,,,,,,,,,')
        
    if msg_ == "":
        return "error\n"
    else:
        return msg_
        
'''
    RETURNS THE LATITUDE AND LONGITUDE, WHICH IS NEEDED TO CALCULATE THE DISTANCE
'''
def getCurrentPosition(msg):

    latLonAltString = str(GGApat.format(msg.lat, msg.lat_dir, msg.lon, msg.lon_dir, msg.altitude, msg.altitude_units))

    latLonAltList = latLonAltString.split('|')

    latitude = latLonAltList[1]
    longitude = latLonAltList[2]

    latitudeList = latitude.split(' ')
    longitudeList = longitude.split(' ')

    latitude = latitudeList[2]
    longitude = longitudeList[2]

    # makes the degrees, minutes, and seconds, into a single degree float
    latitude = float(latitude[:2]) + float(latitude[2:9])/60
    longitude = float(longitude[:3]) + float(longitude[3:10])/60

    # gives the the lat and lon as a pair
    latLon = (latitude, longitude)
    return latLon 
    
'''
    PRINTS THE GPS COORDINATES AND THE DISTANCE TRAVELED BY THE RIDER
'''
def printGPSdata(ending_point, dateTimeStamp, totalDistance):
    datetime = 'Date-Time: %s' %dateTimeStamp
    print (datetime + " | Lat: %s" %str(ending_point[0]) + " | Lon: %s" %str(ending_point[1]*(-1)))
    print("Distance Traveled: " + totalDistance + " kilometers\n")

'''
    GETS DISTANCE GIVEN TWO PAIRS OF LAT-LON POINTS
    HELPS FOR INCREMENTING THE DISTANCE
'''
def getDistance(starting_point, ending_point):
    distance = great_circle(starting_point, ending_point).kilometers
    return distance #returns distance between two points, helps increment total distance

'''
    RUNS MYSQL QUERIES GIVEN THE PROPER INPUTS
'''
def updateToTable(bikeID, ending_point, datetime, totalDistance):
    currentLat = ending_point[0]
    currentLon = ending_point[1] *(-1)
    cursor.execute("INSERT INTO Locations (BikeId, Latitude, Longitude, Timestamp) VALUES (%s, %s, %s, %s) ", (bikeID,currentLat,currentLon,datetime,))
    cnx.commit()
    cursor.execute("UPDATE Capstone_Bike_Shop.Master SET Distance = %s WHERE BikeId = 1 ", (totalDistance,))
    cnx.commit()
    
    
def main():

    starting_point = ""
    ending_point = ""
    serialPort = serial.Serial("/dev/ttyAMA0", 9600, timeout=0.5)

    totalDistance = 0.0

     # obtains running distance from MySQL server
    cursor.execute("SELECT Distance FROM Master WHERE BikeId = %s ", (bikeID,))

    #TUPLE: (u'0.0',)
    temp = cursor.fetchone()
    temp = str(temp)
    #rint(temp)

    formattedDist = temp[1:(len(temp) - 2)]
    #print(formattedDist)
    formattedDist = float(formattedDist)
    totalDistance += formattedDist
    
    print(totalDistance)
    initialDT = datetime.now()
   
    
    while True:
        rawGps = serialPort.readline()

       
        
        msg = parseGPS(rawGps)
        nowDT = datetime.now()

        # print ("initial - now = " + str( (int(initialSeconds) - int(nowSeconds) ) ) )

        if ((nowDT - initialDT).seconds % 25 == 0):
            
            if msg == "error\n":
                print("Errors galore...")
                
            else:
                i = datetime.now()
                dateTimeStamp = i.strftime('%Y-%m-%d %H:%M:%S')
                if (starting_point == ""):
                    starting_point = getCurrentPosition(msg)
                    ending_point = starting_point
                elif (starting_point != ""):
                    starting_point = ending_point
                    ending_point = getCurrentPosition(msg)
                    totalDistance += getDistance(starting_point, ending_point)
                printGPSdata(ending_point, dateTimeStamp, str(totalDistance))
                updateToTable(bikeID, ending_point, dateTimeStamp, totalDistance)

main()
cursor.close()
cnx.close()

