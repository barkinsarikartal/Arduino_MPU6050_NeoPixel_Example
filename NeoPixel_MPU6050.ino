//Adding Libraries
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

//Defining which pin does the NeoPixel strip use and how many LEDs are there in the strip
#define PIN 5
#define n 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(n,PIN, NEO_GRB + NEO_KHZ800);
MPU6050 mpu6050(Wire);

int red, blue;

void setup() {
  //initializing Serial Port, NeoPixel Strip and MPU6050
  Serial.begin(9600);
  Wire.begin();
  strip.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
}

void loop() {

  //Getting X angle info from MPU6050
  int angleX = mpu6050.getAngleX();
  mpu6050.update();

  //Mapping X angle degrees to 0, 255 for red and 255, 0 for blue
  red = map(angleX, -100, 100, 0, 255);
  blue = map(angleX, -100, 100, 255, 0);
  /* The reason why we reversed blue's value is because
  we want red LEDs to flash when we tilt MPU6050 to left
  and blue LEDs to flash when we tilt it o right. */

  //Printing values for X angle, red and blue
  Serial.print("X: ");
  Serial.print(angleX);
  Serial.print(" Red: ");
  Serial.print(red);
  Serial.print(" Blue: ");
  Serial.println(blue);

  //Coloring all LEDs in the strip with the values
  for(int i = 0; i < n; i++){
    strip.setPixelColor(i, strip.Color(red, 0, blue));
    strip.show();
    delay(10);
  }
  delay(10);
}
