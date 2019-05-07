#include <SoftwareSerial.h>

// Pin declarations
#define motor1_enable 13
#define motor1_inputA 11
#define motor1_inputB 12

#define motor2_enable 5
#define motor2_inputA 3
#define motor2_inputB 4

#define rx_bt 7
#define tx_bt 8

SoftwareSerial BTSerial(rx_bt,tx_bt);

int button = 0;
typedef enum { FORWARD, BACKWARDS, LEFT, RIGHT, STOPPED } state;

state current_state = STOPPED;

void setup() {
  pinMode(motor1_enable, OUTPUT);
  pinMode(motor1_inputA, OUTPUT);
  pinMode(motor1_inputB, OUTPUT);
  pinMode(motor2_enable, OUTPUT);
  pinMode(motor2_inputA, OUTPUT);
  pinMode(motor2_inputB, OUTPUT);
  pinMode(rx_bt, INPUT);
  pinMode(tx_bt, OUTPUT);

  digitalWrite(motor1_enable, HIGH);
  digitalWrite(motor2_enable, HIGH);
  

  // Setup communications
  //Serial.begin(9600); //coms with computer
  //BTSerial.begin(9600); //coms with Bluetooth
  
  // Display message to serial monitor
  //Serial.println("Begin communication");
}

void move (state c_state) {
  switch (c_state) {
    case FORWARD:
      digitalWrite (motor1_enable, HIGH);
      digitalWrite (motor2_enable, HIGH);
      digitalWrite (motor1_inputA, HIGH);
      digitalWrite (motor1_inputB, LOW);
      digitalWrite (motor2_inputA, HIGH);
      digitalWrite (motor2_inputB, LOW);
      break;
    case BACKWARDS:
      digitalWrite (motor1_enable, HIGH);
      digitalWrite (motor2_enable, HIGH);
      digitalWrite (motor1_inputA, LOW);
      digitalWrite (motor1_inputB, HIGH);
      digitalWrite (motor2_inputA, LOW);
      digitalWrite (motor2_inputB, HIGH);
      break;
    case LEFT:
      digitalWrite (motor1_enable, HIGH);
      digitalWrite (motor2_enable, HIGH);
      digitalWrite (motor1_inputA, LOW);
      digitalWrite (motor1_inputB, HIGH);
      digitalWrite (motor2_inputA, HIGH);
      digitalWrite (motor2_inputB, LOW);
      break;
    case RIGHT:  
      digitalWrite (motor1_enable, HIGH);
      digitalWrite (motor2_enable, HIGH);
      digitalWrite (motor1_inputA, HIGH);
      digitalWrite (motor1_inputB, LOW);
      digitalWrite (motor2_inputA, LOW);
      digitalWrite (motor2_inputB, HIGH);
      break;
    case STOPPED:
      digitalWrite(motor1_enable, LOW);
      digitalWrite(motor2_enable, LOW);
      break;
  }
}

void loop() {
  delay(4000);
  
  for (int i = 0; i < 4; i++) {
    // STRAIGHT
    move(FORWARD);
    delay(5000);
    
    // TURN LEFT
    move(LEFT);
    delay(1050);
  }
  move(STOPPED);

  /*if (BTSerial.available() ) {
    button = BTSerial.read()
    Serial.println(BTSerial.read());

    switch (button) {
      case 54: // RIGHT
        current_state = RIGHT;
        break;
      case 52: // LEFT
        current_state = LEFT;
        break;
      case 56: // UP
        current_state = FORWARD;
        break;
      case 50: // DOWN
        current_state = BACKWARDS;
        break;
      default:
        current_state = STOPPED;
        break;
    }
  }
  move(current_state);
  */
  
}
