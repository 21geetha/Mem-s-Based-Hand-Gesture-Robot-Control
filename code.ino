#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#define m1 D3
#define m11 D4
#define m2 D5
#define m22 D6

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void) {
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print("Sensor:       "); Serial.println(sensor.name);
  Serial.print("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void) {
  Serial.print("Data Rate:    "); 
  switch(accel.getDataRate()) {
    case ADXL345_DATARATE_3200_HZ: Serial.print("3200 "); break;
    case ADXL345_DATARATE_1600_HZ: Serial.print("1600 "); break;
    case ADXL345_DATARATE_800_HZ: Serial.print("800 "); break;
case ADXL345_DATARATE_400_HZ: Serial.print("400 "); break;
    case ADXL345_DATARATE_200_HZ: Serial.print("200 "); break;
    case ADXL345_DATARATE_100_HZ: Serial.print("100 "); break;
    case ADXL345_DATARATE_50_HZ: Serial.print("50 "); break;
    case ADXL345_DATARATE_25_HZ: Serial.print("25 "); break;
    case ADXL345_DATARATE_12_5_HZ: Serial.print("12.5 "); break;
    case ADXL345_DATARATE_6_25HZ: Serial.print("6.25 "); break;
    case ADXL345_DATARATE_3_13_HZ: Serial.print("3.13 "); break;
    case ADXL345_DATARATE_1_56_HZ: Serial.print("1.56 "); break;
    case ADXL345_DATARATE_0_78_HZ: Serial.print("0.78 "); break;
    case ADXL345_DATARATE_0_39_HZ: Serial.print("0.39 "); break;
    case ADXL345_DATARATE_0_20_HZ: Serial.print("0.20 "); break;
    case ADXL345_DATARATE_0_10_HZ: Serial.print("0.10 "); break;
    default: Serial.print("???? "); break;
  } 
  Serial.println(" Hz"); 
}

void displayRange(void) {
  Serial.print("Range:         +/- ");
  switch(accel.getRange()) {
    case ADXL345_RANGE_16_G: Serial.print("16 "); break;
    case ADXL345_RANGE_8_G: Serial.print("8 "); break;
    case ADXL345_RANGE_4_G: Serial.print("4 "); break;
    case ADXL345_RANGE_2_G: Serial.print("2 "); break;
    default: Serial.print("?? "); break;
  } 
  Serial.println(" g"); 
}

void setup(void) {
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
  if(!accel.begin()) {
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  accel.setRange(ADXL345_RANGE_16_G);
  displaySensorDetails();
  displayDataRate();
  displayRange();
  Serial.println("");

  pinMode(m1, OUTPUT);
  pinMode(m11, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m22, OUTPUT);
  stop1();
}

void loop(void) {
  sensors_event_t event; 
  accel.getEvent(&event);
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
 
  Serial.print("X: "); Serial.print(x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(z); Serial.print("  "); Serial.println("m/s^2 ");
  delay(500);

  if(y < -7) {
    forward();
  } else if(y > 7) {
    back();
  } else if(x < -7) {
    right();
  } else if(x > 7) {
    left();
  } else {
    stop1();
  }
}

void forward() {
  Serial.println("Forward");
  digitalWrite(m1, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m22, LOW);
}

void back() {
  Serial.println("Back");
  digitalWrite(m1, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m2, LOW);
  digitalWrite(m22, HIGH);
}

void left() {
  Serial.println("left");
  digitalWrite(m1, LOW);
  digitalWrite(m11, HIGH);
  digitalWrite(m2, HIGH);
  digitalWrite(m22, LOW);
}

void right() {
  Serial.println("right");
  digitalWrite(m1, HIGH);
  digitalWrite(m11, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m22, HIGH);
}

void stop1() {
  Serial.println("Stop");
  digitalWrite(m1, LOW);
  digitalWrite(m11, LOW);
  digitalWrite(m2, LOW);
  digitalWrite(m22, LOW);
}
