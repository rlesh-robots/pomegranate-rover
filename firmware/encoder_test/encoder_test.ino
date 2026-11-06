const int PIN_A = 2;
const int PIN_B = 3;
volatile long count = 0;

void ISRA() {
  if (digitalRead(PIN_A) != digitalRead(PIN_B)) {
    count ++;
  } else {
    count --;
  }
}

void ISRB() {
  if (digitalRead(PIN_A) != digitalRead(PIN_B)) {
    count --;
  } else {
    count ++;
  }
}

void setup() {
  // put your setup code here, to run once:
  attachInterrupt(digitalPinToInterrupt(PIN_A), ISRA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), ISRB, CHANGE);
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  noInterrupts();
  long tempcount = count;
  interrupts();
  // printing here
  Serial.println(tempcount);
}
