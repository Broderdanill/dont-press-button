# Random Sound Button

## Overview

This project is a single big red button that plays a random MP3 sound every time you press it. It uses an Arduino Nano and a DFPlayer Mini MP3 module.

---

## Parts List

* Arduino Nano (ATmega328P)
* DFPlayer Mini (MP3‑TF‑16P)
* MicroSD card (FAT32)
* 8Ω passive speaker
* Arcade push button with LED
* 1 kΩ resistor (for DFPlayer RX)
* 220–330 Ω resistor (for button LED)
* Dupont jumper wires
* USB cable (for power + programming)

---

## SD Card Setup

1. Format SD card as FAT32
2. Create folder: `/MP3`
3. Add files: `0001.mp3`, `0002.mp3`, ...

---

## Wiring

```text
Arduino Nano                 DFPlayer Mini
------------                 --------------
5V  -----------------------> VCC
GND -----------------------> GND
D10 --[1kΩ]----------------> RX
D11 -----------------------> TX

Speaker:
SPK1 ----------------------> +
SPK2 ----------------------> -

Button:
NO  ----------------------> D2
COM ----------------------> GND

Button LED:
5V --[220–330Ω]-----------> LED+
GND ----------------------> LED-
```

### DFPlayer

* VCC → Arduino 5V
* GND → Arduino GND
* RX → Arduino D10 via 1kΩ resistor
* TX → Arduino D11
* SPK1 → Speaker +
* SPK2 → Speaker −

### Button

* COM → Arduino GND
* NO → Arduino D2

### Button LED

* LED+ → Arduino 5V via 220–330 Ω
* LED− → Arduino GND

---

## Software

Upload the provided Arduino sketch (.ino) to the Nano.
The code:

* Reads how many MP3 files exist
* Randomizes playback
* Avoids repeating the same sound twice in a row

---

## Usage

1. Power the device via USB
2. Wait for startup
3. Press the button to play a random sound

---

## Notes

* If uploading fails, disconnect DFPlayer RX/TX during upload
* Files must be correctly numbered for DFPlayer

---

Enjoy your Random Sound Button!
