#Creator: Brayden Hollis
#Created: 06/26/2014

#Updated:
#By:

#This message is used to transmit which thrusters are on using limited amount of data

#These constants are used for bit mapping to determine which thrusters ought to be on
#Labels are done by in three parts XXX.  The first two characters deal with location of the thrust and the third deals with direct the thruster is facing. The first character is either 'R' (right) or 'L' (left), with directions from driver in craft.  The second character is F (forward) or R (rear) where forward is infrom of driver and rear is behind driver.  The third character is F (forward), S (side), or R (rear).

uint8 RFF=1
uint8 RFS=2
uint8 RRS=4
uint8 RRR=8
uint8 LRR=16
uint8 LRS=32
uint8 LFS=64
uint8 LFF=128

#seq is the variable to ensure most current commands are not supercede by previous commands that were delayed. 32 bits to ensure no overflow for even a 24 hour operation with a publish rate of 1000 hz
uint32 seq
#thrusters is the actual variable that is 1 byte (8 bits) and each bit corresponds to a separate thruster (as defined by the constants).
uint8 thrusters

#example of method for determining is RFF ought to be firing:
#
# if (RFF & thrusters)
#    rff_thruster = ON
# else
#    rff_thruster = OFF
#
# (& is bitwise AND logic operator)

#example of method for assigning multiple thrusters firing at once.
#this is the example for forward motion
#
# thrusters = 0
# thrusters = RRR | LRR
#
# (| is bitwise OR logic operator)
