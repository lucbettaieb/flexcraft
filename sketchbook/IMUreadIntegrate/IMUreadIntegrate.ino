#include <ArduinoHardware.h>
#include <ros.h>

#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>

#include "geometry_msgs/Twist.h"

ros::NodeHandle nh;
geometry_msgs::Twist IMU_data;
ros::Publisher IMU_pub("IMU_data", &IMU_data);

MPU6050 accelgyro;

//Raw sensor data
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Converted sensor data
float accelx_imu = 0, accely_imu = 0, accelx_in = 0, accely_in = 0;
float velx, vely;
float heading = 0, angRate = 0, theta = 0;

//Random variables I needed to do calculations on the fly
float xbias, ybias, gyrobias;
float xcounter, ycounter, ratecounter;
float multi;

//variables to hold the timer/ designate how long each loop should take
int timer;
int time_step = 50;
float dt = 0.05;

void setup(){
  //Start the node
  nh.advertise(IMU_pub);
  nh.initNode();
  
  //Start sensor interfacing
  Wire.begin();
  Serial.begin(9600);
  //Serial.print("Initializing sensor...");
  accelgyro.initialize();
  //Serial.println("Complete!");
  
  //Calculate IMU biases
  for (int i = 0; i < 100; i++){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    xcounter = xcounter + (float(ax));
    ycounter = ycounter + (float(ay));
    ratecounter = ratecounter + (float(gz));
    //Serial.print(xcounter); Serial.print(","); Serial.println(ycounter);
  }
  
  xbias = xcounter / 100.0;
  ybias = ycounter / 100.0;
  gyrobias = ratecounter /100.0;
}

void loop(){
  //This is used to make every loop take the same amount of time
  timer = millis();
  
  //Get the IMU readings!
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  //Convert into meters per second squared and remove dem biases
  accelx_imu = ((float(ax) - xbias)* 0.000599);
  accely_imu = ((float(ay) - ybias)* 0.000599);
  
  //Assume that we will never have accelerations this low - 500 kg flexcraft (highballed), 10 N thruster (lowballed) means 0.02 m/s^2. readings below that are zero'd
  if(accelx_imu < 0.01){
    accelx_imu = 0;
  }
  if(accely_imu < 0.01){
    accely_imu = 0;
  }
  
  //convert rate into degrees per second
  angRate = (float(gz) - gyrobias)/131.0;
  
  //integrate angular rate to find angle from "reference" frame (read; initial direction)
  theta = theta + (angRate * dt);
  
  //This set of code converts theta into an angle in radians between zero and 2pi
  if(theta <= 360 && theta >= 0){
    heading = theta * (PI/180);
  }
  else if (theta > 360){
    multi = int(theta) / 360;
    heading = (theta - (multi * 360)) * (PI/180);
  }
  else if (theta < 0){
    multi = int(theta) / 360 + 1;
    heading = ((multi*360) - theta) * (PI/180);
  }
  else{
    heading = 0;
  }
  
  //This converts accelerometer readings from the IMU frame (moving) to the inertially fixed reference frame (absolute)
  accelx_in = accelx_imu * cos(heading) + accely_imu * sin(heading);
  accely_in = accely_imu * cos(heading) - accelx_imu * sin(heading);
  
  //Integrate the absolute accelerations to find the absolute velocities
  velx = velx + (accelx_in * dt);
  vely = vely + (accely_in * dt);
  
  //prepare the message with velocities, angular rate
  IMU_data.linear.x = velx;
  IMU_data.linear.y = vely;
  IMU_data.angular.z = -angRate;

  //For debugging
  //Serial.print(accelx_in); Serial.print(","); Serial.print(accely_in); Serial.print(",");  Serial.print(velx); Serial.print(","); Serial.print(vely); Serial.print(","); Serial.print(angRate); Serial.print(","); Serial.println(heading);

  //megaphone dat data doe
  IMU_pub.publish(&IMU_data);
  nh.spinOnce();

  //delay the loop so each iteration is time_step milliseconds
  timer = millis() - timer;

  timer = time_step - timer;

  delay(timer);
}



