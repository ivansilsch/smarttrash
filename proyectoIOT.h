// Serializador de JSON
#include <ArduinoJson.h>


// Servomotor
#include <Servo.h>    // Libreria que gestiona el servomotor
Servo servo;
#define SERVO_PIN 16
#include "MyServo.h"  // Interface para abrir la tapa
MyServo my_servo;


// Sensor de flama
#define FLAME_PIN 35
#include "Flame.h"
FlameSensor flame;


// Sensor de inclinacion
#define INCLINATION_PIN 34
#include "Inclination.h"
Inclination inclination;


// Componentes del reloj RTC-3231
#include <RTClib.h>     // Libreria que gestiona el reloj de tiempo real
RTC_DS3231 rtc;
#include "RTC.h"
RTC _rtc;


// Componentes micro sd
#include <SPI.h>        // Libreria de control para la micro SD SDHC.
#include <SD.h>         // Libreria del protocolo SPI.
#define MICROSD_PIN 5
File File_SD;
#include "MicroSD.h"
Micro_SD micro_sd;


// Sensor ultrasonico
#define TRIG_PIN 32
#define ECHO_PIN 33
#define SOUND_SPEED 0.034 // velocidad del sonido en cm/uS
#include "Ultrasonic.h"
Ultrasonic ultrasonic;


// Pantalla LCD
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "Screen.h"
LCD screen;


// Buzzer
#define BUZZER_PIN 17
#include "Buzzer.h"
Buzzer buzzer;


#define FAN_MOTOR_PIN 3
#include "FanMotor.h"
FanMotor fan_motor;


// Wifi y MQTT
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);


// Tareas / sensores y actuadores
#include "Task.h"
Task tsk;


#include "MQTT_MSG_Handler.h"   // Funcion manejadora de mensajes entrantes mqtt
#include "MQTT.h"
MQTTClient mqtt_client;


// Servidor web
WiFiServer web_server(80);
#include "Web.h"
Web web;
