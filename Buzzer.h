class Buzzer {
  public:
    long long int current_millis = 0;
  private:
    bool is_playing = false;
    long long int limit_time = 0;
  public:
    void Buzzer_init(void);
    void stop_if_time_is_over(void);
    void play(int duration);
};


void Buzzer::Buzzer_init(void) {
  pinMode(BUZZER_PIN, OUTPUT);  
}


void Buzzer::stop_if_time_is_over(void) {
  if (is_playing) {
    if (current_millis > limit_time) {
      is_playing = false;
      limit_time = 0;
      analogWrite(BUZZER_PIN, 0);
    }
  }
}


void Buzzer::play(int duration) {
  if (!is_playing) {
    is_playing = true;
    limit_time = current_millis + duration;
    analogWrite(BUZZER_PIN, 200);
  }
}
