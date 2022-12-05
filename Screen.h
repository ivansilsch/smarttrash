class LCD {
  public:
    bool show_state = false;
  public:
    void LCD_init(void);
    void LCD_print_time(void);
    void LCD_print_state(void);
    void LCD_print(void);
};


void LCD::LCD_init(void) {
  lcd.init();
  lcd.backlight();
}


void LCD::LCD_print(void) {
  if (show_state) {
    LCD_print_state();
  } else {
    LCD_print_time();
  }
}


void LCD::LCD_print_time(void) {
  _rtc.RTC_set_time();
  _rtc.RTC_set_date();
  _rtc.RTC_format_time();
  _rtc.RTC_format_date("-");
  lcd.setCursor(0, 0);
  lcd.print(_rtc._date);
  lcd.print("      ");
  lcd.setCursor(0, 1);
  lcd.print(_rtc._time);
  lcd.print("        ");
}


void LCD::LCD_print_state(void) {
  lcd.setCursor(0, 0);
  if (my_servo.is_open) {
    lcd.print("Abierto,");
  } else {
    lcd.print("Cerrado,");
  }

  lcd.print("Flama:");
  if (flame.is_active) {
    lcd.print("Si");
  } else { 
    lcd.print("No");
  }

  lcd.setCursor(0, 1);
  lcd.print("Inclinado:");
  if (inclination.is_active) {
    lcd.print("Si    ");
  } else { 
    lcd.print("No    ");
  }
}

