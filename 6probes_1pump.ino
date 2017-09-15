/*-----( Import needed libraries )-----*/
#include <SPI.h> //Load SPI library
#include <SD.h> //Load SD Library
#include <OneWire.h> //Load library for temperature sensing
#include <DallasTemperature.h> //Load library for temperature sensing
#include <RTClib.h> //Load library for RTC
#include <Wire.h> //Load library for RTC

/*-----( Declare Constants )-----*/
#define ONE_WIRE_BUS1 1 /*-(Connect to Pin 1 )-*/
#define ONE_WIRE_BUS2 2 /*-(Connect to Pin 2 )-*/
#define ONE_WIRE_BUS3 3 /*-(Connect to Pin 3 )-*/
#define ONE_WIRE_BUS4 4 /*-(Connect to Pin 4 )-*/
#define ONE_WIRE_BUS5 5 /*-(Connect to Pin 5 )-*/
#define ONE_WIRE_BUS6 6 /*-(Connect to Pin 6 )-*/
#define PUMP 9 /*-(Connect to Pin 9 )-*/

// for the data logging shield, define pin number for the SD cs line
const int chipSelect = 10; //Select pin 10

RTC_PCF8523 rtc; //Calling PCF8523 RTC

// Inizialitizing logging file
//File SensorData;

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWire1(ONE_WIRE_BUS1);
OneWire ourWire2(ONE_WIRE_BUS2);
OneWire ourWire3(ONE_WIRE_BUS3);
OneWire ourWire4(ONE_WIRE_BUS4);
OneWire ourWire5(ONE_WIRE_BUS5);
OneWire ourWire6(ONE_WIRE_BUS6);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensors1(&ourWire1);
DallasTemperature sensors2(&ourWire2);
DallasTemperature sensors3(&ourWire3);
DallasTemperature sensors4(&ourWire4);
DallasTemperature sensors5(&ourWire5);
DallasTemperature sensors6(&ourWire6);


/*-----( Declare Variables )-----*/
float sensor_1;
float sensor_2;
float sensor_3;
float sensor_4;
float sensor_5;
float sensor_6;
char timestamp[20];

void setup() /*----( SETUP: RUNS ONCE )----*/
{
  pinMode(PUMP, OUTPUT);
  analogWrite(PUMP, 200);
  /*-(start serial port to see results )-*/
  Serial.begin(9600);
  rtc.begin();
  //DateTime now = rtc.now();
  //sprintf(timestamp, "%02d/%02d/%02d %02d:%02d:%02d", now.day(), now.month(), now.year(),now.hour(), now.minute(), now.second());  
  //Serial.println("Temperature Sensor: DS18B20");
  //Serial.print("Start time: ");
  //Serial.println(timestamp);

  /*-( Start up the DallasTemperature library )-*/
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  sensors4.begin();
  sensors5.begin();
  sensors6.begin();
  
  //setup SD card
 // Serial.print("Initializing SD card...");

  // see if the SD card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } //end if loop
  //Serial.println("card initialized.");

  File SensorData = SD.open("test.txt", FILE_WRITE);
  
  if (SensorData){ //If SensorData = TRUE, print to serial monitor and log data to SensorData
    //Log to SD Card
    SensorData.print("Time stamp");
    SensorData.print(",");
    SensorData.print("Temperature 1");
    SensorData.print(",");
    SensorData.print("Temperature 2");
    SensorData.print(",");
    SensorData.print("Temperature 3");
    SensorData.print(",");
    SensorData.print("Temperature 4");
    SensorData.print(",");
    SensorData.print("Temperature 5");
    SensorData.print(",");
    SensorData.println("Temperature 6");
    SensorData.close();
  }   //end if
  //else
  //{
  //  Serial.println("There is an error in initializing .txt file");
 // }
  
}/*--(end setup )---*/

void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{
  //Serial.println();
  //Serial.print("Requesting temperature...");
  sensors1.requestTemperatures(); // Send the command to get temperatures
  sensor_1 = sensors1.getTempCByIndex(0);
  sensors2.requestTemperatures(); // Send the command to get temperatures
  sensor_2 = sensors2.getTempCByIndex(0);
  sensors3.requestTemperatures(); // Send the command to get temperatures
  sensor_3 = sensors3.getTempCByIndex(0);
  sensors4.requestTemperatures(); // Send the command to get temperatures
  sensor_4 = sensors4.getTempCByIndex(0);
  sensors5.requestTemperatures(); // Send the command to get temperatures
  sensor_5 = sensors5.getTempCByIndex(0);
  sensors6.requestTemperatures(); // Send the command to get temperatures
  sensor_6 = sensors6.getTempCByIndex(0);
  Serial.println("DONE");

  DateTime now = rtc.now();
  sprintf(timestamp, "%02d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(),now.hour(), now.minute(), now.second());  
  //Set variable values  
  
  //Open file to log data in.
  File SensorData = SD.open("test.txt", FILE_WRITE);
  
  if (SensorData){ //If SensorData = TRUE, print to serial monitor and log data to SensorData
    //Print to serial monitor
    Serial.print(timestamp);
    Serial.print(",");
    Serial.print(sensor_1);
    Serial.print(",");
    Serial.print(sensor_2);
    Serial.print(",");
    Serial.print(sensor_3);
    Serial.print(",");
    Serial.print(sensor_4);
    Serial.print(",");
    Serial.print(sensor_5);
    Serial.print(",");
    Serial.println(sensor_6);

    //Log to SD Card
    Serial.print("Logging to SD Card...");
    SensorData.print(timestamp);
    SensorData.print(",");
    SensorData.print(sensor_1);
    SensorData.print(",");
    SensorData.print(sensor_2);
    SensorData.print(",");
    SensorData.print(sensor_3);
    SensorData.print(",");
    SensorData.print(sensor_4);
    SensorData.print(",");
    SensorData.print(sensor_5);
    SensorData.print(",");
    SensorData.println(sensor_6);
    SensorData.close();
    Serial.println("DONE");

    delay(2000);
  }   //end if loop
 // else
 // {
 //   Serial.println("There is an error in initializing .txt file");
 // }
  
}/* --(end main loop )-- */

/* ( THE END ) */
