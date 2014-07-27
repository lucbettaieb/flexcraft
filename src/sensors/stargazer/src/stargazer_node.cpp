#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "StarGazer.hpp"

int main(int argc, char **argv) {
	// Variables - should be parameters
	int pub_freq = 100;
	std::string port = "/dev/ttyUSB0";
	

	// Initialize Ros
	ros::init(argc, argv, "stargazer_pose2D");

	ros::NodeHandle nh;

	ros::Publisher stargazer_pub = nh.advertise<geometry_msgs::Pose2D>("stargazer/pose2D", 1);

	ros::Rate loop_rate(pub_freq);


	// Initialize StarGazer;
	StarGazer sg(port);

	ROS_INFO("MarkType: %s", sg.read_parameter("MarkType").c_str());
	ROS_INFO("IDNum: %s", sg.read_parameter("IDNum").c_str());
	ROS_INFO("RefID: %s", sg.read_parameter("RefID").c_str());
	ROS_INFO("HeightFix: %s", sg.read_parameter("HeightFix").c_str());
	ROS_INFO("MarkMode: %s", sg.read_parameter("MarkMode").c_str());
	ROS_INFO("BaudRate: %s", sg.read_parameter("BaudRate").c_str());

	geometry_msgs::Pose2D pose;

	sg.start_calc();

	StarGazer::PositionData pd;


	while(ros::ok()) {
		pd = sg.get_position().back();

		if ( pd.dead ) {
			std::cout << "dead!\n";
			pose.x = -100;
			pose.y = -100;
			pose.theta = -100;		
		} else {
			std::cout << "x: " << pd.x << ", y: " << pd.y << ", z: " << pd.z << ", theta: " << pd.theta << ", id: " << pd.id << "\n";
			pose.x = pd.x;
			pose.y = pd.y;
			pose.theta = pd.theta;
		}

		stargazer_pub.publish(pose);
	}
		
	sg.stop_calc();
}
