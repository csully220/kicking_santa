#include <Servo.h>

#define TRIGGER 3
#define FIRE_LED 6
#define AUDIO 5
#define LEGS 9

// the setup function runs once when you press reset or power the board

bool start_seq = false;
int frame_counter = 0;
Servo legs;
int legmid = 90;
int legmax = legmid + 45; //0-254
int legmin = legmid - 45;
int legpos = legmid;
int leg_dt = 5;
bool legs_rising = true;

int led_val = 0;
int led_min = 60;
int led_dt = 1;
bool led_rising = true;

void setup() {
  pinMode(TRIGGER, INPUT);
  pinMode(FIRE_LED, OUTPUT);
  legs.attach(LEGS);
  legs.write(45);
  delay(300);
  legs.write(135);
  delay(300);
  legs.write(legpos);
}

// the loop function runs over and over again forever
void loop() {
  start_seq = digitalRead(TRIGGER);
  if (start_seq) {

    while(frame_counter <= 2000) {
      // LED fire stuff
      if(led_rising) {
          led_val += led_dt; 
          if(led_val >= 255) {
            led_val = 255;
            led_rising = false; 
          }
      } else {
          led_val -= led_dt; 
          if(led_val >= led_min) {
            led_val = led_min;
            led_rising = true; 
          }
      }
      analogWrite(FIRE_LED, led_val);
      
      // kicking Santa legs stuff
      if(legs_rising) {
          legpos += leg_dt; 
          if(legpos >= legmax) {
            legpos = legmax;
            legs_rising = false; 
          }
      } else {
          legpos -= leg_dt; 
          if(legpos >= legmin) {
            legpos = legmin;
            legs_rising = true; 
          }
      }
      legs.write(legpos);
      delay(5);
      frame_counter++;
    }
    legs.write(legmid);
  }
}
