// implementation of CPX piano,
// the piano use two inputs, the first one is the touch sensor which abvioustly stands for the piano keys.
// the switch button stands for the piano tone level settings.
// the outputs are the LEDs, and of course the speaker.
// the result is nice and simple piano :)
// you welcome to watch an example of live performance at the link!
// https://youtu.be/xRBZPd_7kdM 

#include <Adafruit_CircuitPlayground.h>

int pads[] = {2, 3, 10 ,6};
int padsCount = 4;
int threshhold = 1000; 
int mode = 0; 

void setup() {
  CircuitPlayground.begin();
}

void loop() {
  if (CircuitPlayground.slideSwitch()){
    mode = 1;
  } else {
    mode = 0;
  }
  for (int i = 0; i < padsCount; i ++) {
    // if the pad is touched
    if (capTouched(pads[i])) {
      playSound(pads[i]);
    }
  }
}

void playSound(int pad) {
  //every pad touch causes a different sound to play and a pixel to light 
  //mode 1 is for higher sounds 
  switch (pad) {
    case 3:
      CircuitPlayground.playTone(100 + (mode * 300), 100, false);
      CircuitPlayground.setPixelColor(0, 200, 100, 0);
      break;
    case 2:
      CircuitPlayground.playTone(200 + (mode * 300), 100, false);
      CircuitPlayground.setPixelColor(1, 0, 255, 0);
      break;
    case 6:
      CircuitPlayground.playTone(300 + (mode * 300), 100, false);
      CircuitPlayground.setPixelColor(6, 0, 0, 255);
      break;
    case 10:
      CircuitPlayground.playTone(400 + (mode * 300), 100, false);
      CircuitPlayground.setPixelColor(9, 50, 250, 100);
      break;
  }
  delay(100);
  CircuitPlayground.clearPixels();
}

boolean capTouched(int pad) {
  // return true if the readCap transcends threshhold
  if (CircuitPlayground.readCap(pad) > threshhold) {
    return true;  
  } else {
    return false;
  }
}