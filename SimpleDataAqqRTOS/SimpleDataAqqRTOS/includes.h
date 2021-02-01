#include <Nextion.h>
#include <NexNumber.h>
#include <NexButton.h>
#include <NexText.h>
#include <NexPicture.h>
#include <NexTouch.h>
#include <NexHotspot.h>
#include <NexWaveform.h>
#include <Servo.h>
#include <SFM4200CORE.h>
#include <Adafruit_ADS1015.h>
#include <Wire.h>

SFM4200CORE senseFlow(0x40);
Adafruit_ADS1115 ads(0x48);
Servo motor;
