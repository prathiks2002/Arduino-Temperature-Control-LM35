// elapsedMillis library needs to be installed
// .ZIP file downloaded from https://www.arduino.cc/reference/en/libraries/elapsedmillis/
#include <elapsedMillis.h>

// Define the LM35 temperature sensor pin
const int sensorPin = A0;    // LM35 temperature sensor connected to Analog pin A0

// Define the onboard LED pin
const int ledPin = 13;       // Onboard LED connected to digital pin 13

// Define the temperature threshold for LED control
const int temperatureThreshold = 30;

// Variables to store temperature readings and manage LED blinking
int temperature;
elapsedMillis ledBlinkTimer;

void setup() 
{
  
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() 
{
  
  // Read temperature from the LM35 sensor
  temperature = readTemperature();

  // Control LED based on temperature
  if (temperature < temperatureThreshold) 
  {
    blinkLED(250);  // Blink every 250 milliseconds
  } 
  else 
  {
    blinkLED(500);  // Blink every 500 milliseconds
  }
}

// Function to read temperature from the LM35 sensor
int readTemperature() 
{
  // Read analog value from the LM35 sensor
  int sensorValue = analogRead(sensorPin);

  // Convert analog value to voltage
  float voltage = (sensorValue / 1024.0) * 5.0;

  // Convert voltage to temperature in Celsius
  float temperatureC = (voltage - 0.5) * 100.0;

  // Print temperature to the Serial Monitor for debugging
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // Return the temperature value
  return temperatureC;
}

// Function to control the LED based on the specified interval
void blinkLED(int interval) 
{
  
  // Check if the specified interval has passed
  if (ledBlinkTimer >= interval) 
  {
    
    // Toggle the LED state
    digitalWrite(ledPin, !digitalRead(ledPin));

    // Reset the timer for the next interval
    ledBlinkTimer = 0;
  }
}
