// Basic demo for magnetometer readings from Adafruit LIS3MDL

#include <Wire.h>
#include <Adafruit_LIS3MDL.h>
#include <Adafruit_Sensor.h>
#include <Arduino_LSM6DSOX.h>

Adafruit_LIS3MDL lis3mdl;
#define LIS3MDL_CLK 19  //SCL
#define LIS3MDL_MISO 12
#define LIS3MDL_MOSI 18  //SDA
#define LIS3MDL_CS 10
#define MAGNEETPIN 33

void setup(void) {
  Serial.begin(115200);
  Wire.setSCL(19);
  Wire.setSDA(18);

  while (!Serial) delay(10);  // will pause Zero, Leonardo, etc until serial console opens

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1)
      ;
  }

  // Try to initialize!
  if (!lis3mdl.begin_I2C()) {  // hardware I2C mode, can pass in address & alt Wire
                               //if (! lis3mdl.begin_SPI(LIS3MDL_CS)) {  // hardware SPI mode
                               //if (! lis3mdl.begin_SPI(LIS3MDL_CS, LIS3MDL_CLK, LIS3MDL_MISO, LIS3MDL_MOSI)) { // soft SPI
    Serial.println("Failed to find LIS3MDL chip");
    while (1) { delay(10); }
  }



  Serial.println("LIS3MDL Found!");
  Serial.println("Accelerometer Found!");


  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in g's");
  Serial.println("X\tY\tZ");

  //MAGNEET
  lis3mdl.setPerformanceMode(LIS3MDL_ULTRAHIGHMODE);
  lis3mdl.setOperationMode(LIS3MDL_CONTINUOUSMODE);
  lis3mdl.setDataRate(LIS3MDL_DATARATE_1000_HZ);
  lis3mdl.setRange(LIS3MDL_RANGE_16_GAUSS);

  lis3mdl.setIntThreshold(500);
  lis3mdl.configInterrupt(false, false, true,  // enable z axis
                          true,                // polarity
                          false,               // don't latch
                          true);               // enabled!c

}  //end setup

void loop() {

  //ACCELEROMLETER
  float x, y, z;
  //MAGNEET
  /*IMU.readAcceleration(x, y, z);
  Serial.print(x);
  Serial.print("  ");
  Serial.print(y);
  Serial.print("  ");
  Serial.println(z);
  lis3mdl.read();  // get X Y and Z data at once*/
  // Then print out the raw data
  lis3mdl.read();
  Serial.print("  ");
  Serial.print(lis3mdl.x);
  Serial.print("  ");
  Serial.print(lis3mdl.y);
  Serial.print("  ");
  Serial.println(lis3mdl.z);
  delay(20);
}