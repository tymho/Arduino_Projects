const int chipSelect = 4;
int sumclean = 0;
int avgclean = 0;
int sumdirt = 0;
int avgdirt = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  String dataStringclean = "";
  String dataStringdirt = "";

  delay(100);
  int sensorValue0 = analogRead(A0);
  float voltage0 = sensorValue0 * (5.0 / 1023.0);   // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  int sensorValue1 = analogRead(A1);
  float voltage1 = sensorValue1 * (5.0 / 1023.0);
  int sensorValue2 = analogRead(A2);
  float voltage2 = sensorValue2 * (5.0 / 1023.0);
  int sensorValue3 = analogRead(A3);
  float voltage3 = sensorValue3 * (5.0 / 1023.0);
  int sensorValue4 = analogRead(A4);
  float voltage4 = sensorValue4 * (5.0 / 1023.0);
  int sensorValue5 = analogRead(A5);
  float voltage5 = sensorValue5 * (5.0 / 1023.0);
  int sensorValue6 = analogRead(A6);
  float voltage6 = sensorValue6 * (5.0 / 1023.0);
  float avgclean = (voltage0+voltage1+voltage2) / 3;
  float avgdirt = (voltage3+voltage4+voltage5) / 3;
  dataStringclean += String(avgclean)
  dataStringdirt += String(avgdirt)
}
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataStringclean);
    dataFile.println(dataStringdirt);    
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataStringclean);
    Serial.println(dataStringdirt);
    
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
