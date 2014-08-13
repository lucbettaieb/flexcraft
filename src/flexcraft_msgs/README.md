Creator: Brayden Hollis
Created: 06/26/2014

This package is designed to contain all the custom message definitions for the flexcraft control code.  The logic behind this is packages in the code can all depend on this single package for message definitions instead of being dependent on each other.  Additionally this reduces a source of circular dependency.

<h3>Adding additional message definitions</h3>
1. Create message definition in msg directory
2. Edit CMakeLists.txt file by placing your new message file name in add_message_files:
```
#Example of what this part will look like
add_message_files(
	FILES
	deltaV2D.msg
	thrusters8.msg
	yourmsg.msg
)
```
3. Save it.
4. go to flexcraft directory
5. type catkin_make - this will generate the message header file
