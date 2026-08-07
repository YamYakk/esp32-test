#include "DallasTemperatureReader.h"

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>

namespace DallasTemperatureReader {
namespace {
constexpr uint8_t kDallasPin = 25;

OneWire oneWire(kDallasPin);
DallasTemperature sensors(&oneWire);
bool initialized = false;
}  // namespace

void printReading() {
  if (!initialized) {
    sensors.begin();
    initialized = true;
  }

  if (sensors.getDeviceCount() == 0) {
    Serial.println("DALLAS TEMP: SENSOR NOT FOUND");
    return;
  }

  sensors.requestTemperatures();
  const float temperatureF = sensors.getTempFByIndex(0);
  if (temperatureF == DEVICE_DISCONNECTED_F) {
    Serial.println("DALLAS TEMP: READ FAILED");
    return;
  }

  Serial.print("DALLAS TEMP_F=");
  Serial.println(temperatureF, 1);
}

}  // namespace DallasTemperatureReader
