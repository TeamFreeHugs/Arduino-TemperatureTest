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
  if (tmpC > warningTmp) {
    loopColorYellow();
  }

  motor.run(100);

  if (tmpC > 31 && tmpC < 35) {
    motor.run(100);
  } else if (tmpC > 35.1 && tmpC < 37) {
    motor.run(200);
  } else if (tmpC > 37.1 && tmpC < 39.9) {
    motor.run(300);
  } else if (tmpC > 40) {
    motor.run(-200);
  } else {
    motor.stop();
  }
  delay(5);
}

void loopColorYellow() {
  for (int i = 1; i < 5; i++) {
    led.setColorAt(i, 237, 231, 40);
    led.show();
    delay(1);
    led.setColorAt(i, 0, 0, 0);
    led.show();
  }
}
