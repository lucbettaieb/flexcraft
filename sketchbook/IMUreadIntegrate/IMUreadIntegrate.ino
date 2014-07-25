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

int16_t ax, ay, az;
int16_t gx, gy, gz;

float accelx, accely;
float velx, vely;
float angRate;

int timer;
int time_step = 8;
float dt = float(time_step) * (1.0/1000.0);

void setup(){
  
  nh.advertise(IMU_pub);
  
  nh.initNode();
  
  Wire.begin();
  Serial.begin(57600);
  Serial.print("Initializing sensor...");
  accelgyro.initialize();
  Serial.println("Complete!");
}

void loop(){
  timer = millis();
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  accelx = float(ax) / 16072.704;
  accely = float(ay) / 16072.704;
  angRate = float(gz) / 131;
  velx = velx + accelx * dt;
  vely = vely + accely * dt;
  
  IMU_data.linear.x = velx;
  IMU_data.linear.x = vely;
  IMU_data.angular.z = -angRate;

  //Serial.print(accelx); Serial.print(","); Serial.print(accely); Serial.print(",");  Serial.print(velx); Serial.print(","); Serial.print(vely); Serial.print(","); Serial.println(angRate);

  IMU_pub.publish(&IMU_data);

  nh.spinOnce();

  timer = millis() - timer;

  timer = time_step - timer;

  Serial.println(timer);

  delay(timer);
}



