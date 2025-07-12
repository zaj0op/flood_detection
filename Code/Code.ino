#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>
#define SPEAKER_PIN 9  
#define SD_PIN 10
TMRpcm audio; 
int trigPin = 2;    // TRIG pin
int echoPin = 3; 
long duration;
int distanceCm;

void setup() {
  // begin serial port
  Serial.begin (9600);
  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  // microSD module
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
  //LEDs
  pinMode(6, OUTPUT); //Relay1 IN1 BLUE LED
  pinMode(7, OUTPUT); //Relay1 IN2 YELLOW LED
  pinMode(8, OUTPUT); //Relay2 IN1 RED LED

}

void loop() {
  // SENSOR
  // begin serial port
  Serial.begin (9600);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;
  Serial.print("distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");
  delay(500);
  
  // IF ELSE
if (distanceCm <= 4) {
    redLight();
    audioRed();
  }
  else if(distanceCm >= 4 && distanceCm <= 8){
    yellowLight();
    audioYellow();
  }
  else if(distanceCm >= 8 && distanceCm <= 12){
    blueLight();
    audioBlue();
  }
  else{
    offLight();
  }
}

//LIGHT
void offLight(){
  digitalWrite(6, HIGH); 
  digitalWrite(7, HIGH); 
  digitalWrite(8, HIGH);
}
void blueLight(){ 
  digitalWrite(6, LOW); 
  digitalWrite(7, HIGH); 
  digitalWrite(8, HIGH);
}
void yellowLight(){
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}
void redLight(){
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

  //AUDIO
  void audioBlue(){
    if (!audio.isPlaying()) {
    audio.play("Blue.wav");
    }
  } 
  void audioYellow(){
    if (!audio.isPlaying()) {
    audio.play("Yellow.wav");
    }
  }
  void audioRed(){
    if (!audio.isPlaying()) {
    audio.play("Red.wav");
    }
  }