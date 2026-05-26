#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_TEMPLATE_NAME "Industrial Monitoring"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "YourWiFiName";
char pass[] = "YourPassword";

// DHT setup
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ-2 pin
#define MQ2PIN A0

// Blynk virtual pins
#define VPIN_TEMP V0
#define VPIN_HUM  V1
#define VPIN_GAS  V2

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  dht.begin();
}

void loop()
{
  Blynk.run();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int gasValue = analogRead(MQ2PIN);

  // Print to Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Humidity: ");
  Serial.print(humidity);
  Serial.print(" % | Gas: ");
  Serial.println(gasValue);

  // Send data to Blynk
  Blynk.virtualWrite(VPIN_TEMP, temperature);
  Blynk.virtualWrite(VPIN_HUM, humidity);
  Blynk.virtualWrite(VPIN_GAS, gasValue);

  // Alert condition
  if (temperature > 40 || gasValue > 400)
  {
    Blynk.logEvent("alert", "Warning! High Temp or Gas Detected");
  }

  delay(2000);
}