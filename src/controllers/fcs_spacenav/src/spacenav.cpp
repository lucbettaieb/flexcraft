#include "ros/ros.h"
#include "flexcraft_msgs/deltaV2D.h"
#include "sensor_msgs/Joy.h"

class SpaceNav {
	public:
		SpaceNav() {
			pub = nh.advertise<flexcraft_msgs::deltaV2D>("mid_cmd", 1);
			sub = nh.subscribe("/spacenav/joy", 1, &SpaceNav::spacenavCallback, this);
 		}

		void spacenavCallback(const sensor_msgs::Joy::ConstPtr& msg) {
			// also use angle for translation commands for ease of driver (depending on how user grips the system, angle is more natural and easier to accomplish)
			const int joy_x = 0;
			const int joy_y = 1;
			const int joy_z = 2;
			const int joy_roll = 3;
			const int joy_pitch = 4;
			const int joy_yaw = 5;

			float rot_threshold = 0.3;
			float trans_threshold = 0.3;

			flexcraft_msgs::deltaV2D cmd;

			// FCS Y direction
			if (msg->axes[joy_roll] > rot_threshold || msg->axes[joy_y] < -1*trans_threshold) {
				ROS_INFO("Right");
				cmd.deltaVY = -1;
			} else if (msg->axes[joy_roll] < -1*rot_threshold || msg->axes[joy_y] > trans_threshold) {
				ROS_INFO("Left");
				cmd.deltaVY = 1;
			} else {
				cmd.deltaVY = 0;
			}

			// FCS X direction
			if (msg->axes[joy_pitch] > rot_threshold || msg->axes[joy_x] > trans_threshold) {
				ROS_INFO("Forward");
				cmd.deltaVX = 1;
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

			pub.publish(cmd);
		}

	private:
		ros::NodeHandle nh;
		ros::Publisher pub;
		ros::Subscriber sub;
};








int main(int argc, char **argv) {
	ros::init(argc, argv, "fcs_spacenav");

	ROS_INFO("Inside main");

	SpaceNav rosspacenav;

	ros::spin();

	return 0;
}
