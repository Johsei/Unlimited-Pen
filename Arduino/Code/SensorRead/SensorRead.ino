/****************************************************************
 * Example1_Basics.ino
 * ICM 20948 Arduino Library Demo 
 * Use the default configuration to stream 9-axis IMU data
 * Owen Lyke @ SparkFun Electronics
 * Original Creation Date: April 17 2019
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ***************************************************************/
#include "ICM_20948.h"  // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU
#include <math.h>

#define SERIAL_PORT Serial

#define WIRE_PORT Wire  // Your desired Wire port.
#define AD0_VAL   0     // The value of the last bit of the I2C address. 
                        // On the SparkFun 9DoF IMU breakout the default is 1, and when 
                        // the ADR jumper is closed the value becomes 0

ICM_20948_I2C myICM;  // create an ICM_20948_I2C object

float acc[3], mag[3];

void setup() {

  SERIAL_PORT.begin(115200);
  while(!SERIAL_PORT){};

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);
  
  bool initialized = false;
  while( !initialized ){

    myICM.begin( WIRE_PORT, AD0_VAL );

    // SERIAL_PORT.print( F("Initialization of the sensor returned: ") );
    // SERIAL_PORT.println( myICM.statusString() );
    
    if( myICM.status != ICM_20948_Stat_Ok ){
      SERIAL_PORT.println( "Trying again..." );
      delay(500);
    }else{
    initialized = true;
    }
  }
}

void loop() {

  if( myICM.dataReady() ){

    // Neue Daten abholen
    myICM.getAGMT();

    // Vektoren von Beschleunigung und Magnetfeld fuellen
    acc[0] = myICM.accX();
    acc[1] = myICM.accY();
    acc[2] = myICM.accZ();

    mag[0] = myICM.magX();
    mag[1] = myICM.magY();
    mag[2] = myICM.magZ();

    SERIAL_PORT.print("accX:");
    SERIAL_PORT.print(acc[0],6);
    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("accY:");
    SERIAL_PORT.print(acc[1],6);
    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("accZ:");
    SERIAL_PORT.print(acc[2],6);
    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("magX:");
    SERIAL_PORT.print(mag[0],6);
    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("magY:");
    SERIAL_PORT.print(mag[1],6);
    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("magZ:");
    SERIAL_PORT.print(mag[2],6);

    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("accGes:");
    SERIAL_PORT.print(vectorsum(acc),6);
    SERIAL_PORT.print("\t\t");
    SERIAL_PORT.print("magGes:");
    SERIAL_PORT.println(vectorsum(mag),6);

    


    
//    SERIAL_PORT.print(myICM.accX(),6);
//    SERIAL_PORT.print("\t");
//    SERIAL_PORT.print(myICM.accY(),6);
//    SERIAL_PORT.print("\t");
//    SERIAL_PORT.print(myICM.accZ(),6);
//    SERIAL_PORT.print("\t");

//    SERIAL_PORT.print(myICM.magX(),6);
//    SERIAL_PORT.print("\t");
//    SERIAL_PORT.print(myICM.magY(),6);
//    SERIAL_PORT.print("\t");
//    SERIAL_PORT.println(myICM.magZ(),6);
    

    // Send Accel X to Serial (Key: G)
    //Serial.print("G");
    //printhex(myICM.accX());

    // Send Accel Y to Serial (Key: H)
    //Serial.print("H");
    //printhex(myICM.accY());

    // Send Accel Z to Serial (Key: I)
    //Serial.print("I");
    //printhex(myICM.accZ());

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
    
    //delay(20);
  }
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
  SERIAL_PORT.print(floatString);
}

float vectorsum(float vector[])
{
  return sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
}



// OLD STUFF

void printFormattedFloat(float val, uint8_t leading, uint8_t decimals){
  float aval = abs(val);
  if(val < 0){
    SERIAL_PORT.print("-");
  }else{
    SERIAL_PORT.print(" ");
  }
  for( uint8_t indi = 0; indi < leading; indi++ ){
    uint32_t tenpow = 0;
    if( indi < (leading-1) ){
      tenpow = 1;
    }
    for(uint8_t c = 0; c < (leading-1-indi); c++){
      tenpow *= 10;
    }
    if( aval < tenpow){
      SERIAL_PORT.print("0");
    }else{
      break;
    }
  }
  if(val < 0){
    SERIAL_PORT.print(-val, decimals);
  }else{
    SERIAL_PORT.print(val, decimals);
  }
}

void printScaledAGMT( ICM_20948_AGMT_t agmt){
  SERIAL_PORT.print("Scaled. Acc (mg) [ ");
  printFormattedFloat( myICM.accX(), 5, 2 );
  SERIAL_PORT.print(", ");
  printFormattedFloat( myICM.accY(), 5, 2 );
  SERIAL_PORT.print(", ");
  printFormattedFloat( myICM.accZ(), 5, 2 );
  SERIAL_PORT.print(" ], Gyr (DPS) [ ");
  printFormattedFloat( myICM.gyrX(), 5, 2 );
  SERIAL_PORT.print(", ");
  printFormattedFloat( myICM.gyrY(), 5, 2 );
  SERIAL_PORT.print(", ");
  printFormattedFloat( myICM.gyrZ(), 5, 2 );
  SERIAL_PORT.print(" ], Mag (uT) [ ");
  printFormattedFloat( myICM.magX(), 5, 2 );
  SERIAL_PORT.print(", ");
  printFormattedFloat( myICM.magY(), 5, 2 );
  SERIAL_PORT.print(", ");
  printFormattedFloat( myICM.magZ(), 5, 2 );
  SERIAL_PORT.print(" ], Tmp (C) [ ");
  printFormattedFloat( myICM.temp(), 5, 2 );
  SERIAL_PORT.print(" ]");
  SERIAL_PORT.println();
}
