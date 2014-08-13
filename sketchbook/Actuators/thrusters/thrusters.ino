const char RFB=4;
const char RFL=5;
const char RRL=8;
const char RRF=9;
const char LRF=7;
const char LRR=6;
const char LFR=3;
const char LFB=2;

#include <ros.h>
#include <std_msgs/UInt8.h>
#include <flexcraft_msgs/thrusters8.h>

ros::NodeHandle  nh;

const int timeout = 10000;  //timeout is used to ensure not using outdated commands
                            //10000 is chosen for being long enough through slight empirical studies, not necessarily a great value
int timeout_counter;        //timout_counter is used to track 'time' against timeout

void messageCb(const flexcraft_msgs::thrusters8& msg)
{ unsigned char thruster_control = msg.thrusters;

  digitalWrite(RFB, thruster_control & msg.RFB);
  digitalWrite(RFL, thruster_control & msg.RFL);
  digitalWrite(RRL, thruster_control & msg.RRL);
  digitalWrite(RRF, thruster_control & msg.RRF);
  digitalWrite(LRF, thruster_control & msg.LRF);
  digitalWrite(LRR, thruster_control & msg.LRR);
  digitalWrite(LFR, thruster_control & msg.LFR);
  digitalWrite(LFB, thruster_control & msg.LFB);
  
  //new command, reset timeout_counter
  timeout_counter = 0;

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

ros::Subscriber<flexcraft_msgs::thrusters8> sub("low_cmd", &messageCb );

void setup()
{ pinMode(RFB, OUTPUT);
  pinMode(RFL, OUTPUT);
  pinMode(RRL, OUTPUT);
  pinMode(RRF, OUTPUT);
  pinMode(LRF, OUTPUT);
  pinMode(LRR, OUTPUT);
  pinMode(LFR, OUTPUT);
  pinMode(LFB, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  
  timeout_counter = 0;
}

void loop()
{
  if(timeout_counter > timeout)
  {
    digitalWrite(RFB, LOW);
    digitalWrite(RFL, LOW);
    digitalWrite(RRL, LOW);
    digitalWrite(RRF, LOW);
    digitalWrite(LRF, LOW);
    digitalWrite(LRR, LOW);
    digitalWrite(LFR, LOW);
    digitalWrite(LFB, LOW);
  }
  
  nh.spinOnce();
//  delay(1000);

  timeout_counter++;
}

