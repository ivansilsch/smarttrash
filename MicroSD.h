class Micro_SD {
  public:
    String filename;
  public:
    void microSD_init(void);
    void set_filename(void);
    void microSD_save(void);
    String microSD_read_file(void);
    StaticJsonDocument<256> global_state_to_JSON(void);
};


void Micro_SD::microSD_init(void) {
  while(!SD.begin(MICROSD_PIN)) {
    Serial.print(F("[Error] Memoria SD no conectada"));
    Serial.println(F(" - Revisa conexiones"));
    delay(3000);
  }
  Serial.println(F("[Success] SD detectada!"));
}


void Micro_SD::set_filename(void) {
  //Actualiza el nombre del archivo
  _rtc.RTC_set_date();
  _rtc.RTC_format_date("-");
  filename = _rtc._date;
}


StaticJsonDocument<256> Micro_SD::global_state_to_JSON(void) {
    // Crea el json
    StaticJsonDocument<256> doc;
    doc["date"] = _rtc._date;
    doc["time"] = _rtc._time;
    doc["is_open"] = my_servo.is_open;
    doc["flame_detected"] = flame.is_active;
    doc["inclination"] = inclination.is_active;
    return doc;
}


String Micro_SD::microSD_read_file(void) {
  File_SD = SD.open("/" + filename + ".json", FILE_READ);
  String File_string = "";
  if (File_SD) {
    while (File_SD.available()) {
      File_string += String( (char) File_SD.read() );
    }
    File_SD.close();
  }
  return File_string;
}


void Micro_SD::microSD_save(void) {
  // Aqui se almacena el json
  set_filename(); 
  File_SD = SD.open("/" + filename + ".json", FILE_APPEND);
  if (File_SD) {

    _rtc.RTC_set_time();
    _rtc.RTC_format_time(); 

    StaticJsonDocument<256> json = global_state_to_JSON();  

    if (!serializeJson(json, File_SD)) {
		  Serial.println(F("[Error] No se pudo guardar el estado en el archivo"));
		  return;	
	  } else {
      File_SD.println(",");
    }
    File_SD.close();

  }
}
