flexcraft
=========

Control software for the FlexCraft Simulator (FCS), a robotic platform located in the Flight Robotics Laboratory at NASA's Marshall Space Flight Center.

<h3>About</h3>
This repository contains the code base for the FlexCraft Simulator (FCS) as designed by the FlexCraft Robotics Academy Plus Team (initially).

FCS is a physical test bed for development of the FlexCraft, a concept robotics space vehicle for replacing Extra-Vehicular Activities (EVAs). As a test bed for development, FCS is designed to be modular for swapping pieces to test designs. Particularly the system is designed for testing human interfaces (controllers), manipulators, and control software, all of which interface with software. Overall the system is designed to test teh capability of teleoperation versus driver performance for EVA activites. Thus while this repository maintains code for the system, the larger importance of this repository is the software framework and architecture in which all test designs out to follow to maintain modularity.

The software is built upon the Robot Operating System (ROS) as ROS provides communication and modularity capability and provides some pre-existing software.

<h3>Install/Setup</h3>
After cloning into your local filesystem, here are steps to help you get going:
```
#initialize the workspace
cd path/to/flexcraft/src
catkin_init_workspace

#build the project for the first time
cd ../
catkin_make

#if things seem to not be working
source flexcraft/devel/setup.bash
```

<h3>Included</h3>
List of folders and files in this folder and lists of important subfolders/files

- devel...........[folder] ROS generated folder
- noncode.........[folder] contains related files that are not code
- sketchbook......[folder] contains all arduino code for low level interfacing
	- Actuators.........[folder] contains all low level (arduino) code for actuator control
	- Human_Interfaces..[folder] contains all low level (arduino) code for human interfaces (both input and output)
	- Sensors...........[folder] contains all low level (arduino) code for sensor reading
	- libraries.........[folder] contains all non-default libraries used in arduino code
- src.............[folder] contains all source code, the main part of the repository
	- autonomy..........[folder] contains all source code modules for autonomous movement
	- control_sw........[folder] contains all source code modules for control software
	- fcs_launch........[folder] contains all launch files that combine cross category modules, thus containing files to start system
	- flexcraft_gazebo..[folder] contains all parts required strickly for gazebo simulation of system
	- flexcraft_msgs....[folder] contains all custom ROS message definitions for flexcraft
	- input_hi..........[folder] contains all source code modules for human interfaces input systems
	- manipulator.......[folder] contains all source code modules for manipulators
	- output_hi.........[folder] contains all source code modules for human interfaces output systems
	- sensors...........[folder] contains all source code modules for sensors and sensor processing
- startup.........[folder] contains desktop launch systems
- README.md.......[text file] this file
- setup.bash......[bash script] automated install script - installs ROS and entire system

<h4>Note on thruster naming conventions:</h4>
side (Left/Right) - side (front/rear) - direction it makes the craft go (backwards/forwards/right/left)
```
 1 ^ -------------- ^ 3
 2  <              > 4
     \            /
      \          /
       \        /
        \      /
     5 < \    / > 7
       6 v\  /v 8
           \/
```
<ol>
<li>LFB</li>
<li>LFR</li>
<li>RFB</li>
<li>RFL</li>
<li>LRR</li>
<li>LRF</li>
<li>RRL</li>
<li>RRF</li>
</ol>
