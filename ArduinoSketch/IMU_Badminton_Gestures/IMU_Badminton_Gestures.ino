#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <EEPROM.h>

/* delay between samples */
#define BNO055_SAMPLERATE_DELAY_MS (12)

Adafruit_BNO055 bno055_sensor = Adafruit_BNO055(1,BNO055_ADDRESS_A);

void setup(void)
{
  Serial.begin(115200);
  /* Inicializar el sensor */
  delay(1000);
  if(!bno055_sensor.begin())
  {
    while(1)
    {
      Serial.println
      ("Sensor BNO055 no detectado... revisar cableado I2C ADDR!");
      delay(100);
    }
  }
  Serial1.begin(115200);
  delay(1000);
  bno055_sensor.setExtCrystalUse(true);
}

void loop()
{
  // - Absolute Orientation - 
  imu::Quaternion quat = bno055_sensor.getQuat(); 
  // - VECTOR_LINEARACCEL   - m/s^2
  imu::Vector<3> acce = bno055_sensor.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  
  String temp="";
  temp+=acce.x();
  temp+=","; 
  temp+=acce.y();
  temp+=",";
  temp+=acce.z();
  temp+=",";
  temp+=quat.w();
  temp+=",";
  temp+=quat.x();
  temp+=",";
  temp+=quat.y();
  temp+=",";
  temp+=quat.z();


  /*Send over serial bluetooth*/
  Serial1.println(temp);
  Serial.println(temp);
  delay(BNO055_SAMPLERATE_DELAY_MS);
}
