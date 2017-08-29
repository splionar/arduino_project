/*-----( Import needed libraries )-----*/
#include <OneWire.h>
#include <DallasTemperature.h>

/*-----( Declare Constants )-----*/
#define ONE_WIRE_BUS_IN 2 /*-(Connect to Pin 2 )-*/
#define ONE_WIRE_BUS_OUT 4 /*-(Connect to Pin 4 )-*/

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWireIn(ONE_WIRE_BUS_IN);
OneWire ourWireOut(ONE_WIRE_BUS_OUT);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature sensorsIn(&ourWireIn);
DallasTemperature sensorsOut(&ourWireOut);

/*-----( Declare Variables )-----*/


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
}/*--(end setup )---*/


void loop() /*----( LOOP: RUNS CONSTANTLY )----*/
{
  Serial.println();
  Serial.print("Requesting temperature...");
  sensorsIn.requestTemperatures(); // Send the command to get temperatures
  sensorsOut.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  Serial.print("Device In = ");
  Serial.print(sensorsIn.getTempCByIndex(0));
  Serial.println(" Degrees C");

  Serial.print("Device Out = ");
  Serial.print(sensorsOut.getTempCByIndex(1));
  Serial.println(" Degrees C");

  delay(5000);
}/* --(end main loop )-- */

/* ( THE END ) */
