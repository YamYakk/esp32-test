#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "DallasTemperatureReader.h"

namespace {
constexpr uint8_t kSdaPin = 21;
constexpr uint8_t kSclPin = 22;
constexpr float kHpaToInHg = 0.0295299830714f;

Adafruit_BME280 bme;
bool bmeFound = false;
}  // namespace

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("BOOT OK");

  Wire.begin(kSdaPin, kSclPin);
  bmeFound = bme.begin(0x76, &Wire) || bme.begin(0x77, &Wire);
}

void loop() {
  DallasTemperatureReader::printReading();

  if (!bmeFound) {
    Serial.println("BME280 NOT FOUND");
    delay(15000);
    return;
  }

  const float temperatureF = bme.readTemperature() * 9.0f / 5.0f + 32.0f;
  const float pressureInHg = (bme.readPressure() / 100.0f) * kHpaToInHg;

  Serial.print("The temp in shop is ");
  Serial.print(temperatureF, 1);
  Serial.print(" F and the pressure is ");
  Serial.print(pressureInHg, 2);
  Serial.println(" inHg.");
  delay(15000);
}
