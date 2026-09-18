//Ibrahim Ramy:
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define SPEED_LEFT 5
#define SPEED_RIGHT 10
#define trig 3
#define echo 4
#define LDRSensor A0

int baseline = 450;         
int motorSpeed = 255;       
long duration;              
float distanceValue;        
int ldrValue;  
bool light = false;       

void Motor_voidLeft();
void Motor_voidRight();
void Motor_voidForward();
void Motor_voidBackward();
void Motor_voidStop();
void applySpeed();
float getDistance();


void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(SPEED_LEFT, OUTPUT);
  pinMode(SPEED_RIGHT, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LDRSensor, INPUT);

  Motor_voidStop();
}
void loop() {

  ldrValue = analogRead(LDRSensor);
  Serial.print("LDR: ");
  Serial.println(ldrValue);

  distanceValue = getDistance();

  // ==========================================================
  // CASE 1: LDR BELOW BASELINE → RUN FULL SEQUENCE
  // ==========================================================
  if (ldrValue < baseline && distanceValue > 5){
    light = true;
  }
  if (light) {

    Serial.println("LDR < baseline → Running movement sequence");

    // -------- Step 1: forward--------
    Motor_voidForward();
    Serial.println("F");
    for (int i =0; i<5; i++){
      distanceValue = getDistance();
      if (distanceValue < 5 && distanceValue > 0){
        Serial.println(distanceValue);
        Serial.println("-----");
        Motor_voidStop();
        light = false;
        return;
      }
      delay(10);
    }
    
    // -------- Step 2: Turn Left --------
    Motor_voidLeft();
    Serial.println("L");
    for (int i =0; i<5; i++){
      distanceValue = getDistance();
      if (distanceValue < 5 && distanceValue > 0){
        Motor_voidStop();
        light = false;
        return;
      }
      delay(70);
    }

    // -------- Step 3: Forward 0.4 sec --------
    Motor_voidForward();
    Serial.println("F");
    for (int i =0; i<5; i++){
      distanceValue = getDistance();
      if (distanceValue < 5 && distanceValue > 0){
        Motor_voidStop();
        light = false;
        return;
      }
      delay(25);
    }

    // -------- Step 4: Turn Right --------
    Motor_voidRight();
    Serial.println("R");
    for (int i =0; i<5; i++){
      distanceValue = getDistance();
      if (distanceValue < 5 && distanceValue > 0){
        Motor_voidStop();
        light = false;
        return;
      }
      delay(85);
    }

    Motor_voidStop();
    ldrValue = analogRead(LDRSensor);
    Serial.println(LDRSensor);
    light = false;
  }

  // ==========================================================
  // CASE 2: LDR ABOVE BASELINE → STOP INSTANTLY
  // ==========================================================
  if (ldrValue > baseline) {
    Serial.println("LDR > baseline → STOP");
    Motor_voidStop();
  }
}
bool checkInterrupt() {
  // Check LDR stop condition
  if (ldrValue > baseline) {
    Serial.println("LDR interrupt → STOP");
    Motor_voidStop();
    return false;
  }

  return true;  // return to sequence caller

}
void delayWithInterrupt(unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    if (checkInterrupt()) return;
    delay(10);
  }
}
void applySpeed() {
  analogWrite(SPEED_LEFT, motorSpeed);
  analogWrite(SPEED_RIGHT, motorSpeed);
}

float getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  return duration * 0.0344 / 2; 
}

void Motor_voidLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  applySpeed();
}
void Motor_voidRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  applySpeed();
}
void Motor_voidForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  applySpeed();
}
void Motor_voidBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  applySpeed();
}



void Motor_voidStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(SPEED_LEFT, 0);
  analogWrite(SPEED_RIGHT, 0);
}
