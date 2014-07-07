//const char RFF=1;
//const char RFS=2;
//const char RRS=4;
//const char RRR=8;
//const char LRR=16;
///const char LRS=32;
//const char LFS=64;
//const char LFF=128;

#include <ros.h>
#include <std_msgs/UInt8.h>
#include <flexcraft_msgs/thrusters8.h>

ros::NodeHandle  nh;

void messageCb(const flexcraft_msgs::thrusters8& msg)
{ unsigned char thruster_control = msg.thrusters;

  if (thruster_control & msg.RFF)
    digitalWrite(6, HIGH);
  if (thruster_control & msg.RFS)
    digitalWrite(7, HIGH);
  if (thruster_control & msg.RRS)
    digitalWrite(8, HIGH);
  if (thruster_control & msg.RRR)
    digitalWrite(9, HIGH);
  if (thruster_control & msg.LRR)
    digitalWrite(10, HIGH);
  if (thruster_control & msg.LRS)
    digitalWrite(11, HIGH);
  if (thruster_control & msg.LFS)
    digitalWrite(12, HIGH);
  if (thruster_control & msg.LFF)
    digitalWrite(13, HIGH);

/*  //OFF
  delay(2000);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
 digitalWrite(13, LOW);
  delay(500);*/
}

ros::Subscriber<flexcraft_msgs::thrusters8> sub("cmd_low", &messageCb );

void setup()
{ pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
//  delay(1000);
}

