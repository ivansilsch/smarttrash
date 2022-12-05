#include "proyectoIOT.h";

void loop_local(void * params);
void loop_remote(void * params);

void setup() {
  Serial.begin(115200);

  // Inicia todos los sensores y actuadores
  _rtc.RTC_init();
  micro_sd.microSD_init();
  ultrasonic.Ultrasonic_init();
  my_servo.Servo_init();
  buzzer.Buzzer_init();
  screen.LCD_init();
  flame.Flame_init();
  inclination.Inclination_init();
  fan_motor.FanMotor_init();

  // Inicia el programa del 1er nucleo

  xTaskCreatePinnedToCore(loop_local, "loop_local", 10000, NULL, 1, NULL, 0);

  // Inicia wifi y mqtt
  mqtt_client.WIFI_init();
  mqtt_client.MQTT_init();
  web.Web_init();

  // Inicia el programa del 2do nucleo
  xTaskCreatePinnedToCore(loop_remote, "loop_remote", 10000, NULL, 1, NULL, 1);

}




void loop_local(void * params) {
  /*
    Loop que se ejecuta en el 1er nucleo.
    Es usado para realizar acciones locales con el esp32.
    No depende de conexiones a internet.
  */
	for( ;; ) {
    tsk.SCREEN_toggle_sequence(3000); //Decide si mostrar el tiempo o los sensores 
    tsk.SCREEN_PRINT_setInterval(1000);    //Tarea 3, imprime en lcd cada n milisegundos

    tsk.current_millis = millis();
    buzzer.current_millis = millis();

    // obtencion de los valores de los sensores 
    ultrasonic.calculate_object_distance();
    flame.update();
    inclination.update();
  
    buzzer.stop_if_time_is_over(); // Silencia el buzzer

    if (ultrasonic.distanceCm < 10 && ultrasonic.distanceCm > 0) {
      //Desactiva el temporizador de cierre si detecta un objeto para evitar que se cierre
      tsk.is_close_timeout_active = false;

      if (!my_servo.is_open) {
        // Abre la tapa
        my_servo.open_top();
        tsk.save_and_publish_setInterval(10000);
      } 

    } else if (ultrasonic.distanceCm > 50 && my_servo.is_open) {
      // Activa el temporizador de cierre cuando no hay un objeto cerca
      tsk.CloseTimeout_activate();
    }

    // tsk.CloseTimeout_print_state(); // debugging
    tsk.CloseTimeout_disable_if_time_ended();


    if (inclination.is_active) {
      tsk.PLAY_BUZZER_setInterval(500);
      tsk.save_and_publish_setInterval(10000);
    }

    if (flame.is_active) {
      tsk.PLAY_BUZZER_setInterval(500); 
      tsk.save_and_publish_setInterval(10000);
      my_servo.open_top();
      fan_motor.on();
    } else {
      fan_motor.off();
    }


	}
}




void loop_remote(void * params) {
  /*
    Loop que se ejecuta en el 2do nucleo.
    Es usado para realizar acciones sobre una conexion wifi que es propensa a desconexiones.
  */
	for( ;; ) {

    if (!mqtt.connected()) {
      mqtt_client.MQTT_reconnect();
    }
    // "Listener" para manejar datos entrantes de un cliente mqtt mediante la funcion "callback"
    mqtt.loop();

	}
}

void loop() {}
