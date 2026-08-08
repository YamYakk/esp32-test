#pragma once

#include <Arduino.h>

namespace A02YYUWReader {
namespace {
constexpr uint8_t kRxPin = 16;
constexpr unsigned long kBaudRate = 9600;
constexpr uint8_t kFrameHeader = 0xFF;

inline HardwareSerial& serialPort() {
  static HardwareSerial sensorSerial(2);
  return sensorSerial;
}

// The A02YYUW sends: 0xFF, distance MSB, distance LSB, checksum.
inline bool readDistanceMm(uint16_t& distanceMm) {
  static uint8_t frame[4];
  static uint8_t frameIndex = 0;

  while (serialPort().available()) {
    const uint8_t byteRead = static_cast<uint8_t>(serialPort().read());

    if (frameIndex == 0) {
      if (byteRead == kFrameHeader) {
        frame[frameIndex++] = byteRead;
      }
      continue;
    }

    frame[frameIndex++] = byteRead;
    if (frameIndex < sizeof(frame)) {
      continue;
    }

    frameIndex = 0;
    const uint8_t checksum = static_cast<uint8_t>(frame[0] + frame[1] + frame[2]);
    if (checksum != frame[3]) {
      continue;
    }

    distanceMm = (static_cast<uint16_t>(frame[1]) << 8) | frame[2];
    return true;
  }

  return false;
}
}  // namespace

// Starts UART2 with the sensor's white TX wire connected to GPIO 16.
inline void begin() {
  serialPort().begin(kBaudRate, SERIAL_8N1, kRxPin, -1);
}

// Prints the newest valid distance frame received since the prior call, in mm.
inline void printReading() {
  uint16_t distanceMm = 0;
  bool receivedFrame = false;

  while (readDistanceMm(distanceMm)) {
    receivedFrame = true;
  }

  if (!receivedFrame) {
    Serial.println("A02YYUW: NO VALID DATA");
    return;
  }

  Serial.print("A02YYUW_DISTANCE_MM=");
  Serial.println(distanceMm);
}
}  // namespace A02YYUWReader
