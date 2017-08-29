/*-----( Import needed libraries )-----*/
#include <SPI.h> //Load SPI library
#include <SD.h> //Load SD Library
#include <OneWire.h>
#include <DallasTemperature.h>

/*-----( Declare Constants )-----*/
#define ONE_WIRE_BUS_IN 2 /*-(Connect to Pin 2 )-*/
#define ONE_WIRE_BUS_OUT 4 /*-(Connect to Pin 4 )-*/

// for the data logging shield, define pin number for the SD cs line
const int chipSelect = 10; //Select pin 10

// Inizialitizing logging file
File SensorData;

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWireIn(ONE_WIRE_BUS_IN);
OneWire ourWireOut(ONE_WIRE_BUS_OUT);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensorsIn(&ourWireIn);
DallasTemperature sensorsOut(&ourWireOut);

/*-----( Declare Variables )-----*/
float sensor_in;
float sensor_out;

void setup() /*----( SETUP: RUNS ONCE )----*/
{
  /*-(start serial port to see results )-*/
  delay(1000);
  Serial.begin(9600);
  Serial.println("YourDuino.com: Temperature Sensor Test Program");
  Serial.println("Temperature Sensor: DS18B20");
  delay(1000);

  /*-( Start up the DallasTemperature library )-*/
  sensorsIn.begin();
  sensorsOut.begin();
  
  //setup SD card
   Serial.print("Initializing SD card...");

  // see if the SD card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  } //end if loop
  Serial.println("card initialized.");
  
}/*--(end setup )---*/

void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{
  Serial.println();
  Serial.print("Requesting temperature...");
  sensorsIn.requestTemperatures(); // Send the command to get temperatures
  sensorsOut.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  //Set variable values
  sensor_in = sensorsIn.getTempCByIndex(0);
  sensor_out = sensorsOut.getTempCByIndex(1);
  
  //Open file to log data in.
  SensorData = SD.open("datalog.txt", FILE_WRITE);
  
  if (SensorData){ //If SensorData = TRUE, print to serial monitor and log data to SensorData
  //Print to serial monitor
  Serial.print("Device In = ");
  Serial.print(sensor_in);
  Serial.println(" Degrees C");

  Serial.print("Device Out = ");
  Serial.print(sensor_out);
  Serial.println(" Degrees C");

  delay(5000);
  
  //Log to SD Card
  SensorData.print(sensor_in);
  SensorData.print(",");
  SensorData.println(sensor_out);
  }   //end if loop
  
}/* --(end main loop )-- */

/* ( THE END ) */
