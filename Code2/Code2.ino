#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>

#define SPEAKER_PIN 9 //9
#define SD_PIN 10
TMRpcm audio; 

void setup() {
  Serial.begin(9600);
  pinMode(SD_PIN, OUTPUT);
    digitalWrite(SD_PIN, HIGH);
  //ADUIO
    if (!SD.begin(SD_PIN)) {
      Serial.println("SD card initialization failed!");
    while (1);
    }
  audio.speakerPin = SPEAKER_PIN;
  audio.setVolume(5);
  audio.quality(1);
}

void loop() {
  audio.play("Red.wav");
}