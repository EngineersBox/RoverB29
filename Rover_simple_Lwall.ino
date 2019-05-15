#include <SoftwareSerial.h>

// Pin declarations
#define motor1_enable 13
#define motor1_inputA 12
#define motor1_inputB 11

#define motor2_enable 5
#define motor2_inputA 4
#define motor2_inputB 3

// Forward sonar
#define fsonar_echo 7
#define fsonar_trig 8

// Right sonar
#define rsonar_echo 9
#define rsonar_trig 10

long duration_r, duration_f, distance_r, distance_f;

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
  pinMode(fsonar_echo, INPUT);
  pinMode(fsonar_trig, OUTPUT);
  pinMode(rsonar_echo, INPUT);
  pinMode(rsonar_trig, OUTPUT);

  digitalWrite(motor1_enable, HIGH);
  digitalWrite(motor2_enable, HIGH);
  
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
      digitalWrite (motor1_inputA, HIGH);
      digitalWrite (motor1_inputB, LOW);
      digitalWrite (motor2_inputA, LOW);
      digitalWrite (motor2_inputB, HIGH);
      break;
    case RIGHT: 
      digitalWrite (motor1_enable, HIGH);
      digitalWrite (motor2_enable, HIGH);
      digitalWrite (motor1_inputA, LOW);
      digitalWrite (motor1_inputB, HIGH);
      digitalWrite (motor2_inputA, HIGH);
      digitalWrite (motor2_inputB, LOW);
      break;
    case STOPPED:
      digitalWrite(motor1_enable, LOW);
      digitalWrite(motor2_enable, LOW);
      break;
  }
}

void loop() {

  // Right sonar pulse
  digitalWrite(rsonar_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(rsonar_trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(rsonar_trig, LOW);

  // Front sonar pulse
  digitalWrite(fsonar_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(fsonar_trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(fsonar_trig, LOW);

  // Measure duration of right echo
  duration_r = pulseIn(rsonar_echo, HIGH);
  distance_r = (duration_r / 2) * 0.00343; // Calculate distance in mm

  // Measure duration of front echo
  duration_f = pulseIn(fsonar_echo, HIGH);
  distance_f = (duration_r / 2) * 0.00343; // Calculate distance in mm

  if ((20 < distance_r < 40) and (10 < distance_f < 20)) {
    move(LEFT);
  } else if ((40 < distance_r) and (10 < distance_f < 20)) {
    move(RIGHT);
  } else if ((20 < distance_r < 40) and (20 < distance_f)) {
    move(FORWARD);
  } else {
    move(FORWARD);
  }
}
