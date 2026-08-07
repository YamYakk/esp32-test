#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>

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
  if (!bmeFound) {
    Serial.println("BME280 NOT FOUND");
    delay(2000);
    return;
  }

  const float temperatureF = bme.readTemperature() * 9.0f / 5.0f + 32.0f;
  const float humidity = bme.readHumidity();
  const float pressureInHg = (bme.readPressure() / 100.0f) * kHpaToInHg;

  Serial.print("BME280 FOUND  TEMP_F=");
  Serial.print(temperatureF, 1);
  Serial.print("  HUMIDITY_PCT=");
  Serial.print(humidity, 1);
  Serial.print("  PRESSURE_INHG=");
  Serial.println(pressureInHg, 2);
  delay(2000);
}
