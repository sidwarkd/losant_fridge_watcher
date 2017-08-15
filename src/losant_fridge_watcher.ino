/*
 * Description: Simple firmware to report light and temperature data to the
                Particle Cloud as well as remotely trigger an attached buzzer.
 * Author: Kevin Sidwar
 * Date: August 11, 2017
 */

// Define the pin values for the attached components
int PHOTOCELL = A0;
int TMP36_SENSOR = A4;
int BUZZER = D3;

int soundTheAlarm(String data)
{
  // Sound the alarm for 3 seconds
  tone(BUZZER, 2551, 3000);
}

double getTemperatureInCelsius()
{
  // Translate the TMP36 voltage output to a temperature reading. Conversion
  // formula was found in the datasheet.
  int tmp36Value = analogRead(TMP36_SENSOR);
  return (tmp36Value * 0.0008 - 0.5) / 0.010;
}

// setup() runs once, when the device is first turned on.
void setup() {

  // Configure the pin connected to the photocell as an analog input
  pinMode(PHOTOCELL, INPUT);

  // Configure the pin connected to the TMP36 as an analog input
  pinMode(TMP36_SENSOR, INPUT);

  // Register the alarm function with the Particle Cloud
  Particle.function("alarm", soundTheAlarm);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  int lightIntensity;

  // Get the current light reading and publish it as a Particle event
  lightIntensity = analogRead(PHOTOCELL);
  Particle.publish("light-intensity", String(lightIntensity) , PRIVATE);

  // Publish a Particle event with temperature information
  Particle.publish("temp-reading", String(getTemperatureInCelsius()));
  delay(10000);
}
