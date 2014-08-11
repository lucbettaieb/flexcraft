#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "geometry_msgs/Twist.h"
#include "flexcraft_msgs/deltaV2D.h"
#include "flexcraft_msgs/thrusters8.h"


double x = 0.0;
double y = 0.0;
double th = 0.0;

double vx = 0.0;
double vy = 0.0;
double vth = 0.0;

double last_vx = 0, last_vy = 0, last_vth = 0;


void imuCallback(const flexcraft_msgs::deltaV2D::ConstPtr& msg)
{
  vx = last_vx;
  vy = last_vy;
  vth = last_vth;

  if (msg->deltaVX < 0)
  { // move backward - fire forward facing thrusters
    vx += 0.2;
  }
  else if (msg->deltaVX > 0)
  {// move forward - fire backward facing thrusters
   vx -= 0.2;
  }
  if (msg->deltaVY < 0)
  { // move to right - fire left thrusters
   vy += 0.2;
  }
  else if (msg->deltaVY > 0)
  { // move to left - fire right thrusters
   vy -= 0.2;
  }

  // rotation - use side thrusters as more sysmetric from center of mass
  if (msg->alpha < 0)
  {  // move clockwise
     vth -= 0.05;
  }
  else if (msg->alpha > 0)
  { // move counterclockwise
    vth += .05;
  }


}




int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle n;

  ros::Subscriber imu_sub = n.subscribe("mid_cmd", 1, imuCallback);

  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster odom_broadcaster;


  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  ros::Rate r(1.0);

  while (n.ok())
  {
    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();

    double dt = (current_time - last_time).toSec();
    double delta_x = vx * dt;
    double delta_y = vy * dt;
    double delta_th = vth * dt;

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(odom);

    last_time = current_time;

    last_vx = vx; last_vy = vy; last_vth = vth;

    r.sleep();
  }
}



// For IMU:

/*

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include "geometry_msgs/Twist.h"


double x = 0.0;
double y = 0.0;
double th = 0.0;

double vx = 0.0;
double vy = 0.0;
double vth = 0.0;


void imuCallback(const geometry_msgs::Twist::ConstPtr& msg)
{ vx = msg->linear.x;
  vy = msg->linear.y;
  vth = msg->angular.z;
}


int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");

  ros::NodeHandle n;

  ros::Subscriber imu_sub = n.subscribe("IMU_data", 1, imuCallback);

  ros::Publisher odom_pub = n.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster odom_broadcaster;


  ros::Time current_time, last_time;
  current_time = ros::Time::now();
  last_time = ros::Time::now();

  double current_vx = 0, current_vy = 0, current_vth = 0;
  double last_vx = 0, last_vy = 0, last_vth = 0;

  ros::Rate r(1.0);

  while (n.ok())
  {
    ros::spinOnce();               // check for incoming messages
    current_time = ros::Time::now();
    current_vx = vx; current_vy = vy; current_vth =vth;

    double dt = (current_time - last_time).toSec();
    double delta_x = ((current_vx - last_vx)/2) * dt;
    double delta_y = ((current_vy - last_vy)/2) * dt;
    double delta_th = ((current_vth - last_vth)/2);

    x += delta_x;
    y += delta_y;
    th += delta_th;

    //since all odometry is 6DOF we'll need a quaternion created from yaw
    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

    //first, we'll publish the transform over tf
    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = current_time;
    odom_trans.header.frame_id = "odom";
    odom_trans.child_frame_id = "base_link";

    odom_trans.transform.translation.x = x;
    odom_trans.transform.translation.y = y;
    odom_trans.transform.translation.z = 0.0;
    odom_trans.transform.rotation = odom_quat;

    //send the transform
    odom_broadcaster.sendTransform(odom_trans);

    //next, we'll publish the odometry message over ROS
    nav_msgs::Odometry odom;
    odom.header.stamp = current_time;
    odom.header.frame_id = "odom";

    //set the position
    odom.pose.pose.position.x = x;
    odom.pose.pose.position.y = y;
    odom.pose.pose.position.z = 0.0;
    odom.pose.pose.orientation = odom_quat;

    //set the velocity
    odom.child_frame_id = "base_link";
    odom.twist.twist.linear.x = vx;
    odom.twist.twist.linear.y = vy;
    odom.twist.twist.angular.z = vth;

    //publish the message
    odom_pub.publish(odom);

    last_time = current_time;

    last_vx = current_vx; last_vy = current_vy; last_vth = vth;

    r.sleep();
  }
}

*/

