import serial
import pynmea3


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
##			       4 = Real Time Kinematic
##			       5 = Float RTK
##                               6 = estimated (dead reckoning) (2.3 feature)
##			       7 = Manual input mode
##			       8 = Simulation mode
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




GGApat = " | Lat: {0:s} {1:s} | Lon: {2:s} {3:s} | Alt: {4:.4f} {5:s}"

def parseGPS(rawGpsData):
    if rawGpsData.find('GGA') > 0:
        # msg is a Model that stores the parsed gps data
        msg = pynmea3.parse(rawGpsData) # parse raw gps coordinates
        #msg = pynmea3.parse('$GNGGA,140816.00,,,,,,,,,,,,')
        if msg != "":
            print('Time: %s' %(msg.timestamp) + GGApat.format(msg.lat, msg.lat_dir, msg.lon, msg.lon_dir, msg.altitude, msg.altitude_units))
        else: print('error\n')


serialPort = serial.Serial("/dev/ttyAMA0", 9600, timeout=0.5)

while True:
    
    rawGps = serialPort.readline()
    parseGPS(rawGps)

    
