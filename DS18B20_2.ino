/*-----( Import needed libraries )-----*/
#include <SPI.h> //Load SPI library
#include <SD.h> //Load SD Library
#include <OneWire.h> //Load library for temperature sensing
#include <DallasTemperature.h> //Load library for temperature sensing
#include <RTClib.h> //Load library for RTC
#include <Wire.h> //Load library for RTC

/*-----( Declare Constants )-----*/
#define ONE_WIRE_BUS_IN 2 /*-(Connect to Pin 2 )-*/
#define ONE_WIRE_BUS_OUT 4 /*-(Connect to Pin 4 )-*/
#define ONE_WIRE_BUS_AMB 6 /*-(Connect to Pin 6 )-*/

// for the data logging shield, define pin number for the SD cs line
const int chipSelect = 10; //Select pin 10

RTC_PCF8523 rtc; //Calling PCF8523 RTC

// Inizialitizing logging file
//File SensorData;

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWireIn(ONE_WIRE_BUS_IN);
OneWire ourWireOut(ONE_WIRE_BUS_OUT);
OneWire ourWireAmb(ONE_WIRE_BUS_AMB);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensorsIn(&ourWireIn);
DallasTemperature sensorsOut(&ourWireOut);
DallasTemperature sensorsAmb(&ourWireAmb);

/*-----( Declare Variables )-----*/
float sensor_in;
float sensor_out;
float sensor_amb;
char timestamp[20];

void setup() /*----( SETUP: RUNS ONCE )----*/
{
  /*-(start serial port to see results )-*/
  Serial.begin(9600);
  rtc.begin();
  DateTime now = rtc.now();
  sprintf(timestamp, "%02d/%02d/%02d %02d:%02d:%02d", now.day(), now.month(), now.year(),now.hour(), now.minute(), now.second());  
  Serial.println("Temperature Sensor: DS18B20");
  Serial.print("Start time: ");
  Serial.println(timestamp);

  /*-( Start up the DallasTemperature library )-*/
  sensorsIn.begin();
  sensorsOut.begin();
  sensorsAmb.begin();
  
  //setup SD card
  Serial.print("Initializing SD card...");

  // see if the SD card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } //end if loop
  Serial.println("card initialized.");

  File SensorData = SD.open("test.txt", FILE_WRITE);
  
  if (SensorData){ //If SensorData = TRUE, print to serial monitor and log data to SensorData
    //Log to SD Card
    SensorData.print("Time stamp");
    SensorData.print(",");
    SensorData.print("Internal Temperature");
    SensorData.print(",");
    SensorData.println("Surface Temperature");
    SensorData.print(",");
    SensorData.println("Ambient Temperature");
    SensorData.close();
  }   //end if
  else
  {
    Serial.println("There is an error in initializing .txt file");
  }
  
}/*--(end setup )---*/

void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{
  Serial.println();
  Serial.print("Requesting temperature...");
  sensorsIn.requestTemperatures(); // Send the command to get temperatures
  sensorsOut.requestTemperatures(); // Send the command to get temperatures
  sensorsAmb.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  DateTime now = rtc.now();
  sprintf(timestamp, "%02d/%02d/%02d %02d:%02d:%02d", now.day(), now.month(), now.year(),now.hour(), now.minute(), now.second());  
  //Set variable values
  sensor_in = sensorsIn.getTempCByIndex(0);
  sensor_out = sensorsOut.getTempCByIndex(1);
  sensor_amb = sensorsAmb.getTempCByIndex(2);
  
  //Open file to log data in.
  File SensorData = SD.open("test.txt", FILE_WRITE);
  
  if (SensorData){ //If SensorData = TRUE, print to serial monitor and log data to SensorData
    //Print to serial monitor
    Serial.print("Date/Time : ");
    Serial.println(timestamp);
    
    Serial.print("Internal = ");
    Serial.print(sensor_in);
    Serial.println(" Degrees C");

    Serial.print("Surface = ");
    Serial.print(sensor_out);
    Serial.println(" Degrees C");
    
    Serial.print("Ambient = ");
    Serial.print(sensor_amb);
    Serial.println(" Degrees C");
  
    delay(1000);
  
    //Log to SD Card
    Serial.print("Logging to SD Card...");
    SensorData.print(timestamp);
    SensorData.print(",");
    SensorData.print(sensor_in);
    SensorData.print(",");
    SensorData.println(sensor_out);
    SensorData.print(",");
    SensorData.println(sensor_amb);
    SensorData.close();
    Serial.println("DONE");
  }   //end if loop
  else
  {
    Serial.println("There is an error in initializing .txt file");
  }
  
}/* --(end main loop )-- */

/* ( THE END ) */
