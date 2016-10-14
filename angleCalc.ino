#include<Wire.h>
const int MPU_addr=0x68;
double AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //These will be the raw data from the MPU6050.
uint32_t timer; //it's a timer, saved as a big-ass unsigned int.  We use it to save times from the "micros()" command and subtract the present time in microseconds from the time stored in timer to calculate the time for each loop.
double compAngleX, compAngleY; //These are the angles in the complementary filter
#define degconvert 57.2957786 //there are like 57 degrees in a radian.
double angleYaw = 0.0;
int counter = 0;
void setup() {
  Wire.begin();
  #if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
  #else
    TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
  #endif
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  delay(100);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  double roll = atan2(AcY, AcZ)*degconvert;
  double pitch = atan2(-AcX, AcZ)*degconvert;
  double gyroXangle = roll;
  double gyroYangle = pitch;
  double compAngleX = roll;
  double compAngleY = pitch;
  timer = micros();
}

void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); 
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read();  
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  Tmp=Wire.read()<<8|Wire.read();  
  GyX=Wire.read()<<8|Wire.read();  
  GyY=Wire.read()<<8|Wire.read(); 
  GyZ=Wire.read()<<8|Wire.read(); 
  double dt = (double)(micros() - timer) / 1000000; 
  timer = micros(); 
  double roll = atan2(AcY, AcZ)*degconvert;
  double pitch = atan2(-AcX, AcZ)*degconvert;
  double gyroXrate = GyX/131.0;
  double gyroYrate = GyY/131.0;
  double gyroZrate = GyZ/131.0;
  //if the angular accalaration is too small, we consider it as a noise, and do no update
  if(abs(gyroZrate)<1){
      gyroZrate = 0;
    }
    
  angleYaw = angleYaw + gyroZrate*dt;
  compAngleX = 0.99 * (compAngleX + gyroXrate * dt) + 0.01 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.99 * (compAngleY + gyroYrate * dt) + 0.01 * pitch; 
  Serial.print(compAngleX);Serial.print("\t");
  Serial.print(angleYaw);Serial.print("\t");
  Serial.print(compAngleY);Serial.print("\n");
  //on the robot, don't use the counter, instead, set the angle to 0 before every move.
  counter ++;
  if(counter%1000 == 0){
//    angleYaw = 0;
    }
  //after each move, compare the angle againest the intended value and do adjustments.
   
}
