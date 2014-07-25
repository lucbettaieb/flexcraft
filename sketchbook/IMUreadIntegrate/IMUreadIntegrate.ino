                   
#include <I2Cdev.h>
#include <MPU6050.h>

#include <Wire.h>

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

  Serial.print(accelx); Serial.print(","); Serial.print(accely); Serial.print(",");  Serial.print(velx); Serial.print(","); Serial.print(vely); Serial.print(","); Serial.println(angRate);

  timer = millis() - timer;

  timer = time_step - timer;

  Serial.println(timer);

  delay(timer);
}



