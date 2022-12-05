class FlameSensor {
  public:
    bool is_active = false;
  public:
    void Flame_init(void);
    void update(void);
};


void FlameSensor::Flame_init(void) {
  pinMode(FLAME_PIN, INPUT);
}


void FlameSensor::update(void) {
  is_active = (bool) digitalRead(FLAME_PIN); 
}