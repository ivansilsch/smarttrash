# Smart Trash
A trash bin controlled by a servomotor over MQTT protocol to send commands to be opened or closed. It sends the state of the sensors when they're activated and save it to an SD card as JSON, and it serves a web server to visualize that history and a "waste management team" could be notified.

This is a project developed to learn the basics of IoT for the IoT subject at school, and some of its capabilities doesn't make sense.

It was developed with the ESP32 DEV Module board and the Arduino API.
### Sensors 
* Obstacles FC-51 - To detect if a hand is close to the bin.
* Inclination Sw520d - To detect if the bin fell.
* Flame Hl01 (For accomplish the assignment) - To detect fire.
### Actuators: 
* Servomotor. For opening and closing the bin. 
* Buzzer. Emit an intermiten sound in case a flame is detected or the bin is inclinated.
* Mini Motor DC (For accomplish the assignment) - It acts as an air fan.
### Modules
* RTC32321 - To get the current date and time.
* Display LCD 16x2 I2C - To print the sensors values.
* Micro Sd Card reader. To save the sensor values.

```sh
# Compiling the program to the board
arduino-cli compile -u -b esp32:esp32:esp32 -p /dev/ttyUSB0 --config 115200

# Monitoring the board
arduino-cli monitor -p /dev/ttyUSB0 --config 115200
```
