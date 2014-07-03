#include "ros/ros.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "aswd_keyboard");

	ros::NodeHandle nh;

	while(ros::ok())
	{
		std::cout << "Hello Dave" << std::endl;

		ros::spinOnce();

	}

	return 0;
}
