#pragma once

namespace DallasTemperatureReader {

// Reads the first DS18B20 sensor on GPIO 25 and writes its Fahrenheit value to Serial.
void printReading();

}  // namespace DallasTemperatureReader
