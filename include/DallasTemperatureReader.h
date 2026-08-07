#pragma once

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

namespace DallasTemperatureReader {
namespace {
constexpr uint8_t kDallasPin = 25;
}  // namespace

// Reads every DS18B20 sensor on GPIO 25 and writes its Fahrenheit values to Serial.
inline void printReading() {
  static OneWire oneWire(kDallasPin);
  static DallasTemperature sensors(&oneWire);
  static bool initialized = false;

  if (!initialized) {
    sensors.begin();
    initialized = true;
  }

  const uint8_t deviceCount = sensors.getDeviceCount();
  if (deviceCount == 0) {
    Serial.println("DALLAS TEMP: SENSOR NOT FOUND");
    return;
  }

  sensors.requestTemperatures();
  for (uint8_t index = 0; index < deviceCount; ++index) {
    const float temperatureF = sensors.getTempFByIndex(index);
    Serial.print("DALLAS TEMP_");
    Serial.print(index + 1);
    Serial.print("_F=");

    if (temperatureF == DEVICE_DISCONNECTED_F) {
      Serial.println("READ FAILED");
      continue;
    }

    Serial.println(temperatureF, 1);
  }
}

}  // namespace DallasTemperatureReader
