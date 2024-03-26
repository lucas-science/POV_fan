int PWM = 200; //PWM doit être compris entre 0 et 255

void setup() {
  pinMode(5,OUTPUT);

}

void loop() {
  analogWrite(5,PWM);

}
