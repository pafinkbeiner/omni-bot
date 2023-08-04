#include <Servo.h>

Servo s1;
Servo s2;
Servo s3;

int inc_b = 0;
int selected_pin = 0;
int selected_speed = 0;

int relay_pin_1 = 2;

int pwm_pin_1 = 3;
int pwm_pin_2 = 5;
int pwm_pin_3 = 6;

int s1_min = 13;
int s2_min = 5;
int s3_min = 2;

int s1_max = 174;
int s2_max = 166;
int s3_max = 163;

int s1_neut = 94;
int s2_neut = 86;
int s3_neut = 83;

void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(relay_pin_1, OUTPUT);
  s1.attach(pwm_pin_1);
  s2.attach(pwm_pin_2);
  s3.attach(pwm_pin_3);
  s1.write(s1_neut);
  s2.write(s2_neut);
  s3.write(s3_neut);
}

void loop() {
  if ( Serial.available() > 0){

    int data = Serial.parseInt();
    inc_b = data;

    if (inc_b == 255){
      // flush input
      selected_pin = 0;
      selected_speed = 0;
      Serial.println("Reset");
    }else{
      // load variables
      if (selected_pin == 0){
        selected_pin = inc_b;
      }else{
        selected_speed = inc_b;
      }
      // change speed
      if( selected_pin != 0 && 
          selected_speed != 0 && 
          selected_speed <= 180 && 
          selected_speed >= 0
        ){
        switch (selected_pin) {
          case 1: 
            s1.write(map(selected_speed,0,180,s1_min,s1_max)); 
            Serial.println("Write "+ String(selected_speed) + " to Motor S1");
            break;
          case 2: 
            s2.write(map(selected_speed,0,180,s2_min,s2_max)); 
            Serial.println("Write "+ String(selected_speed) + " to Motor S2");
            break;
          case 3: 
            s3.write(map(selected_speed,0,180,s3_min,s3_max)); 
            Serial.println("Write "+ String(selected_speed) + " to Motor S3");
            break;
          case 4:
            if(selected_speed >= 90){
              digitalWrite(relay_pin_1, HIGH);
              Serial.println("Enabled Relay 1");
            }else{
              digitalWrite(relay_pin_1, LOW);
              Serial.println("Disabled Relay 1");
            }
        }
      }

    }
  }
}
