#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeTemperature myTemp(PORT_3, SLOT1);

Me7SegmentDisplay disp(PORT_6);

MeDCMotor motor(M1);

MeRGBLed led(PORT_4);

float tmpC = 0;

float warningTmp = 36.5;

void setup()
{
  disp.set();
  disp.init();
  Serial.begin(9600);
  led.setNumber(4);
  led.setColorAt(1, 237, 231, 40);

}
void loop()
{
  tmpC = myTemp.temperature();
  printf("%f", tmpC);
  Serial.print("Temperature=");
  Serial.println(tmpC);
  disp.display(tmpC);


  motor.run(100);

  if (tmpC < 33) {
    motor.run(100);
    loopColorWhite();
  } else if (tmpC > 35.1 && tmpC < 37) {
    motor.run(200);
    loopColorYellow();
  } else if (tmpC > 37.1 && tmpC < 39.9) {
    motor.run(300);
    loopColorBlue();
  } else if (tmpC > 40) {
    motor.run(-200);
    loopColorRed();
  } else {
    motor.stop();
  }
  delay(5);
}

void loopColorYellow() {
  for (int i = 1; i < 4; i++) {
    led.setColorAt(i, 237, 231, 40);
    led.show();
    delay(1);
    led.setColorAt(i, 0, 0, 0);
    led.show();
  }
}

void loopColorRed() {
  for (int i = 1; i < 4; i++) {
    led.setColorAt(i, 235, 0, 0);
    led.show();
    delay(1);
    led.setColorAt(i, 0, 0, 0);
    led.show();
  }
}

void loopColorWhite() {
  for (int i = 1; i < 4; i++) {
    led.setColorAt(i, 255, 255, 255);

    led.show();
    delay(1);
    led.setColorAt(i, 0, 0, 0);
    led.show();
  }
}

void loopColorBlue() {
  for (int i = 1; i < 4; i++) {
    led.setColorAt(i, 92, 37, 204);
    led.show();
    delay(1);
    led.setColorAt(i, 0, 0, 0);
    led.show();
  }
}
