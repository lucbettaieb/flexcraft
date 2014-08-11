#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <interactive_markers/interactive_marker_server.h>

void processFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback )
{ ROS_INFO_STREAM( feedback->marker_name << " is now at "  << feedback->pose.position.x << ", " << feedback->pose.position.y << ", " << feedback->pose.position.z ); }

int main(int argc, char** argv)
{ ros::init(argc, argv, "fcs2");

  // create an interactive marker server on the topic namespace simple_marker
  interactive_markers::InteractiveMarkerServer server("fcs2");

  // create an interactive marker for our server
  visualization_msgs::InteractiveMarker int_marker;

  int_marker.header.frame_id = "/base_link";
  int_marker.name = "my_marker";
  int_marker.description = "FlexCraft Simulator";

  //create a fcs marker
  visualization_msgs::Marker box_marker;
  box_marker.type = visualization_msgs::Marker::MESH_RESOURCE;
  //box_marker.mesh_resource = "file:///home/fcs_basestation/catkin_ws/src/flexcraft/src/displays/using_markers/meshes/flexcraft.dae";
  box_marker.mesh_resource = "package://using_markers/meshes/flexcraft.dae";

  box_marker.scale.x = 0.7;
  box_marker.scale.y = 0.7;
  box_marker.scale.z = 0.6;
  box_marker.color.r = 1.0;
  box_marker.color.g = 1.0;
  box_marker.color.b = 1.0;
  box_marker.color.a = 1.0;

  // create a non-interactive control which contains the fcs
  visualization_msgs::InteractiveMarkerControl box_control;
  box_control.always_visible = true;
  box_control.markers.push_back( box_marker );

  // add the control to the interactive marker
  int_marker.controls.push_back( box_control );

  //create a control message to manually translate in x and y, and rotate fcs (in RViz)
  visualization_msgs::InteractiveMarkerControl control;

  control.orientation.w = 1;
  control.orientation.x = 1;
  control.orientation.y = 0;
  control.orientation.z = 0;
  control.name = "move_x";
  control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
  int_marker.controls.push_back(control);

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 1;
  control.orientation.z = 0;
  control.name = "rotate_z";
  control.interaction_mode = visualization_msgs::InteractiveMarkerControl::ROTATE_AXIS;
  int_marker.controls.push_back(control);

  control.orientation.w = 1;
  control.orientation.x = 0;
  control.orientation.y = 0;
  control.orientation.z = 1;
  control.name = "move_y";
  control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;

  // add the control to the interactive marker
  int_marker.controls.push_back(control);




  // add the interactive marker to our collection &
  // tell the server to call processFeedback() when feedback arrives for it
  server.insert(int_marker, &processFeedback);

  // 'commit' changes and send to all clients
  server.applyChanges();

  // start the ROS main loop
  ros::spin();
}
// %Tag(fullSource)%







//Template



/*
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <interactive_markers/interactive_marker_server.h>

void processFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback )
{
  ROS_INFO_STREAM( feedback->marker_name << " is now at "
      << feedback->pose.position.x << ", " << feedback->pose.position.y
      << ", " << feedback->pose.position.z );
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "fcs2");

  // create an interactive marker server on the topic namespace simple_marker
  interactive_markers::InteractiveMarkerServer server("fcs2");

  // create an interactive marker for our server
  visualization_msgs::InteractiveMarker int_marker;
  int_marker.header.frame_id = "/base_link";
  int_marker.name = "my_marker";
  int_marker.description = "Simple 1-DOF Control";

  // create a marker
  visualization_msgs::Marker marker;
  marker.type = visualization_msgs::Marker::MESH_RESOURCE;
  marker.mesh_resource = "file:///home/fcs_basestation/catkin_ws/src/using_markers/meshes/flexcraft.dae";


  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;
  marker.color.r = 1.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;


  // create a non-interactive control which contains the box
  visualization_msgs::InteractiveMarkerControl box_control;
  box_control.always_visible = true;
  box_control.markers.push_back( marker );

  // add the control to the interactive marker
  int_marker.controls.push_back( box_control );

  // create a control which will move the box
  // this control does not contain any markers,
  // which will cause RViz to insert two arrows
  visualization_msgs::InteractiveMarkerControl rotate_control;
  rotate_control.name = "move_x";
  rotate_control.interaction_mode =
      visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;

  // add the control to the interactive marker
  int_marker.controls.push_back(rotate_control);

  // add the interactive marker to our collection &
  // tell the server to call processFeedback() when feedback arrives for it
  server.insert(int_marker, &processFeedback);

  // 'commit' changes and send to all clients
  server.applyChanges();

  // start the ROS main loop
  ros::spin();
}
// %Tag(fullSource)%





*/
