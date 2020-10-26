#include <SoftwareSerial.h>
#include <Arduino_LSM9DS1.h>



SoftwareSerial softwareSerial(5, 6);

const int pressPin = 4;
const float  OffSetPressure = 0.483 ;     //This value should be overwritten at start to calibrate the sensor
float outputPressure, pressureValue;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.setTimeout(10);
  IMU.begin();
  softwareSerial.begin(38400);

}

void loop() {

  // If the command is recieved from Qt will send it automatically to Thrusters arduino
  if (Serial.available()) {
    softwareSerial.print(Serial.readString());
  }



  // Update the value of pressure and imu sensors every 5 sec and send it to Qt
  if (millis() % 5000 == 0) {
    outputPressure = analogRead(0) * 5.00 / 1024;                        //Sensor output voltage
    pressureValue = (outputPressure - OffSetPressure) * 400;             //Calculate water pressure
    Serial.println(IMU.accelerationSampleRate()+ " Hz");
    Serial.println(pressureValue+" Pa");
  }

}
