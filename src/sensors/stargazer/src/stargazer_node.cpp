#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"
#include "StarGazer.hpp"

#define x_ind 0
#define y_ind 1
#define angle_ind 2

// Calculates the velocity from position and resets the position (pose_f and delta_t are inputs, velocity is output and pose_i is input and output (becomes pose_f))
void pos_to_vel(StarGazer::PositionData &pose_f, double velocity[], double pose_i[], double delta_t) {
	// calculates velocity
	velocity[x_ind] = ((double)pose_f.x - pose_i[x_ind]) / delta_t;
	velocity[y_ind] = ((double)pose_f.y - pose_i[y_ind]) / delta_t;
	velocity[angle_ind] = ((double)pose_f.theta - pose_i[angle_ind]) / delta_t;

	// updates position
	pose_i[x_ind] = (double) pose_f.x;
	pose_i[y_ind] = (double) pose_f.y;
	pose_i[angle_ind] = (double) pose_f.theta;
}

	

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

  sg.write_parameter( "MarkMode", "Alone" );
	sg.write_parameter( "HeightFix", "No" );

	ROS_INFO("MarkType: %s", sg.read_parameter("MarkType").c_str());
	ROS_INFO("IDNum: %s", sg.read_parameter("IDNum").c_str());
	ROS_INFO("RefID: %s", sg.read_parameter("RefID").c_str());
	ROS_INFO("HeightFix: %s", sg.read_parameter("HeightFix").c_str());
	ROS_INFO("MarkMode: %s", sg.read_parameter("MarkMode").c_str());
	ROS_INFO("BaudRate: %s", sg.read_parameter("BaudRate").c_str());


	// Velocity calculation variables
	double velocity[3] = {0, 0, 0};				//{v_x, v_y, omega}
	double position_i[3] = {-1000, -1000, -1000};		//{x, y, theta}
	double time_f, time_i = 0;

	// StarGazer variables
	geometry_msgs::Pose2D pose;

	sg.start_calc();

	StarGazer::PositionData pd;


	while(ros::ok()) {
		pd = sg.get_position().back();

		if ( pd.dead ) {
			std::cout << "dead!\n";
			pose.x = -1000;
			pose.y = -1000;
			pose.theta = -1000;		
		} else {
			std::cout << "x: " << pd.x << ", y: " << pd.y << ", z: " << pd.z << ", theta: " << pd.theta << ", id: " << pd.id << "\n";
			pose.x = pd.x;
			pose.y = pd.y;
			pose.theta = pd.theta;

			// velocity calculations
			time_f = ros::Time::now().toSec();
			pos_to_vel(pd, velocity, position_i, time_f-time_i);
			time_i = time_f;
//			std::cout << "v_x: " << velocity[x_ind] << ", v_y: " << velocity[y_ind] << ", omega: " << velocity[angle_ind] << "\n";

		}

		stargazer_pub.publish(pose);
	}
		
	sg.stop_calc();
}
