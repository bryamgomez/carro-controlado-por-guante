#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

MPU6050 sensor;
int ax, ay, az;
String str;

int flex_4 = A0;
int flex_3 = A1;
int flex_2 = A2;
int flex_1 = A3;

RF24 radio (7, 8);
const byte address [6] = "00001";
int text[5];

void setup() {

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  Wire.begin();           //Iniciando I2C
  sensor.initialize();    //Iniciando el sensor

}


void loop()
{

  sensor.getAcceleration(&ax, &ay, &az);

  if ((ax > -11000 && ax < 5000) && (ay < 3000 && ay > -5500)) {
    str = "1";
  }
  if ((ax > 5000) && (ay < 3000 && ay > -5500)) {
    str = "2";

  }
  if ((ax < -11000 ) && (ay < 3000 && ay > -5500)) {
    str = "3";

  }
  if ((ax > -11000 && ax < 5000)  && (ay > 3000)) {
    str = "4";
  }
  if ((ax > -11000 && ax < 5000)  && (ay < -5000)) {
    str = "5";
  }

  text[0] = str.toInt();

  text[2] = analogRead(flex_2);
  text[3] = analogRead(flex_1);
  text[4] = analogRead(flex_4);
  Serial.println(text[3]);



  radio.write(&text, sizeof(text));
  delay (100);

}
