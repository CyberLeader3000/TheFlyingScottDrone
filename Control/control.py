#!/usr/bin/env python3
# -*- coding: utf-8 -*-

###################################################################################
# Drone Control         Copyright 2020 Douglas Wheeler
#
# This is copyrighted under the BSD new license, the full text can be found here:
# https://opensource.org/licenses/BSD-3-Clause
#
# Author: Douglas Wheeler
# Description: Provides programmatic control for the drone for the
# "TheFlyingScottDrone" NXP Hovergames team. The drone is designed to support
# firefighters doing search and rescue to evacuate people from the path of wild
# fires. Utilises MavLink via the MavSDK-Python library. Reqires >= Python 3.6
#
# Date: 2020 Jan 12
###################################################################################

# Built-in imports
import asyncio
import math

# Other libraries
from mavsdk import System, MissionItem


###################################################################################
# The program's main function
###################################################################################
async def main():

    # Create a drone object and connect
    drone = System()
    await drone.connect(system_address="udp://:14540") # Default port for PX4 SITL simulation
    print("Waiting for drone to connect")
    async for state in drone.core.connection_state(): # Check for connection
        if state.is_connected:
            print("Connected to drone with UUID: " + str({state.uuid}))
            break

    # Calculates points for the drone to visit in its search
    mission = perimeter(47.398041, 8.544287, 80) # Outer rectangle
    mission.extend(perimeter(47.398041, 8.544287, 40)[1:]) # Inner rectangle

    # Starts the mission
    await start_mission_RTL(drone, mission)

    # Provides feedbcak about the drone's mission progress
    async for mission_progress in drone.mission.mission_progress():
        if mission_progress.current_item_index == 1:
            print("Reached search area")
        if mission_progress.current_item_index == mission_progress.mission_count:
            print("Search completed, returning to launch")

    return


###################################################################################
# Given a search area (centre = [lat, lon] and width = [radius*2]), position
# information for the corners of the search area will be calculated, ready to be
# uploaded to the drone.
###################################################################################
def perimeter(lat, lon, radius):
    
    x, y, z = lat_lon_to_coords(lat, lon)
    radius /= 1000 # Converts radius from metres to kilometres
    alt = 25 # Altitude of drone
    corners = []

    # Go to centre of search area
    corners.append(MissionItem(lat, lon, alt, 0, True, float('nan'), float('nan'), MissionItem.CameraAction.NONE, float('nan'), float('nan')))

    # Calculate latitude and longitude of corner 1
    lat, lon = coords_to_lat_lon(x, y+radius, z+radius)
    corners.append(MissionItem(lat, lon, alt, 0, True, float('nan'), float('nan'), MissionItem.CameraAction.NONE, float('nan'), float('nan')))

    # Calculate latitude and longitude of corner 2
    lat, lon = coords_to_lat_lon(x, y+radius, z-radius)
    corners.append(MissionItem(lat, lon, alt, 0, True, float('nan'), float('nan'), MissionItem.CameraAction.NONE, float('nan'), float('nan')))

    # Calculate latitude and longitude of corner 3
    lat, lon = coords_to_lat_lon(x, y-radius, z-radius)
    corners.append(MissionItem(lat, lon, alt, 0, True, float('nan'), float('nan'), MissionItem.CameraAction.NONE, float('nan'), float('nan')))

    # Calculate latitude and longitude of corner 4
    lat, lon = coords_to_lat_lon(x, y-radius, z+radius)
    corners.append(MissionItem(lat, lon, alt, 0, True, float('nan'), float('nan'), MissionItem.CameraAction.NONE, float('nan'), float('nan')))

    # Complete search pattern by returning to corner 1
    corners.append(corners[1])

    return corners


###################################################################################
# Given a drone object (drone) and a list of points (mission), the drone will visit
# these these points then return to the launch position.
###################################################################################
async def start_mission_RTL(drone, mission):
    
    await drone.mission.set_return_to_launch_after_mission(True)

    print("Uploading mission")
    await drone.mission.upload_mission(mission)

    print("Arming")
    await drone.action.arm()

    print("Starting mission")
    await drone.mission.start_mission()


###################################################################################
# Converts latitude and longitude into manipulatable x,y,z coordinates
###################################################################################
def lat_lon_to_coords(lat, lon):
    radius_of_earth = 6371
    rad_lat = math.radians(lat)
    rad_lon = math.radians(lon)
    x = radius_of_earth * math.cos(rad_lat) * math.cos(rad_lon)
    y = radius_of_earth * math.cos(rad_lat) * math.sin(rad_lon)
    z = radius_of_earth * math.sin(rad_lat)
    return x, y, z


###################################################################################
# Converts x,y,z coordinates into latitude and longitude which can be interpreted
# by the drone
###################################################################################
def coords_to_lat_lon(x, y, z):
    radius_of_earth = 6371
    rad_lat = math.asin(z/radius_of_earth)
    rad_lon = math.atan2(y, x)
    lat = math.degrees(rad_lat)
    lon = math.degrees(rad_lon)
    return lat, lon

###################################################################################
# Set up asyncio event loop
###################################################################################
if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
