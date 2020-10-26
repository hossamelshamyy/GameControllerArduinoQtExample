#include <SoftwareSerial.h>

SoftwareSerial softwareSerial(5, 6);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  softwareSerial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
if (softwareSerial.available()) {
    String x = softwareSerial.readString();
    verticalThrusters(x.substring(1,4).toInt());
    horizontalThrusters(x.substring(4).toInt());
  }
}

void verticalThrusters(int speed) {
  Serial.println("Vertical speed = " + speed);
}
void horizontalThrusters(int speed) {
  Serial.println("Horizontal speed = " + speed);

}
