/*************************************************************************/ 
// ui_translator.cpp\
//
// This node translates geometry_msgs::Twist to flexcraft_msgs/deltaV2D.
// This is similar to twist translator, although here we are subscribing to
// "flexcraft_ui_joystick/cmd_vel", which is what get published by the 
// mr_teleoperator package (a UI and xbox joystick widget for RQT)
// at flexcraft / src / output_hi / mr_teleoperator 
//
// This could be implemented better by taking the type of joystick, either 
// mouse/keyboard or xbox, and setting the x_vel and z_vel (vertical and horizontal joystick feedback)
// thresholds accordingly, instead of the current implementation where mouse/keyboard thresholds
// are simply commented out
// 
// Eli Davis
/************************************************************************/

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

  //The x_vel and z_vel thresholds are based on vertical and horizontal joystick feedback
  // The if and else statements below are configured for xbox control, see commented code
  // directly below for keyboard and/or mouse direct control feedback thresholds
  
  if (x_vel > 0.6 && z_vel > 0.6)
  { Rotate = 1.0;
    ROS_INFO("counter clockwise"); }
  else if (x_vel > 0.6 && z_vel < -0.6)
  { Rotate = -1.0;
    ROS_INFO("clockwise"); }
  else if (x_vel > 1.5)
  { deltaX = 1.0;
    ROS_INFO("Forward"); }
  else if (x_vel < -1.5)
  { deltaX = -1.0;
    ROS_INFO("Backward"); }
  else if (z_vel > 0.8)
  { deltaY = 1.0;
    ROS_INFO("Left"); }
  else if (z_vel < -0.8)
  { deltaY = -1.0;
    ROS_INFO("Right"); }
  else
  { }  }

// The following commented if and else statements are the thresholds for mouse/keyboard control
/* void uiCallback(const geometry_msgs::Twist::ConstPtr& msg)
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
  
  */

int main(int argc, char **argv)
{ ros::init(argc, argv, "ui_translator");
  ros::NodeHandle nh;

  ros::Subscriber translator_sub = nh.subscribe("flexcraft_ui_joystick/cmd_vel", 1, uiCallback);
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


