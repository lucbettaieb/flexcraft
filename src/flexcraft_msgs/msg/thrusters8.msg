#Creator: Brayden Hollis
#Created: 06/26/2014

#Updated:
#By:

#This message is used to transmit which thrusters are on using limited amount of data

#These constants are used for bit mapping to determine which thrusters ought to be on
#Labels are done by in three parts XXX.  The first two characters deal with location of the thrust and the third deals with the direction the thruster moves the craft. The first character is either 'R' (right) or 'L' (left), with directions from driver in craft.  The second character is F (front) or R (rear) where front is infront of driver and back is behind the driver.  The third character is F (forward), R (right), L (left) or B (backward).

uint8 RFB=1
uint8 RFL=2
uint8 RRL=4
uint8 RRF=8
uint8 LRF=16
uint8 LRR=32
uint8 LFR=64
uint8 LFB=128

#seq is the variable to ensure most current commands are not supercede by previous commands that were delayed. 32 bits to ensure no overflow for even a 24 hour operation with a publish rate of 1000 hz
uint32 seq
#thrusters is the actual variable that is 1 byte (8 bits) and each bit corresponds to a separate thruster (as defined by the constants).
uint8 thrusters

#example of method for determining is RFF ought to be firing:
#
# if (RFB & thrusters)
#    rfb_thruster = ON
# else
#    rfb_thruster = OFF
#
# (& is bitwise AND logic operator)

#example of method for assigning multiple thrusters firing at once.
#this is the example for forward motion
#
# thrusters = 0
# thrusters = RRB | LRB
#
# (| is bitwise OR logic operator)
