class RTC {
  public:
    uint8_t _hour=0, _minute=0, _second=0, _month=0, _day=0;
    uint16_t _year=0;
    String _time = "";
    String _date = "";
  public: 
    void RTC_init(void);
    void RTC_format_time(void);
    void RTC_format_date(String delimiter);
    String smaller_than_10(int number);
    void RTC_set_time(void);
    void RTC_set_date(void);
};


void RTC::RTC_init(void) {
  if (!rtc.begin()) {
    Serial.println(F("[Error] RTC no encontrado"));
    while(1) delay(1000);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println(F("[Success] RTC cargado"));
}


String RTC::smaller_than_10(int number) {
  if (number < 10) {
    return "0" + String(number);
  }
  return String( number );
}


void RTC::RTC_format_time(void) {
  _time = String( _hour ) + ":";
  _time += smaller_than_10( _minute )+ ":";
  _time += smaller_than_10( _second );
}


void RTC::RTC_format_date(String delimiter) {
  _date = String( _year ) + delimiter;
  _date += smaller_than_10( _month ) + delimiter;
  _date += smaller_than_10( _day );
}


void RTC::RTC_set_time(void) {
  DateTime now = rtc.now();
  _second = now.second();
  _minute = now.minute();
  _hour = now.hour();
}


void RTC::RTC_set_date(void) {
  DateTime now = rtc.now();
  _day = now.day();
  _month = now.month();
  _year = now.year();
}
