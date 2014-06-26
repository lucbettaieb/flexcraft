#Creator: Brayden Hollis
#Created: 06/26/2014

#Updated:
#By:

#This message delivers the change in velocity for planar systems.  Typically such changes would have units, but in our current application, units our unknown, and implemenation are not in current plans. X is forward and Y is to the drivers left (follows from right hand rule with z as up).

#linear
float32 deltaVX
float32 deltaVY

#angular
float32 alpha

#current implemenation will set deltaVX as +1.0 for forward and -1.0 for backward and deltaVY as +1.0 for sideways motion to driver left and -1.0 for sideways motion to driver's right.  alpha as +1.0 is turning towards the left (counter clockwise) and -1.0 is turning towards the right (clockwise) as determined from right hand rule.

