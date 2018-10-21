// NASA Spase Apps challenge 2018
// Command: Interstellar Dolphin
// Challange: Make Sense out of Mars
// v0.1

#include<Wire.h>
const int MPU=0x68; 
int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2;
 
long duration_HC1; // Duration of the impulse
long duration_HC2; // Duration of the impulse

int HC1_Trig ;
int HC1_Echo ; 
int HC2_Trig ;
int HC2_Echo ;

long iter;

void setup() {
  
  // Ultra Sonic Sensor 1
  // Port 3 - Trigger
  // Port 4 - Echo

  // VCC -> 5V
  // Trig -> Port 3
  // Echo -> Port 4

  HC1_Trig = 3;
  HC1_Echo = 4;

  HC2_Trig = 5;
  HC2_Echo = 6;

  pinMode(HC1_Trig, OUTPUT);
  pinMode(HC1_Echo, INPUT);

  pinMode(HC2_Trig, OUTPUT);
  pinMode(HC2_Echo, INPUT);

  // Initialization of the Serial Port
  Serial.begin(9600);

  // Position sensor 1
  // VCC -> 3.3 V/ 5V (better)
  // GND -> GND
  // SCL -> A5
  // SDA -> A4
  // XDA -> 
  // XCL ->
  // ADO -> 10
  // INT ->

  // Position sensor 2
  // VCC -> 3.3 V/ 5V (better)
  // GND -> GND
  // SCL -> A3
  // SDA -> A2
  // XDA -> 
  // XCL ->
  // ADO -> 11
  // INT ->

  pinMode(10, OUTPUT); // sensor 1
  pinMode(11, OUTPUT); // sensor 2

  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  // Init Trigger
  digitalWrite(HC1_Trig, LOW);
  digitalWrite(HC2_Trig, LOW);

  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  delayMicroseconds(2);
  
  // Begin measurement
  digitalWrite(HC1_Trig, HIGH);
  digitalWrite(HC2_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(HC1_Trig, LOW);
  digitalWrite(HC2_Trig, LOW);

  // Measure Pulse on Echo
  duration_HC1 = pulseIn(HC1_Echo, HIGH);
  duration_HC2 = pulseIn(HC2_Echo, HIGH);
  //mm = duration/(2.924*2.0);

  // Measure position data sensor 1
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX1 = Wire.read()<<8|Wire.read();    
  AcY1 = Wire.read()<<8|Wire.read();  
  AcZ1 = Wire.read()<<8|Wire.read();  
  GyX1 = Wire.read()<<8|Wire.read();  
  GyY1 = Wire.read()<<8|Wire.read();  
  GyZ1 = Wire.read()<<8|Wire.read();

  // Measure position data sensor 2
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  delayMicroseconds(2);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX2 = Wire.read()<<8|Wire.read();    
  AcY2 = Wire.read()<<8|Wire.read();  
  AcZ2 = Wire.read()<<8|Wire.read();  
  GyX2 = Wire.read()<<8|Wire.read();  
  GyY2 = Wire.read()<<8|Wire.read();  
  GyZ2 = Wire.read()<<8|Wire.read();

  // Write to Serial Port
  Serial.print(duration_HC1); Serial.print(" ");
  Serial.print(duration_HC2); Serial.print(" ");

  // Accelerometer data
  Serial.print(AcX1); Serial.print(" "); // X
  Serial.print(AcY1); Serial.print(" "); // Y
  Serial.print(AcZ1); Serial.print(" "); // Z
  
  // Gyroscope data
  Serial.print(GyX1); Serial.print(" "); // X
  Serial.print(GyY1); Serial.print(" "); // Y
  Serial.print(GyZ1); Serial.print(" "); // Z

    // Accelerometer data
  Serial.print(AcX2); Serial.print(" "); // X
  Serial.print(AcY2); Serial.print(" "); // Y
  Serial.print(AcZ2); Serial.print(" "); // Z
  
  // Gyroscope data
  Serial.print(GyX2); Serial.print(" "); // X
  Serial.print(GyY2); Serial.print(" "); // Y
  Serial.print(GyZ2);                    // Z

  Serial.println();

  // Pause 100 ms = 0.1 s 
  delay(100);
}
