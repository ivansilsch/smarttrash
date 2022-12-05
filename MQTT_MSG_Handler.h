void run_action_from_message(String message) {
  Serial.println(message);
  StaticJsonDocument<256> json;
  deserializeJson(json, message);

  // Elije que hacer dependiendo de los datos del mensaje enviado
  if (!json["is_open"]) {
    // Desactiva el temporizador de cierre
    tsk.is_close_timeout_active = false;    
    tsk.close_timeout = 0; 
    // Cierra la tapa
    my_servo.close_top();

  }  else {
    //Desactiva el temporizador de cierre si detecta un objeto para evitar que se cierre
    tsk.is_close_timeout_active = false;
    tsk.close_timeout = 0; 
    // Abre la tapa
    my_servo.open_top();
    buzzer.play(500);
  }
}


void callback(char *topic, byte *payload, unsigned int length) {
  String message = "";
	Serial.print("[" + String(topic) + "] ");
	for (int i=0; i<length; i++) {
    message.concat((char) payload[i]);
	}
	Serial.println(message);
  run_action_from_message(message);
}