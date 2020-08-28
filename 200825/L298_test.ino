#define ENA 3
#define ENB 5
#define IN1 2
#define IN2 4
#define IN3 6
#define IN4 7

int pwm_base = 100;
int pwm_offset = 0;
int pwm_steering = 0;
/*
int line_sensor_pin[5] = {8,9,10,11,12};
int line_sensor_pin_data[5] = {0,0,0,0,0};
*/

#define TRIG 13 // trig 핀 설정
#define ECHO 12 // echo 핀 설정

void setup() {
  /// Motor Initialize
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);

  // LED Initialize
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
/*  
  // Line sensor Initialize
  for(int i=0;i<5;i++) pinMode(line_sensor_pin[i], INPUT);
  */
  Serial.begin(115200); // 시리얼 통신 속도
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

///Right motor
void motor_R_direction (int direction) {
  if(direction == 0) { /// STOP
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  } else if(direction == 2) { /// Back
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  } else if(direction == 1) { /// Front
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  } 
}

void motor_R_speed (int pwm) {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  if(pwm > 0)
  {
    analogWrite(ENA,pwm);
  }
  else if(pwm == 0)
  {
    analogWrite(ENA,0);
  }
  else
  {
    analogWrite(ENA,pwm);
  }
}

///Left motor
void motor_L_direction (int direction) {
  if(direction == 0) { /// STOP
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  } else if(direction == 2) { /// Back
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  } else if(direction == 1) { /// Front
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  } 
}
/*
void motor_L_Control1 (int pwm) {
  if(direction == 0) { /// STOP
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,pwm);
  } else if(direction == 2) { /// Back
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,pwm);
  } else if(direction == 1) { /// Front
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,pwm);
  } 
}


void motor_R_Control1 (int pwm) {
  if(direction == 0) { /// STOP
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,pwm);
  } else if(direction == 2) { /// Back
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  analogWrite(ENA,pwm);
  } else if(direction == 1) { /// Front
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENA,pwm);
  } 
}
*/
void motor_L_speed (int pwm) {
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);  
  if(pwm > 0)
  {
    analogWrite(ENB,pwm);
  }
  else if(pwm == 0)
  {
    analogWrite(ENB,0);
  }
  else
  {
    analogWrite(ENB,pwm);
  }
}

void led_indicator_blink (void) {
  // LED Blink to indicate Motor start
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void car_direction(int c_direction)
{
  if(c_direction == 0) /// stop
  {
    motor_L_direction(0);
    motor_R_direction(0);
  }
  else if(c_direction == 1) /// go
  {
    motor_L_direction(1);
    motor_R_direction(1);
  }
  else if(c_direction == 2) /// back
  {
    motor_L_direction(2);
    motor_R_direction(2);
  }
  else if(c_direction == 3) // right turn
  {
    motor_L_direction(1);
    motor_R_direction(2);
  }
  else if(c_direction == 4) // left turn
  {
    motor_L_direction(2);
    motor_R_direction(1);
  }
}

void car_speed(int speed)
{
  if(speed == 0) // stop
  {
    motor_L_speed(0);
    motor_R_speed(0);
  }
  else if(speed == 1) // go
  {
    motor_L_speed(100);
    motor_R_speed(100);
  }
  else if(speed == 2) // soft left
  {
    motor_L_speed(100);
    motor_R_speed(50);
  }
  else if(speed == 3) // soft right
  {
    motor_L_speed(50);
    motor_R_speed(100);
  }
  else
  {
    motor_L_speed(0);
    motor_R_speed(0);
  }
}
/*
int read_line_sensor()
{
  int type = -100;
  int sum = 0;
  for(int i=0;i<5;i++)
  {
    line_sensor_pin_data[i]=digitalRead(line_sensor_pin[i]);
  if(line_sensor_pin_data[i] == 1) sum++;
  }
  if(sum == 1)
  {
  if(line_sensor_pin_data[0] == 1) type = -4;
  if(line_sensor_pin_data[1] == 1) type = -2;
  if(line_sensor_pin_data[2] == 1) type = 0;
  if(line_sensor_pin_data[3] == 1) type = 2;
  if(line_sensor_pin_data[4] == 1) type = 4;
  
  }
  if(sum == 2)
  {
  if((line_sensor_pin_data[0] == 1) && (line_sensor_pin_data[1] == 1) ) type = -3;
  if((line_sensor_pin_data[1] == 1) && (line_sensor_pin_data[2] == 1) ) type = -1;
  if((line_sensor_pin_data[2] == 1) && (line_sensor_pin_data[3] == 1) ) type = 1;
  if((line_sensor_pin_data[3] == 1) && (line_sensor_pin_data[4] == 1) ) type = 3;
  
  }
  
  return type;
}
*/
void actual_moving(int type)
{
  switch(type)
  {
    case -4:
    car_direction(4);
    car_speed(1);
    break;
    case -3:
    car_direction(4);
    car_speed(1);
    break;
    case -2:
    car_direction(4);
    car_speed(1);
    break;
    case -1:
    car_direction(4);
    car_speed(1);
    break;
    case 0:
    car_direction(4);
    car_speed(1);
    break;
    case 1:
    car_direction(4);
    car_speed(1);
    break;
    case 2:
    car_direction(4);
    car_speed(1);
    break;
    case 3:
    car_direction(4);
    car_speed(1);   
    break;
    case 4:
    car_direction(4);
    car_speed(1);   
    break;
    case -100:
    car_direction(4);
    car_speed(1);   
    break;
}
}



void loop() {
/*  int line_type = -100;
  int pwm_r, pwm_l;
  pwm_r = 0; pwm_l = 0;
  
  read_line_sensor();
  line_type = read_line_sensor();
  
 for(int i=0;i<5;i++)
 {
   Serial.print(line_sensor_pin_data[i]);
   Serial.print(" ");
 }
 Serial.print(line_type);
 Serial.println(" "); 
 if(line_type != -100) pwm_steering = line_type * 10; //// 10 is TBD by Machine learning.
 
 pwm_l = pwm_base + pwm_steering;
 pwm_r = pwm_base + pwm_offset - pwm_steering;
 motor_L_speed(pwm_l);
 motor_R_speed(pwm_r);
 Serial.print(pwm_l); */
 
 long duration, distance;
 digitalWrite(TRIG,LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG,HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG,LOW);
 duration = pulseIn(ECHO, HIGH);
 distance = duration * 17 / 1000;


 Serial.println(duration);
 Serial.print("\nDistance : ");
 Serial.print(distance);
 Serial.println(" Cm");
 delay(1000);
}
