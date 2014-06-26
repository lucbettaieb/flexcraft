#Creator: Brayden Hollis
#Created: 06/26/2014

#Updated:
#By:

#This message is used to transmit which thrusters are on using limited amount of data

#These constants are used for bit mapping to determine which thrusters ought to be on
#Labels are done by in three parts XXX.  The first two characters deal with location of the thrust and the third deals with direct the thruster is facing. The first character is either 'R' (right) or 'L' (left), with directions from driver in craft.  The second character is F (forward) or R (rear) where forward is infrom of driver and rear is behind driver.  The third character is F (forward), S (side), or R (rear).

char RFF=1
char RFS=2
char RRS=4
char RRR=8
char LRR=16
char LRS=32
char LFS=64
char LFF=128

#thrusters is the actual variable that is 1 byte (8 bits) and each bit corresponds to a separate thruster (as defined by the constants).
char thrusters

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
