#include <Servo.h>

#define TRIGGER 5
#define FIRE_LED 6
#define FIRE_FAN 8
#define LEGS 9

// the setup function runs once when you press reset or power the board

Servo legs;
bool start_seq = false;

void setup() {
  pinMode(TRIGGER, INPUT);
  pinMode(FIRE_LED, OUTPUT);
  pinMode(FIRE_FAN, OUTPUT);
  digitalWrite(FIRE_FAN, LOW);
  legs.attach(LEGS);
  legs.write(45);
  delay(300);
  legs.write(135);
  delay(300);
  legs.write(90);
}

// the loop function runs over and over again forever

void loop() {
  start_seq = digitalRead(TRIGGER);
  
  if (start_seq) {
    unsigned long startMillis = millis();
    unsigned long ledMillis, legMillis;
    
    int legmid = 90;
    int legmax = legmid + 60; //0-254
    int legmin = legmid - 60;
    bool legs_rising = true;
    
    int led_val = 0;
    int led_min = 10;
    int led_dt = 2;
    bool led_rising = true;
    
    while(true) {
      unsigned long currentMillis = millis();
      // Phase 1: Legs kick, no LED
      if ((currentMillis - startMillis) <= 5000) {
        if ((currentMillis - legMillis) >= 650) {
          if(legs_rising) {
              //legpos += leg_dt_slow; 
              legs.write(legmax);
              legs_rising = false; 
          } else {
              legs.write(legmin);
              legs_rising = true; 
          }
          legMillis = currentMillis;
        }
      }
      
      // Phase 2: Legs kick faster, LEDs glow and fan starts
      if ((currentMillis - startMillis) > 5000) {
        legmax = legmid + 45;
        legmin = legmid - 45;
        // Fan ON
        digitalWrite(FIRE_FAN, HIGH);
        
        // LED fire stuff
        if ((currentMillis - ledMillis) >= 5) {
          if(led_rising) {
            led_val += led_dt;
            if(led_val >= 255) {
              led_val = 255;
              led_rising = false;
            }
          } else {
            led_val -= led_dt;
            if(led_val <= led_min) {
              led_val = led_min;
              led_rising = true; 
            }
          }
          ledMillis = currentMillis;
        }
        analogWrite(FIRE_LED, led_val);
      
        // kicking Santa legs stuff
        if ((currentMillis - legMillis) >= 400) {
          if(legs_rising) {
            //legpos += leg_dt_slow; 
            legs.write(legmax);
            legs_rising = false; 
          } else {
            legs.write(legmin);
            legs_rising = true; 
          }
          legMillis = currentMillis;
        }
      }
      if ((currentMillis - startMillis) >= 10000) break;
    }
    legs.write(legmid);
    analogWrite(FIRE_LED, 0);
    digitalWrite(FIRE_FAN, LOW);
  }
  
}
