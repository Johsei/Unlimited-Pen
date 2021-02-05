//Lib: https://github.com/dtornqvist/icm-20948-arduino-library

#include "ICM20948.h"

// an ICM20948 object with the ICM-20948 sensor on I2C bus 0 with address 0x69
ICM20948 IMU(Wire, 0x68);

void printhex(float f); 

int status;
char buffer [8];


void setup() {
  // serial to display data
  Serial.begin(115200);
  /*Serial.println("Initializing Serial...");
  while(!Serial) {}
  Serial.println("Serial initialized");*/

  // start communication with IMU 
  status = IMU.begin();
  /*Serial.print("status = ");
  Serial.println(status);
  if (status < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status);
    while(1) {}
  }*/

}

void loop() {
  // read the sensor
  IMU.readSensor();

  /*

  //Bei Fehlern könnte ein check von Serial.availableForWrite() helfen
  
  // Send Accel X to Serial (Key: G)
  Serial.print("G");
  printhex(IMU.getAccelX_mss());

  // Send Accel Y to Serial (Key: H)
  Serial.print("H");
  printhex(IMU.getAccelY_mss());

  // Send Accel Z to Serial (Key: I)
  Serial.print("I");
  printhex(IMU.getAccelZ_mss());

  // Send Accel X to Serial (Key: J)
  //Serial.print("J");
  //printhex(IMU.getAccelX_mss());
  
  // Send Accel X to Serial (Key: K)
  //Serial.print("K");
  //printhex(IMU.getAccelX_mss());

  // Send Accel X to Serial (Key: L)
  //Serial.print("L");
  //printhex(IMU.getAccelX_mss());

  // Send Accel X to Serial (Key: M)
  //Serial.print("M");
  //printhex(IMU.getAccelX_mss());

  // Send Accel X to Serial (Key: N)
  //Serial.print("N");
  //printhex(IMU.getAccelX_mss());

  // Send Accel X to Serial (Key: O)
  //Serial.print("O");
  //printhex(IMU.getAccelX_mss());

  //Send Key Pressed Event (Key: P)
  //TODO

  //Send Key Released Event (Key: Q)
  //TODO

  */

  Serial.print(IMU.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.println(IMU.getAccelZ_mss(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getGyroX_rads(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getGyroY_rads(),6);
  //Serial.print("\t");
  //Serial.println(IMU.getGyroZ_rads(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getMagX_uT(),6);
  //Serial.print("\t");
  //Serial.print(IMU.getMagY_uT(),6);
  //Serial.print("\t");
  //Serial.println(IMU.getMagZ_uT(),6);
  //Serial.print("\t");
  //Serial.println(IMU.getTemperature_C(),6);
  
  //delay();
}

void printhex(float f)
{
  //Cool fürs Verständnis von Floats: https://www.h-schmidt.net/FloatConverter/IEEE754.html
  //Im folgenden wird aus der vom Sensor ausgegebenen Float eine HEX gemacht, die dann effizient ausgegeben werden kann
  
  char floatString[9]; //Zwischenspeicher, enthält die float als Hex-String
  unsigned char *chpt; //Pointer, der auf die float zeigt, um sie als Hex mit sprintf einzulesen
  
  chpt = (unsigned char *)&f;
  sprintf(floatString, "%02X%02X%02x%02x", chpt[3], chpt[2], chpt[1], chpt[0]);
  floatString[8] = '\0';
  Serial.print(floatString);
}
