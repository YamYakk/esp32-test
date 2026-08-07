# Project instructions

## Hardware
- Target board: esp32dev
- Upload port: /dev/ttyUSB0
- Serial baud: 115200

## Build
- Use: /home/ryan/.platformio/penv/bin/pio run

## Upload
- Use: /home/ryan/.platformio/penv/bin/pio run --target upload --upload-port /dev/ttyUSB0

## Serial monitor
- Use: /home/ryan/.platformio/penv/bin/pio device monitor -b 115200 -p /dev/ttyUSB0## Build


## Verification
After upload, monitor serial output and confirm:
- "BOOT OK"
- repeated "hello from esp32"

## Rules
- Make small changes
- Explain what changed
- Build after code edits
- Do not change board config unless needed
