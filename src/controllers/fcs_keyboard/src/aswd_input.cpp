#include "ros/ros.h"
#include "flexcraft_msgs/deltaV2D.h"
#include <termios.h> //needed for non-blocking input
//this is a test
//This function creates a non-blocking character input
// answers.ros.org/question/63491/keyboard-key-pressed/
int getch() {
	static struct termios oldt, newt;	
	tcgetattr( STDIN_FILENO, &oldt);					// save old settings
	newt = oldt;
	newt.c_lflag &= ~(ICANON);								// disable buffering
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);	// apply new settings

	int c = getchar();	// read character (non-blocking)

	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);	// restore old settings
  return c;
}

int main(int argc, char **argv) {
	//node and node name
	ros::init(argc, argv, "aswd_keyboard");

	ros::NodeHandle nh;

	int rate;
	ros::param::param("~rate", rate, 100);

  ros::Publisher keyboard_pub = nh.advertise<flexcraft_msgs::deltaV2D>("mid_cmd", 1);

	ros::Rate loop_rate(rate);

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
