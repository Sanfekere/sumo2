//#define DEBUG_MODE

// LED pins
#define LEDA 13
#define LED1 5
#define LED2 11
#define LED3 2

// Button pin
#define BTN 12

#define START_IR 18

// DIP switches
#define DIP1 15
#define DIP2 14
#define DIP3 16
#define DIP4 1

// Line sensors
#define LINE_L A2
#define LINE_R A1
#define LINE_B A4

// Enemy sensors
#define SHARP1 A5
#define SHARP2 A3
#define SHARP3 7
#define SHARP4 A8
#define SHARP5 A7

// Motor pins
#define RIGHT_DIR 10
#define LEFT_DIR  4
#define RIGHT_PWM 9
#define LEFT_PWM  3

void setup() {
  // Enable serial monitor
  Serial.begin(9600);
  
   // LEDs
   pinMode(LEDA, OUTPUT);
#define LEDA_ON digitalWrite(LEDA, HIGH)
#define LEDA_OFF digitalWrite(LEDA, LOW)
  pinMode(LEDA, OUTPUT);
#define LED1_ON digitalWrite(LED1, HIGH)
#define LED1_OFF digitalWrite(LED1, LOW)
  pinMode(LED2, OUTPUT);
#define LED2_ON digitalWrite(LED2, HIGH)
#define LED2_OFF digitalWrite(LED2, LOW)
  pinMode(LED3, OUTPUT);
#define LED3_ON digitalWrite(LED3, HIGH)
#define LED3_OFF digitalWrite(LED3, LOW)

  // Button
  pinMode(BTN, INPUT_PULLUP);
#define READ_BTN !digitalRead(BTN)
  pinMode(START_IR, INPUT);
#define READ_IR digitalRead(START_IR)



  // DIP
  pinMode(DIP1, INPUT_PULLUP);
  pinMode(DIP2, INPUT_PULLUP);
  pinMode(DIP3, INPUT_PULLUP);
  pinMode(DIP4, INPUT_PULLUP);
#define READ_DIP1 !digitalRead(DIP1)
#define READ_DIP2 !digitalRead(DIP2)
#define READ_DIP3 !digitalRead(DIP3)
#define READ_DIP4 !digitalRead(DIP4)

  // Line sensors
  pinMode(LINE_L, INPUT);
  pinMode(LINE_R, INPUT);
  pinMode(LINE_B, INPUT);
#define LINE_TRESHOLD 120
#define LINE_L_DET analogRead(LINE_L) < LINE_TRESHOLD
#define LINE_R_DET analogRead(LINE_R) < LINE_TRESHOLD
#define LINE_B_DET analogRead(LINE_B) < LINE_TRESHOLD

  // Enemy sensors
  pinMode(SHARP1, INPUT);
  pinMode(SHARP2, INPUT);
  pinMode(SHARP3, INPUT);
  pinMode(SHARP4, INPUT);
  pinMode(SHARP5, INPUT);
#define READ_SHARP1 !digitalRead(SHARP1)
#define READ_SHARP2 !digitalRead(SHARP2)
#define READ_SHARP3 !digitalRead(SHARP3)
#define READ_SHARP4 !digitalRead(SHARP4)
#define READ_SHARP5 !digitalRead(SHARP5)

  // Motors
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);

  delay(1000);
}

void driveForward(int l_speed, int r_speed) {
  analogWrite(LEFT_PWM, l_speed);
  digitalWrite(LEFT_DIR, LOW);
  analogWrite(RIGHT_PWM, r_speed);
  digitalWrite(RIGHT_DIR, LOW);
}

void driveBackward(int l_speed, int r_speed) {
  analogWrite(LEFT_PWM, l_speed);
  digitalWrite(LEFT_DIR, HIGH);
  analogWrite(RIGHT_PWM, r_speed);
  digitalWrite(RIGHT_DIR, HIGH);
}

void driveLeft(int l_speed, int r_speed) {
  analogWrite(LEFT_PWM, l_speed);
  digitalWrite(LEFT_DIR, HIGH);
  analogWrite(RIGHT_PWM, r_speed);
  digitalWrite(RIGHT_DIR, LOW);
}

void driveRight(int l_speed, int r_speed) {
  analogWrite(LEFT_PWM, l_speed);
  digitalWrite(LEFT_DIR, LOW);
  analogWrite(RIGHT_PWM, r_speed);
  digitalWrite(RIGHT_DIR, HIGH);
}

