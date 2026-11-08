const int PIN_A = 2;
const int PIN_B = 3;
volatile long count = 0;

unsigned long previousCount = 0;
unsigned long previousMillis = 0;
const long interval = 100;
// ISR = interrupt service routine
// when pin a (connected to encoder A) changes, run this ISR
void ISRA() {
  if (digitalRead(PIN_A) != digitalRead(PIN_B)) {
    count ++;
  } else {
    count --;
  }
}

// when pin b (connected to encoder B) changes, run this ISR
void ISRB() {
  if (digitalRead(PIN_A) != digitalRead(PIN_B)) {
    count --;
  } else {
    count ++;
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_A), ISRA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), ISRB, CHANGE);
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis();
  int deltatime = currentMillis - previousMillis;
  // run if there has been an amount of milliseconds equal to the interval
  if (deltatime >= interval) {
    noInterrupts();
    long tempcount = count;
    interrupts();
    previousMillis = currentMillis;
    int deltaCounts = tempcount - previousCount;
    int diameter = 80;
    
    // counts times the amount of counts per millimeter = distance, counts cancel out
    float distance = deltaCounts * ((PI*diameter)/4200);
   
    //simple distance over time for speed, in millimeters per millisecond = meters per second
    float speed = (distance / deltatime);
    
    //save current counts for deltaCounts
    previousCount = tempcount;
    Serial.println(speed, 4);
  }
  
}
