#include <Servo.h>


#define TRIGGER 2
#define FIRE_LED 3
#define AUDIO 4
#define LEGS 5

// the setup function runs once when you press reset or power the board

bool start_seq = false;
Servo legs;
int legmax = 0; //0-254
int legmin = 90;
int legpos = 0;
int leg_dt = 5;

void setup() {
  pinMode(TRIGGER, INPUT);
  pinMode(FIRE_LED, OUTPUT);
  pinMode(FIRE_FAN, OUTPUT);
  pinMode(AUDIO, OUTPUT);
  pinMode(LEGS, OUTPUT);
  legs.attach(LEGS);
}

// the loop function runs over and over again forever
void loop() {
  start_seq = digitalRead(TRIGGER);
  if (start_seq) {
    legs.write(legpos)
    }
  }
}
