#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "flexcraft_msgs/thrusters8.h"

// definitions of the bits for each thruster (the first value is which side (left or right), the second value is front or rear, and the third value is direction craft moves (left, right, forward, or backward).
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

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg) {
	thrusters = 0;
	const int linear_thresh = 120;
	const int angle_thresh = 120;

  if(msg->linear.x < -1*linear_thresh) {
		// move backward - fire forward facing thrusters
		ROS_INFO("Backward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RFB | flexcraft_msgs::thrusters8::LFB;
	} else if(msg->linear.x > linear_thresh) {
		// move forward - fire backward facing thrusters
		ROS_INFO("Forward");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRF | flexcraft_msgs::thrusters8::LRF;
	}

	if(msg->linear.y < -1*linear_thresh) {
		// move to right - fire left thrusters
		ROS_INFO("Right");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRR | flexcraft_msgs::thrusters8::LFR;
	} else if(msg->linear.y > linear_thresh) {
		// move to left - fire right thrusters
		ROS_INFO("Left");
		thrusters = thrusters | flexcraft_msgs::thrusters8::RRL | flexcraft_msgs::thrusters8::RFL;
	}

	// rotation - use side thrusters as more sysmetric from center of mass
	if(msg->angular.z < -1*angle_thresh) {
		// move clockwise
		ROS_INFO("Clockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LFR | flexcraft_msgs::thrusters8::RRL;
	} else if(msg->angular.z > angle_thresh) {
		// move counterclockwise
		ROS_INFO("Counterclockwise");
		thrusters = thrusters | flexcraft_msgs::thrusters8::LRR | flexcraft_msgs::thrusters8::RFL;
	}
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "translator");

	ros::NodeHandle nh;

	int rate;
	ros::param::param("~rate", rate, 10);

	ros::Subscriber translator_sub = nh.subscribe("mid_cmd", 1, twistCallback);
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
