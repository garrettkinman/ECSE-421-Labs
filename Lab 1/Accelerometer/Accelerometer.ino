#include "LIS3DHTR.h"
#ifdef SOFTWAREWIRE
    #include <SoftwareWire.h>
    SoftwareWire myWire(3, 2);
    LIS3DHTR<SoftwareWire> LIS;       //Software I2C
    #define WIRE myWire
#else
    #include <Wire.h>
    LIS3DHTR<TwoWire> LIS;           //Hardware I2C
    #define WIRE Wire
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
  };
  LIS.begin(WIRE, LIS3DHTR_ADDRESS_UPDATED); //IIC init
  delay(100);
  LIS.setOutputDataRate(LIS3DHTR_DATARATE_50HZ);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!LIS) {
    Serial.println("LIS3DHTR didn't connect.");
    while (1)
      ;
    return;
  }
  //3 axis
  Serial.print(LIS.getAccelerationX()); Serial.print(",");
  Serial.print(LIS.getAccelerationY() + 0.05); Serial.print(",");
  Serial.println(LIS.getAccelerationZ() - 0.05);
  delay(100);
}
