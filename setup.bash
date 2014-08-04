#!/bin/bash

#this file fully sets up flexcraft code on an ubuntu 12.04 machine
#it install ros hydro and then installs the code

#installs ros hydro following the instructions from wiki.ros.org/hydro/Installation/Ubuntu
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu precise main" > /etc/apt/sources.list.d/ros-latest.list'

wget https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -O - | sudo apt-key add -

sudo apt-get update

sudo apt-get -y install ros-hydro-desktop-full

sudo rosdep init
rosdep update

echo "source /opt/ros/hydro/setup.bash" >> ~/.bashrc
source ~/.bashrc

#set up flexcraft code (assumes code already pulled as this file is in repository)
catkin_make

#sources flexcraft file so ros knows of this code
here=$PWD
echo "source $here/devel/setup.bash" >> ~/.bashrc

#makes this terminal reset
source ~/.bashrc

#install some file dependencies
sudo apt-get install -y ros-hydro-camera-info-manager-py
rosdep install spacenav_node

# remakes the system so it is good to go.  -j1 does it sequentially so not dependency errors
catkin_make -j1

# create desktop files
./create_desktop.bash
