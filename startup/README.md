startup
================

Contains simple ways to start code

<h3>About</h3>
As not everyone is familiar with ROS or even with command line, this folder contains a few simple ways to start up the code.  It contains script files that set appropiate ROS parameters and starts the code.  It also contains desktop launchers that run this scripts eliminating the need for commandline all together.

<h3>Include</h3>
- desktops...............[folder] contains the desktop launchers for non-commandline users
- icons..................[folder] contains the icons used by the desktop launchers
- scripts................[folder] contains the startup scripts, including the ones used by the desktop launchers
- create_desktop.bash....[bash script] script for creating the startup scripts and desktop launchers as they depend on directory locations and thus change with each computer
- README.md..............[text file] this file

<h3>IMPORTANT NOTES</h3>
- create_desktop.bash is designed to be in parent folder (flexcraft directory).
- create_desktop.bash takes two inputs
	- which desktop launchers to place on desktop (all, onboard, teleop)
	- path to flexcraft directory for when not run from flexcraft directory
- the onboard launchers and scripts will only work on a machine whose network is called chandra, unless the scripts are modified. The desktop launchers do not need to be modified.
- the teleop launchers and scripts will only connect to a machine whose ip is masked as chandra, unless the scripts are modified. The desktop launchers do not need to be modified.
