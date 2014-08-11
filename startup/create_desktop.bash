#!/bin/bash

# this script creates the desktop launchers and the corresponding scripts
# it has two input variables
#   The first variable is which launchers to put on the desktop. It currently understands the inputs "all" "teleop" and "onboard" corresponding to putting all launchers, the teleoperation launcher only, and the onboard launcher only on the desktop, respectively. Default is "all".
#   The second variable is the directly location of flexcraft folder.  It is defaulted as pwd (this location) as this file likely will be ran from the flexcraft folder.

# this file is expected to be ran from the flexcraft folder.
flexcraft=${2:-$PWD} # if this file is not ran from flexcraft folder, the second variable should be the path of flexcraft folder

which=${1:-"all"}


# create onboard launcher
# create the actual desktop file
echo "[Desktop Entry]
Version=1.0
Name=FCS Onboard
GenericName=Application
#This script has two inputs spacenav and keyboard (default is false)
Exec=$flexcraft/startup/scripts/flexcraft_onboard_startup.bash false false
Terminal=true
Icon=$flexcraft/startup/icons/flexyside.png
Type=Application
Comment=Currently a test of desktop files, but launches FlexCraft Software" > onboard.desktop
# make executable
chmod +x onboard.desktop
# move to startup desktop folder
cp onboard.desktop $flexcraft/startup/desktops/FlexCraft.desktop

# place on desktop
if [ "$which" == "all" ] || [ "$which" == "onboard" ]
then
	cp onboard.desktop ~/Desktop/FlexCraft.desktop
fi

# remove temp file
rm onboard.desktop


# create the onboard startup script
echo "#!/bin/bash

#This file launches the FlexCraft onboard code, allowing for the user to use a mouse instead of requring a keyboard.

#These variables allows input to be done in desktop application.  First variable is for launching human input device spacenav(3d mouse) and second is keyboard. 
spacenav=false
keyboard=false
spacenav=\$1
keyboard=\$2

#These setup ros as not using bash file
source /opt/ros/hydro/setup.bash
source $flexcraft/devel/setup.bash

#This actually launches code
roslaunch fcs_launch start_all.launch spacenav:=\$spacenav keyboard:=\$keyboard" > onboard

# make executable
chmod +x onboard

# move to script folder
mv onboard $flexcraft/startup/scripts/flexcraft_onboard_startup.bash





# create the actual desktop file
echo "[Desktop Entry]
Version=1.0
Name=FCS Teleop
GenericName=Application
#This script has two inputs spacenav and keyboard (default is false)
Exec=$flexcraft/startup/scripts/flexcraft_teleop_startup.bash false false
Terminal=true
Icon=$flexcraft/startup/icons/flexyside.png
Type=Application
Comment=Currently a test of desktop files, but launches FlexCraft Software" > teleop.desktop

# make executable
chmod +x teleop.desktop

# move to start desktop folder
cp teleop.desktop $flexcraft/startup/desktops/FlexCraftTeleop.desktop

# move to desktop
if [ "$which" == "all" ] || [ "$which" == "teleop" ]
then
	cp teleop.desktop ~/Desktop/FlexCraftTeleop.desktop
fi

# remove temp
rm teleop.desktop


# create the teleoperation startup script
echo "#!/bin/bash

#This file launches the FlexCraft onboard code, allowing for the user to use a mouse instead of requring a keyboard.

#These variables allows input to be done in desktop application.  First variable is for launching human input device spacenav(3d mouse) and second is keyboard. 
spacenav=false
keyboard=false
spacenav=\$1
keyboard=\$2

#This sets up the ros environment
source /opt/ros/hydro/setup.bash
source $flexcraft/devel/setup.bash

#This sets the other computer as master
export ROS_MASTER_URI=http://chandra:11311

#config this computers ros variables for communication
ip=\$(ifconfig | grep 'inet addr:'| grep -v '127.0.0.1' | cut -d: -f2 | cut -dB -f1)
export ROS_IP=\$ip
export ROS_HOSTNAME=\$ip

#This actually launches code
roslaunch fcs_launch start_teleop.launch spacenav:=\$spacenav keyboard:=\$keyboard" > teleop

# make executable
chmod +x teleop

# move to scripts folder
mv teleop $flexcraft/startup/scripts/flexcraft_teleop_startup.bash
