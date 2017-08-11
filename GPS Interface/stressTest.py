from geopy.distance import great_circle
from datetime import datetime
import mysql.connector
from mysql.connector import errorcode
import random
import time

cnx = mysql.connector.connect(user='db_admin', password='capstone',
                              host='capstone-bikes.cphpxguj45gw.us-east-1.rds.amazonaws.com',
                              database='Capstone_Bike_Shop')
cursor = cnx.cursor()
print("Connected to database...")


'''
    GETS DISTANCE GIVEN TWO PAIRS OF LAT-LON POINTS
    HELPS FOR INCREMENTING THE DISTANCE
'''
def getDistance(starting_point, ending_point):
    distance = great_circle(starting_point, ending_point).kilometers
    return distance  # returns distance between two points, helps increment total distance


'''
    RUNS MYSQL QUERIES GIVEN THE PROPER INPUTS
'''
def updateToTable(bikeID, ending_point, datetime, distance):
    currentLat = ending_point[0]
    currentLon = ending_point[1]
    cursor.execute("INSERT INTO Locations (BikeId, Latitude, Longitude, Timestamp) VALUES (%s, %s, %s, %s) ",
                   (bikeID, currentLat, currentLon, datetime,))
    cnx.commit()
    cursor.execute("UPDATE Capstone_Bike_Shop.Master SET Distance = %s WHERE BikeId = %s ", (distance,bikeID))
    cnx.commit()

'''
    GIVES RANDOM COORDINATES
'''
def simulateRandomCoordinates():
    lat = random.uniform(-89.9, 89.9)
    lon = random.uniform(-179.9, 179.9)
    return (lat, lon)

'''
    SIMULATES DATA
'''
def simulateData(bikeID):
    starting_point = simulateRandomCoordinates()
    ending_point = simulateRandomCoordinates()
    i = datetime.now()
    distance = getDistance(starting_point, ending_point) # distance not running distance
    dateTimeStamp = i.strftime('%Y-%m-%d %H:%M:%S')
    updateToTable(bikeID, ending_point, dateTimeStamp, distance)


def main():
    for x in range(1, 100): # Random range for number of instances for stress testing server
        for y in range(3, 102): # the bikes we want to test for
            simulateData(y)
        print("Sleeping... Just finished simulation number " + str(x))
        time.sleep(25)


main()
cursor.close()
cnx.close()
