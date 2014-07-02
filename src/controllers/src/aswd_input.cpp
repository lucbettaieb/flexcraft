#include "ros/ros.h"
#include <termios.h>

//This function creates a non-blocking character input
int getch() {
	static struct termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	int c = getchar();

	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "aswd_keyboard");

	ros::NodeHandle nh;

	ROS_INFO("Hello Dave");

	int cmd = 'y';

	while(ros::ok() && cmd != 27) {
		cmd = getch();
    switch(cmd) {
			case 'w':
				ROS_INFO("Forward");
				break;
			case 'a':
				ROS_INFO("Left");
				break;
			case 'd':
				ROS_INFO("Right");
				break;
			case 's':
				ROS_INFO("Backward");
				break;
			case 'q':
				ROS_INFO("CCW");
				break;
			case 'e':
				ROS_INFO("CW");
				break;
			case 27:
				ROS_INFO("Are you sure you're making the right decision? I think we should stop");
				break;
			default:
				ROS_INFO("Sorry Dave, I'm afraid I can't do that");
		}
		ros::spinOnce();

	}

	ROS_INFO("Daisy Daaaaaaaaaaaaaaaaaaaaaaaiiiiis");
	return 0;
}