int getSensorState() {
  int sensorState = 0;

  // Line sensors
  if (LINE_L_DET) {
    LED1_ON;
    sensorState += 1;
  } else {
    LED1_OFF;
  }
  
  if (LINE_R_DET) {
    LED2_ON;
    sensorState += 2;
  } else {
    LED2_OFF;
  }
  
  if (LINE_B_DET) {
    LED3_ON;
    sensorState += 4;
  } else {
    LED3_OFF;
  }

  if (sensorState == 0) {
    if (READ_SHARP2) { sensorState += 8; }
    if (READ_SHARP3) { sensorState += 16;}
    if (READ_SHARP4) { sensorState += 32;}
  }

  if (sensorState == 0) {
    if (READ_SHARP1) { sensorState += 64; }
    if (READ_SHARP5) { sensorState += 128;}
  }

  return sensorState;
}

void loop() {
#ifdef DEBUG_MODE
  Serial.println("*** Line sensors ***");
  Serial.print("Left = ");
  Serial.print(analogRead(LINE_L));
  Serial.print("\tRight = ");
  Serial.print(analogRead(LINE_R));
  Serial.print("\tBack = ");
  Serial.println(analogRead(LINE_B));
  
  Serial.println("*** Enemy sensors ***");
  Serial.print("Left = ");
  Serial.println(READ_SHARP1);
  Serial.print("Front left = ");
  Serial.print(READ_SHARP2);
  Serial.print("\tFront middle = ");
  Serial.print(READ_SHARP3);
  Serial.print("\tFront right = ");
  Serial.println(READ_SHARP4);
  Serial.print("Right = ");
  Serial.println(READ_SHARP5);
  Serial.println();

  delay(100);
#else
  LED1_OFF;
  LED1_OFF;
  LED1_OFF;
  driveForward(0,0);

  int start_ir = 0;
   
  if (READ_IR == 1){
   // Serial.println("on 1");
    start_ir = 1;
  }else{
    start_ir = 0;
    driveForward(0,0);
    }

  if(READ_BTN != 0){
    LED1_ON;
    delay(1000);
    LED2_ON;
    delay(1000);
    LED3_ON;
    delay(3000);
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;  
    start_ir = 1;
  }

  if (start_ir != 0) {

    if (READ_DIP1) {
      driveForward(220,250);
      delay(400);
      driveBackward(50,50);
      delay(100);
      driveForward(0,0);
      delay(5000);
    } 
    else if (READ_DIP2) {
      driveLeft(120,120);
      delay(150);
      driveForward(70,70);
      delay(300);
      driveForward(0,0);
      delay(5000);
    }
    else if (READ_DIP3) {
      driveRight(120,120);
      delay(150);
      driveForward(70,70);
      delay(300);
      driveForward(0,0);
      delay(5000);
    }
    else if (READ_DIP4) {
      driveForward(100,100);
      delay(100);
      driveForward(0,0);
      delay(5000);
    }

    while (1) {    //READ_BTN == 0 && READ_IR == 1
      int sensor_state = getSensorState();
      switch (sensor_state) {
        // Line sensorss
        case 0: // No sensor
          driveForward(80,80);
          break;
        case 1: // Left line
          driveBackward(200,200);
          delay(75);
          driveRight(170,170);
          delay(75);
          break;
        case 2: // Right line
          driveBackward(200,200);
          delay(75);
          driveLeft(170,170);
          delay(75);
          break;
        case 3: // Left line && Right line
          driveBackward(200,200);
          delay(300);
          driveLeft(150,150);
          delay(125);
          break;
        case 4: // Back line
          driveForward(225,225);
          delay(300);
          break;
        case 5: // Back line && Left line
          driveRight(150,150);
          delay(50);
          driveForward(200,200);
          delay(100);
          break;
        case 6: // Back line && Right line
          driveLeft(150,150);
          delay(50);
          driveForward(200,200);
          delay(100);
          break;
        case 7: // All line sensors
          driveForward(0,0);
          break;
    
        // Enemy sensors
        case 8: // Left sharp
          driveRight(120,120);
          delay(50);
          break;
        case 16: // Middle sharp
          driveForward(200,200);
          delay(50);
          break;
        case 24: // Left sharp && Middle sharp
          driveForward(200,150);
          delay(50);
          break;
        case 32: // Right sharp
          driveLeft(150,150);
          delay(50);
          break;
        case 40: // Right sharp && Left sharp
          driveForward(150,150);
          delay(50);
          break;
        case 48: // Right sharp && Middle sharp
          driveForward(150,200);
          delay(50);
          break;
        case 56: // All sharps
          driveForward(225,225);
          delay(50);
          break;
        case 64: // Total left sharp
          driveLeft(150,150);
          delay(125);
          break;
        case 128: // Total right sharp
          driveRight(150,150);
          delay(125);
          break;
      }
      if (READ_BTN == 1){
        return;
      }
      if (READ_IR == 0){
        return;
      }
    }

    if (READ_IR == 0){
      driveForward(0,0);
    }
   

    while (READ_BTN == 1) {
      driveForward(0,0);
    }
  }
#endif
}
