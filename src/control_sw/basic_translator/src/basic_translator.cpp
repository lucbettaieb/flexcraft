#include "ros/ros.h"
#include "flexcraft_msgs/deltaV2D.h"
#include "flexcraft_msgs/thrusters8.h"

// definitions of the bits for each thruster (the first value is which side (left or right), the second value is front or rear, and the third value is direction sideways (corresponding to side), forward, or backward).
/*const char RFF = 1;
const char RFS = 2;
const char RRS = 4;
const char RRR = 8;
const char LRR = 16;
const char LRS = 32;
const char LFS = 64;
const char LFF = 128;*/

// thruster bit - global so publishing happens in code at one place, allowing for time outs
char thrusters;

void deltaVCallback(const flexcraft_msgs::deltaV2D::ConstPtr& msg) {
	thrusters = 0;

  if(msg->deltaVX < 0) {
		// move backward - fire forward facing thrusters
		ROS_INFO("Backward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RFF | flexcraft_msgs::thrusters8::LFF;
	} else if(msg->deltaVX > 0) {
		// move forward - fire backward facing thrusters
		ROS_INFO("Forward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRR | flexcraft_msgs::thrusters8::LRR;
	}

	if(msg->deltaVY < 0) {
		// move to right - fire left thrusters
		ROS_INFO("Right");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRS | flexcraft_msgs::thrusters8::LFS;
	} else if(msg->deltaVY > 0) {
		// move to left - fire right thrusters
		ROS_INFO("Left");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRS | flexcraft_msgs::thrusters8::RFS;
	}

	// rotation - use side thrusters as more sysmetric from center of mass
	if(msg->alpha < 0) {
		// move clockwise
		ROS_INFO("Clockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LFS | flexcraft_msgs::thrusters8::RRS;
	} else if(msg->alpha > 0) {
		// move counterclockwise
		ROS_INFO("Counterclockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRS | flexcraft_msgs::thrusters8::RFS;
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "translator");

	ros::NodeHandle nh;

	ros::Subscriber translator_sub = nh.subscribe("mid_cmd", 1, deltaVCallback);
	ros::Publisher translator_pub = nh.advertise<flexcraft_msgs::thrusters8>("low_cmd", 1);

	ros::Rate loop_rate(10);

	ROS_INFO("Hello, I am C-3PO, human cyborg relations. How might I serve you?");

	int count = 0;
	while (ros::ok())	{
		flexcraft_msgs::thrusters8 low_cmd_msg;

//		low_cmd_msg.thrusters = 0;
		low_cmd_msg.seq = count;
		count++;

		low_cmd_msg.thrusters = thrusters;
		thrusters = 0;
		translator_pub.publish(low_cmd_msg);
		ros::spinOnce();
		loop_rate.sleep();
	}


	return 0;
}
