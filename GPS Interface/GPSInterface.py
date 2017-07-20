"""Authors: Tasdique Chowdhury, Liam Guedez, Vlad Shostak

  This program gets readings from a GPS device, which is attached to a bicycle,
  displays the position of the rider every second, and calculates the distance
  traveled.
"""

# Specification standard from: The National Marine Electronics Association (NMEA)

# GGA Fix information
# essential fix data which provides 3D location and accuracy data.

##Where:
##     GGA          Global Positioning System Fix Data
##     123519       Fix taken at 12:35:19 UTC
##     4807.038,N   Latitude 48 deg 07.038' N
##     01131.000,E  Longitude 11 deg 31.000' E
##     1            Fix quality: 0 = invalid
##                               1 = GPS fix (SPS)
##                               2 = DGPS fix
##                               3 = PPS fix
##              4 = Real Time Kinematic
##              5 = Float RTK
##                               6 = estimated (dead reckoning) (2.3 feature)
##              7 = Manual input mode
##              8 = Simulation mode
##     08           Number of satellites being tracked
##     0.9          Horizontal dilution of position
##     545.4,M      Altitude, Meters, above mean sea level
##     46.9,M       Height of geoid (mean sea level) above WGS84
##                      ellipsoid
##     (empty field) time in seconds since last DGPS update
##     (empty field) DGPS station ID number
##     *47          the checksum data, always begins with *

##If the height of geoid is missing then the altitude should be suspect. Some non-standard implementations
##report altitude with respect to the ellipsoid rather than geoid altitude. Some units do not report
##negative altitudes at all. This is the only sentence that reports altitude.

from geopy.distance import great_circle
import serial
import pynmea3

def parseGPS(rawGpsData):
  """ Args:
          rawGpsData: A string received from the GPS reader.

      Returns:
          If a valid string is passed,
              returns a string containing time, latitude, longitude, and altitude.
          Else,
              returns the string "error\n".
  """
  msg_ = ""

  if rawGpsData.find('GGA') > 0:
      # msg is a Model that stores the parsed gps data
      msg_ = pynmea3.parse(rawGpsData)  # parse raw gps coordinates
      # msg = pynmea3.parse('$GNGGA,140816.00,,,,,,,,,,,,')

  if msg_ == "":
      return "error\n"
  else:
      return msg_

def getCurrentPosition(msg):
  """
  Args:
      msg: A string containing time, latitude, longitude, and altitude.

  Returns:
      A pair containing the latitude and the longitude as doubles.
      This pair is used later to calculate the distance traveled by the rider.
  """
  GGApat = " | Lat: {0:s} {1:s} | Lon: {2:s} {3:s} | Alt: {4:.4f} {5:s}"

  #The format function edits the GGApat string
  #It plugs in latitude as argument 0, longitude as arguments 2 and 3, and altitude as arguments 4 and 5
  latLonAltString = str(GGApat.format(msg.lat, msg.lat_dir, msg.lon, msg.lon_dir, msg.altitude, msg.altitude_units))

  latLonAltList = latLonAltString.split('|')

  latitude = latLonAltList[1]
  longitude = latLonAltList[2]

  latitudeList = latitude.split(' ')
  longitudeList = longitude.split(' ')

  latitude = latitudeList[2]
  longitude = longitudeList[2]

  latLon = (float(latitude), float(longitude))

  return latLon

def editString(gpsData):
  """Helper function for the printGPSdata and the getCurrentPosition functions
      Args:
          gpsData: A semi-legible string containing the latitude, longitude,
          and altitude.

      Returns:
          A more legible string.
  """
  # separate altitude off the string
  removedBarsList = gpsData.split("|")
  altitude = "|" + removedBarsList[3]
  latLon = gpsData[:-len(altitude)]

  # add 'd' for degrees and 'm' for minutes
  count = 0
  for x in latLon:

      if x == '.':
          latLon = latLon[:count - 2] + " d, " + latLon[count - 2:count + 6] + "m, " + latLon[count + 6:]
          count = count + 7
      count = count + 1

  # remove any unnecessary leftmost zeroes
  count = 0
  for x in latLon:
      zero = latLon[count + 2:count + 3]
      if x == ":" and zero == "0":
          latLon = latLon[:count + 2] + latLon[count + 3:]
      count = count + 1

  # reattach altitude and return the edited string
  editedString = latLon + altitude
  return editedString

def printGPSdata(msg, starting_point, ending_point):
"""Prints the GPS coordinates and the distance traveled by the rider"""
  time = 'Time: %s' % (msg.timestamp)
  latLonAlt = GGApat.format(msg.lat, msg.lat_dir, msg.lon, msg.lon_dir, msg.altitude, msg.altitude_units)
  print(time + editString(latLonAlt))
  # print('Time: %s' %(msg.timestamp) + GGApat.format(msg.lat, msg.lat_dir, msg.lon, msg.lon_dir, msg.altitude, msg.altitude_units))

  #great_circle formula takes in two rider positions as two pairs of
  #latitude and longitude and calculates the distance between these two points
  distance = great_circle(starting_point, ending_point).kilometers
  distance = str(distance)
  print("distance traveled: " + distance + " kilometers\n")

def main():
  starting_point = ""
  ending_point = ""
  serialPort = serial.Serial("/dev/ttyAMA0", 9600, timeout=0.5)

  while True:
  #gets the start position of the rider's trip.
  #loops until a valid "GGA" string is read.
      rawGps = serialPort.readline()
     msg = parseGPS(rawGps)

      if msg == "error\n":
          pass  # print(msg)
      else:
          starting_point = getCurrentPosition(msg)
          ending_point = starting_point
          printGPSdata(msg, starting_point, ending_point)
          break

  while True:
  #reads the rider's position every second.
  #loops until the user terminates the program.
      rawGps = serialPort.readline()
      msg = parseGPS(rawGps)

      if msg == "error\n":
          pass  # print(msg)
      else:
          ending_point = getCurrentPosition(msg)
          printGPSdata(msg, starting_point, ending_point)

main()


