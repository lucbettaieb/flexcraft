#include "ros/ros.h"
#include "flexcraft_msgs/deltaV2D.h"
#include "flexcraft_msgs/thrusters8.h"

// definitions of the bits for each thruster (the first value is which side (left or right), the second value is front or rear, and the third value is direction craft moves left, right, forward, or backward).
/*const char RFB = 1;
const char RFL = 2;
const char RRL = 4;
const char RRF = 8;
const char LRF = 16;
const char LRR = 32;
const char LFR = 64;
const char LFB = 128;*/

// thruster bit - global so publishing happens in code at one place, allowing for time outs
char thrusters;

void deltaVCallback(const flexcraft_msgs::deltaV2D::ConstPtr& msg) {
	thrusters = 0;

  if(msg->deltaVX < 0) {
		// move backward - fire forward facing thrusters
		ROS_INFO("Backward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RFB | flexcraft_msgs::thrusters8::LFB;
	} else if(msg->deltaVX > 0) {
		// move forward - fire backward facing thrusters
		ROS_INFO("Forward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRF | flexcraft_msgs::thrusters8::LRF;
	}

	if(msg->deltaVY < 0) {
		// move to right - fire left thrusters
		ROS_INFO("Right");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRR | flexcraft_msgs::thrusters8::LFR;
	} else if(msg->deltaVY > 0) {
		// move to left - fire right thrusters
		ROS_INFO("Left");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRL | flexcraft_msgs::thrusters8::RFL;
	}

	// rotation - use side thrusters as more sysmetric from center of mass
	if(msg->alpha < 0) {
		// move clockwise
		ROS_INFO("Clockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LFR | flexcraft_msgs::thrusters8::RRL;
	} else if(msg->alpha > 0) {
		// move counterclockwise
		ROS_INFO("Counterclockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRR | flexcraft_msgs::thrusters8::RFL;
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "translator");

	ros::NodeHandle nh;

	int rate;  //publishing rate
	ros::param::param<int>("~rate", rate, 10);
	ros::Subscriber translator_sub = nh.subscribe("mid_cmd", 1, deltaVCallback);
	ros::Publisher translator_pub = nh.advertise<flexcraft_msgs::thrusters8>("low_cmd", 1);


	ros::Rate loop_rate(rate);

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
