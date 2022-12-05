class Task {
  public:
    unsigned long long is_close_timeout_active = false;
    unsigned long long close_timeout = 0;
        
    unsigned long long task1_millis = 0;
    unsigned long long task2_millis = 0;
    unsigned long long task3_millis = 0;
    unsigned long long toggle_millis = 0;
  
    unsigned long long current_millis = 0;
  public:
    void CloseTimeout_activate(void);
    void CloseTimeout_disable_now(void);
    void CloseTimeout_disable_if_time_ended(void);
    void CloseTimeout_print_state(void);

    void SCREEN_PRINT_setInterval(int ms);
    void SCREEN_toggle_sequence(int ms);
    void PLAY_BUZZER_setInterval(int ms);
    void save_and_publish_setInterval(int ms);
};


void Task::CloseTimeout_activate(void) {
  if (!is_close_timeout_active) {
    is_close_timeout_active = true;           // Activa el temporizador para cerrar la tapa
    close_timeout = current_millis + 3000;    // Establece el tiempo para usar en un futuro
  }
}


void Task::CloseTimeout_disable_if_time_ended(void) {
  if (is_close_timeout_active) {
    if (current_millis > close_timeout) {
      // Cierra la tapa
      my_servo.close_top();
      
      // Desactiva el temporizador de cierre
      is_close_timeout_active = false;    
      close_timeout = 0;
    }
  }
}


// void Task::CloseTimeout_print_state(void) {
//   Serial.print("open: ");
//   Serial.print(my_servo.is_open);
//   Serial.print("    millis: ");
//   Serial.print(current_millis);
//   Serial.print("    timeout: ");
//   Serial.print(close_timeout);
//   Serial.print("    is_close_timeout_active: ");
//   Serial.print(is_close_timeout_active);
//   Serial.print("    task3_millis: ");
//   Serial.println((task3_millis/1000)*1000);
// }


void Task::save_and_publish_setInterval(int ms) {
  if ( current_millis - task1_millis >= ms ) {

    micro_sd.microSD_save();
    if (mqtt.connected()) {
      char buffer[256];     // Aqui se guarda el json
      _rtc.RTC_set_time();  
      _rtc.RTC_set_date();
      _rtc.RTC_format_time();
      _rtc.RTC_format_date("-");
      StaticJsonDocument<256> json = micro_sd.global_state_to_JSON();    
      size_t n = serializeJson( json, buffer );     // Guarda el json en una cadena de caracteres
      mqtt.publish("smart_trash/client", buffer, n);
    }

    task1_millis = current_millis;
  }  
}


//Decide si mostrar el tiempo o los sensores 
void Task::SCREEN_toggle_sequence(int ms) {
  // unsigned long long cm = (current_millis/1000)*1000;
  // if (cm % (ms * 2) < ms) {
  //   screen.show_state = true;
  // } else {
  //   screen.show_state = false;
  // }
  if (current_millis - toggle_millis >= ms) {
    screen.show_state = !screen.show_state;
  }
}


void Task::SCREEN_PRINT_setInterval(int ms) {
  if ( current_millis - task2_millis >= ms ) {
    screen.LCD_print();
    task2_millis = current_millis;
  }
}


void Task::PLAY_BUZZER_setInterval(int ms) {
  if ( current_millis - task3_millis >= ms ) {
    buzzer.play(200);
    task3_millis = current_millis;
  }
}