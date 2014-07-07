#include <ArduinoHardware.h>
#include <ros.h>
#include "flexcraft_msgs/deltaV2D.h"
ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher joystick = nhadvertise<flexcraft_msgs::deltaV2D>("mid_cmd",1);

ROS_INFO("Good Morning Doctor Chandra");

int x_plus;
int x_minus;
int y_minus;
int y_plus;


void setup(){
  nh.initNode();
}

void loop(){
    // read the input on analog pin 0:
   x_plus = analogRead(A0);
   x_minus = analogRead(A3);
   y_minus = analogRead(A2);
   y_plus = analogRead(A1);
  

//Assign boolean values
  if(x_plus > 900){
    //up = true;
    
  }
  else{
    //up = false;
  }
  
  if(x_minus > 900){
    //down = true;
  }
  else{
    //down = false;
  }
  
  if(y_plus >900){
    //left = true;
  }
  else{
    //left = false;
  }
  
  if(y_minus > 900){
   // right = true;
  }
  else{
    //right = false;
  }
  
//  Serial.print("Forward: "); Serial.println(forward);
//  Serial.print("Backward: "); Serial.println(backward);
//  Serial.print("Left: "); Serial.println(left);
//  Serial.print("Right: "); Serial.println(right);
  nh.spinOnce();
  delay(1);        // delay in between reads for stability
}

