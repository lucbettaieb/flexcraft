#!/bin/bash

#This file launches the FlexCraft onboard code, allowing for the user to use a mouse instead of requring a keyboard.

#These variables allows input to be done in desktop application.  First variable is for launching human input device spacenav(3d mouse) and second is keyboard. 
spacenav=false
keyboard=false
spacenav=$1
keyboard=$2

#This sets up the ros environment
source /opt/ros/hydro/setup.bash
source ~/catkin_ws/src/flexcraft/devel/setup.bash

#This sets the other computer as master
export ROS_MASTER_URI=http://chandra:11311

#This actually launches code
roslaunch fcs_launch start_teleop.launch spacenav:=$spacenav keyboard:=$keyboard
