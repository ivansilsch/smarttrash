class Inclination {
  public:
    bool is_active = false;
  public:
    void Inclination_init(void);
    void update(void);
};


void Inclination::Inclination_init(void) {
  pinMode(INCLINATION_PIN, INPUT);
}


void Inclination::update(void) {
  is_active = (bool) digitalRead(INCLINATION_PIN);
}