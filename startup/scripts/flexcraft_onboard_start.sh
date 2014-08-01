#!/bin/bash

#This file launches the FlexCraft onboard code, allowing for the user to use a mouse instead of requring a keyboard.

source /opt/ros/hydro/setup.bash
source ~/catkin_ws/src/flexcraft/devel/setup.bash

roslaunch fcs_launch start_all.launch
