#include <ros/ros.h>
#include <std_msgs/UInt8.h>
#include <geometry_msgs/Twist.h>
#include "flexcraft_msgs/deltaV2D.h"
//#include <sensor_msgs/Joy.h>

using namespace std;
using namespace ros;

float deltaX, deltaY, Rotate;

void uiCallback(const geometry_msgs::Twist::ConstPtr& msg)
{ float x_vel = msg->linear.x;
  float z_vel = msg->angular.z;
  ROS_INFO("%f   %f", x_vel, z_vel);

  if (x_vel > 1.5 && z_vel > 1.5)
  { Rotate = 1.0;
    ROS_INFO("counter clockwise"); }
  else if (x_vel > 1.5 && z_vel < -1.5)
  { Rotate = -1.0;
    ROS_INFO("clockwise"); }
  else if (x_vel > 1.5)
  { deltaX = 1.0;
    ROS_INFO("Forward"); }
  else if (x_vel < -1.5)
  { deltaX = -1.0;
    ROS_INFO("Backward"); }
  else if (z_vel > 1.5)
  { deltaY = 1.0;
    ROS_INFO("Left"); }
  else if (z_vel < -1.5)
  { deltaY = -1.0;
    ROS_INFO("Right"); }
  else
  { }  }



int main(int argc, char **argv)
{ ros::init(argc, argv, "ui_translator");
  ros::NodeHandle nh;

  ros::Subscriber translator_sub = nh.subscribe("flexcraft/cmd_vel", 1, uiCallback);
  ros::Publisher translator_pub = nh.advertise<flexcraft_msgs::deltaV2D>("/mid_cmd", 1);
  ros::Rate loop_rate(4);

int count = 0;


while (ros::ok())
{ flexcraft_msgs::deltaV2D cmd_msg;
  cmd_msg.deltaVX = deltaX;
  cmd_msg.deltaVY = deltaY;
  cmd_msg.alpha = Rotate;

  deltaX=0; deltaY=0; Rotate=0;

  count += 1;

  translator_pub.publish(cmd_msg);
  ros::spinOnce();
  loop_rate.sleep();
}


return 0;
}

