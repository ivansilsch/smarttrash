class FanMotor {
  public:
    void FanMotor_init(void);
    void on(void);
    void off(void);
};

void FanMotor::FanMotor_init(void) {
  pinMode(FAN_MOTOR_PIN, OUTPUT);
  digitalWrite(FAN_MOTOR_PIN, LOW);
}

void FanMotor::on(void) {
  digitalWrite(FAN_MOTOR_PIN, HIGH);
}

void FanMotor::off(void) {
  digitalWrite(FAN_MOTOR_PIN, LOW);
}
