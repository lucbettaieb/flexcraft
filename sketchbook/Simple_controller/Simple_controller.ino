#include <ArduinoHardware.h>
#include <ros.h>
#include "flexcraft_msgs/deltaV2D.h"

ros::NodeHandle nh;

int x_plus;
int x_minus;
int y_minus;
int y_plus;
int z_plus;
int z_minus;

flexcraft_msgs::deltaV2D cmd_msg;

ros::Publisher controller_pub("cmd_msg", &cmd_msg);

void setup(){
  Serial.println("Initializing...");
  
  nh.advertise(controller_pub);
  
  nh.initNode();
  
  Serial.println("Initialized!");
 
    cmd_msg.deltaVX = 0;
    cmd_msg.deltaVY = 0;
    cmd_msg.alpha = 0;
    cmd_msg.seq = 0;
}

void loop(){
    // read the input on analog pin 0:

   x_plus = analogRead(A3);
   x_minus = analogRead(A1);
   y_minus = analogRead(A2);
   y_plus = analogRead(A0);
   z_plus = analogRead(A5);
   z_minus = analogRead(A4);  

//Check direction commands, send them
//If we're going forward or backward, do that; else, don't do that.
  
  if(x_plus > 0){
    cmd_msg.deltaVX = 1.0;
    //Serial.println("ONWARD");
  }
  else if(x_minus > 0){
    cmd_msg.deltaVX = -1.0;
    //Serial.println("RETREAT");  
  }
  else{
    cmd_msg.deltaVX = 0;
  }
  
  //Left/right control
  if(y_minus > 0){
    cmd_msg.deltaVY = -1.0;
    //down = true;
  }
  else if(y_plus > 0){
    cmd_msg.deltaVY =  1.0; 
  }
  else{
    cmd_msg.deltaVY = 0.0;
  }
  //rotation
  if(z_plus > 0){
    cmd_msg.alpha = 1.0;
  }
  else if(z_minus > 0){
    cmd_msg.alpha = -1.0;
  }
  else{
    cmd_msg.alpha = 0.0;
  }
  
  controller_pub.publish(&cmd_msg);
  
  cmd_msg.seq++;

  nh.spinOnce();
  delay(10);        // delay in between reads for stabil  ity
}

