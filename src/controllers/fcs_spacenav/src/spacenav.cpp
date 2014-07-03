#include "ros/ros.h"
#include "flexcraft_msgs/deltaV2D.h"
#include "sensor_msgs/Joy"

void spacenavCallback(const sensor_msgs::Joy::ConstPtr& msg) {
	// also use angle for translation commands for ease of driver (depending on how user grips the system, angle is more natural and easier to accomplish)
	const int joy_x = 0;
	const int joy_y = 1;
	const int joy_z = 2;
	const int joy_roll = 3;
	const int joy_pitch = 4;
	const int joy_yaw = 5;

	float rot_threshold = 0.4
	float trans_threshold = 0.4;

	flexcraft_msgs::deltaV2D cmd;

	// FCS Y direction
	if (msg->axes[joy_roll] > rot_threshold || msg->axes[joy_y] < -1*trans_threshold) {
		ROS_INFO("Right");
		cmd.deltaVY = -1;
	} else if (msg->axes[joy_roll] < -1*rot_threshod || msg->axes[joy_y] > trans_threshold) {
		ROS_INFO("Left");
		cmd.deltaVY = 1;
	} else {
		cmd.deltaVY = 0;
	}

	// FCS X direction
	if (msg->axes[joy_pitch] > rot_threshold || msg->axes[joy_x] > trans_threshold) {
		ROS_INFO("Forward");
		cmd.deltaVY = 1;
	} else if (msg->axes[joy_pitch] < -1* rot_threshold || msg->axes[joy_x] < -1*trans_threshold) {
		ROS_INFO("Backward");
		cmd.deltaVX = -1;
	} else {
		cmd.deltaVX = 0;
	}

	// FCS Rotation
	if (msg->axes[joy_yaw] > rot_threshold) {
		ROS_INFO("Counterclockwise");
		cmd.alpha = 1;
	} else if (msg->axes[joy_yaw] < -1*rot_threshold) {
		ROS_INFO("Clockwise");
		cmd.alpha = -1;
	} else {
		cmd.alpha = 0;
	}




int main(int argc, char **argv) {
	//node and node name
	ros::init(argc, argv, "aswd_keyboard");

	ros::NodeHandle nh;

  ros::Publisher keyboard_pub = nh.advertise<flexcraft_msgs::deltaV2D>("mid_cmd", 1);

	ros::Rate loop_rate(100);

	ROS_INFO("Hello Dave");

	int count = 0;
	int cmd = 'y';

	while(ros::ok() && cmd != 27) {

		flexcraft_msgs::deltaV2D cmd_msg;
		cmd_msg.deltaVX = 0;
		cmd_msg.deltaVY = 0;
		cmd_msg.alpha = 0;

		// get input
		cmd = getch();

		// process input
    switch(cmd) {
			case 'w':
				ROS_INFO("Forward");
				cmd_msg.deltaVX = 1;
				break;
			case 'a':
				ROS_INFO("Left");
				cmd_msg.deltaVY = 1;
				break;
			case 'd':
				ROS_INFO("Right");
				cmd_msg.deltaVY = -1;
				break;
			case 's':
				ROS_INFO("Backward");
				cmd_msg.deltaVX = -1;
				break;
			case 'q':
				ROS_INFO("CCW");
				cmd_msg.alpha = 1;
				break;
			case 'e':
				ROS_INFO("CW");
				cmd_msg.alpha = -1;
				break;
			case 27:
				ROS_INFO("Are you sure you're making the right decision? I think we should stop");
				break;
			default:
				ROS_INFO("Sorry Dave, I'm afraid I can't do that");
		}
		
		cmd_msg.seq = count;
		keyboard_pub.publish(cmd_msg);

		ros::spinOnce();
		count++;

		loop_rate.sleep();
	}

	ROS_INFO("Daisy Daaaaaaaaaaaaaaaaaaaaaaaiiiiis");
	return 0;
}
