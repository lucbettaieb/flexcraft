mr_teleoperator
===============

This is an open source package, used here to control the FCS
<br>
See: http://wiki.ros.org/mr_teleoperator/Tutorials/Getting%20Started

A collection  of modules that allow one to utilizing a joystick (Xbox, PS) or the mouse or keyboard 
to control the FCS.

This collection includes: 
<ul> 
  <li>
    Rqt plugin  for selecting and controling a specific robot.
  </li>
   <li>
   A node that publishes a geometry_msgs/Twist message type. This is translated by
   ui_translator.cpp in the control_sw package
   </li>
</ul> 


<strong>Example:</strong>
```
roslaunch mr_tools teleoperator.launch
```
