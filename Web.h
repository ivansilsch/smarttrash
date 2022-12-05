class Web {
  public:
    void Web_init(void);
    void Web_handle_requests(void);
    void Web_send_response_to_client(WiFiClient web_client);
};



void Web::Web_init(void) {
  web_server.begin();
  Serial.println(F("[Info] Servidor web iniciado"));
}



void Web::Web_send_response_to_client(WiFiClient web_client) {
  // send a standard http response header
  web_client.println("HTTP/1.1 200 OK");
  web_client.println("Content-Type: application/json");
  web_client.println("Connection: close");  // the connection will be closed after completion of the response
  // web_client.println("Refresh: 5");  // refresh the page automatically every 5 sec
  web_client.println();
  
  // Envia el contenido del archivo de la micro SD
  web_client.println("[");
  web_client.print(  micro_sd.microSD_read_file()  );
  web_client.println("{\"end\":1}");
  web_client.println("]");
}



void Web::Web_handle_requests(void) {
  WiFiClient web_client = web_server.available();
  if (web_client) {
    bool currentLineIsBlank = true;
    while (web_client.connected()) {
      if (web_client.available()) {
        char c = web_client.read();
        // Serial.write(c);
        if (c == '\n' && currentLineIsBlank) {
          Web_send_response_to_client(web_client);
          break;
        }

        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }

      }

    }
    delay(1);
    // close the connection:
    web_client.stop();
    Serial.println("[Info] client disconnected");
  }	
}
