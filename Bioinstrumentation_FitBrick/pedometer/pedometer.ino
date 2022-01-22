// Based on basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float x_acc = 0;
float y_acc = 0;
float z_acc = 0;
float x_jer = 0;
float y_jer = 0;
float z_jer = 0;
float step_vec = 0;
int steps = 0;
void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  step_vec = sqrt(pow(x_jer,2)+pow(z_jer,2));

  if (step_vec>3 && z_jer*((a.acceleration.z - z_acc)/0.4)<-4)
    {
      steps = steps + 1;
    }
  
  x_jer = (a.acceleration.x - x_acc)/0.4;
  y_jer = (a.acceleration.y - y_acc)/0.4;
  z_jer = (a.acceleration.z - z_acc)/0.4;
    /* Print out the values */
  x_acc = a.acceleration.x;
  y_acc = a.acceleration.y;
  z_acc = a.acceleration.z;

  /*
  step_vec = sqrt(pow(x_jer,2)+pow(z_jer,2));
  Serial.print("x: ");
  Serial.println(a.acceleration.x);
  Serial.print("y: ");
  Serial.println(a.acceleration.y);
  Serial.print("z: ");
  Serial.println(a.acceleration.z);
  Serial.print("Vector: ");
  Serial.print(sqrt(pow(a.acceleration.x,2)+pow(a.acceleration.y,2)+pow(a.acceleration.z,2)));
  */
  /*
  Serial.print("x: ");
  Serial.println(x_jer);
  Serial.print("y: ");
  Serial.println(y_jer);
  Serial.print("z: ");
  Serial.println(z_jer);
  Serial.print("Vector: ");
  Serial.print(sqrt(pow(x_jer,2)+pow(z_jer,2)));
 */
  Serial.println(steps);
  delay(400);
}
