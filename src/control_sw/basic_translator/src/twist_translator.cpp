#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
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

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg) {
	thrusters = 0;
	const int linear_thresh = 120;
	const int angle_thresh = 120;

  if(msg->linear.x < -1*linear_thresh) {
		// move backward - fire forward facing thrusters
		ROS_INFO("Backward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RFF | flexcraft_msgs::thrusters8::LFF;
	} else if(msg->linear.x > linear_thresh) {
		// move forward - fire backward facing thrusters
		ROS_INFO("Forward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRR | flexcraft_msgs::thrusters8::LRR;
	}

	if(msg->linear.y < -1*linear_thresh) {
		// move to right - fire left thrusters
		ROS_INFO("Right");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRS | flexcraft_msgs::thrusters8::LFS;
	} else if(msg->linear.y > linear_thresh) {
		// move to left - fire right thrusters
		ROS_INFO("Left");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRS | flexcraft_msgs::thrusters8::RFS;
	}

	// rotation - use side thrusters as more sysmetric from center of mass
	if(msg->angular.z < -1*angle_thresh) {
		// move clockwise
		ROS_INFO("Clockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LFS | flexcraft_msgs::thrusters8::RRS;
	} else if(msg->angular.z > angle_thresh) {
		// move counterclockwise
		ROS_INFO("Counterclockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRS | flexcraft_msgs::thrusters8::RFS;
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "translator");

	ros::NodeHandle nh;

	ros::Subscriber translator_sub = nh.subscribe("mid_cmd", 1, twistCallback);
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
