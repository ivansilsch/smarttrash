class MyServo {
  public:
    bool is_open = false;
  public:
    void Servo_init(void);
    void open_top(void);
    void close_top(void);
};


void MyServo::Servo_init(void) {
  servo.attach(SERVO_PIN);
}


void MyServo::open_top(void) {
  is_open = true;
  servo.write(90);
}


void MyServo::close_top(void) {
  if (is_open) {
    servo.write(180);
    is_open = false; 
  }
}