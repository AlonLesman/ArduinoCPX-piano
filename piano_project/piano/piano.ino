// implementation of CPX piano,
// the piano use two inputs, the first one is the touch sensor which abvioustly stands for the piano keys.
// the switch button stands for the piano tone level settings.
// the outputs are the LEDs, and of course the speaker.
// the result is nice and simple piano :)
// you welcome to watch an example of live performance at the link!
// https://youtu.be/xRBZPd_7kdM 

// #include <Adafruit_CircuitPlayground.h>
#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>


const char KNOB_PIN = 0; // set the input for the knob to analog pin 0
const char LDR_PIN = 1; // set the input for the LDR to analog pin 1
byte volume;

// int pads[] = {2, 3, 10 ,6};
// int padsCount = 4;
// int threshhold = 1000; 
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);

void setup() {
  // CircuitPlayground.begin();
  Serial.begin(9600); // set up the Serial output so we can look at the piezo values // set up the Serial output so we can look at the analog levels
  startMozzi();
}

void updateControl(){
  int knob_value = mozziAnalogRead(KNOB_PIN);
  // map it to an 8 bit volume range for efficient calculations in updateAudio
  volume = knob_value >> 2; 
  // print the value to the Serial monitor for debugging
  Serial.print("volume = ");
  Serial.print((int)volume);
  Serial.print("\t"); // prints a tab

  // read the light dependent resistor
  int light_level = mozziAnalogRead(LDR_PIN); // value is 0-1023

  // print the value to the Serial monitor for debugging
  Serial.print("light level = ");
  Serial.print(light_level);
  Serial.print("\t"); // prints a tab

  // set the frequency
  aSin.setFreq(light_level);

  Serial.println(); // next line
}


int updateAudio(){
  // cast char output from aSin.next() to int to make room for multiplication
  return ((int)aSin.next() * volume) >> 8; // shift back into range after multiplying by 8 bit value
}


void loop(){
  audioHook(); // required here
}
// }


// int updateAudio(){

// }

// void loop() {
//   if (CircuitPlayground.slideSwitch()){
//     mode = 1;
//   } else {
//     mode = 0;
//   }
//   for (int i = 0; i < padsCount; i ++) {
//     // if the pad is touched
//     if (capTouched(pads[i])) {
//       playSound(pads[i]);
//     }
//   }
  
// }

// boolean capTouched(int pad) {
//   // return true if the readCap transcends threshhold
//   if (CircuitPlayground.readCap(pad) > threshhold) {
//     return true;  
//   } else {
//     return false;
//   }
// }

// void playSound(int pad) {
//   //every pad touch causes a different sound to play and a pixel to light 
//   //mode 1 is for higher sounds 
//   switch (pad) {
//     case 3:
//         // Define a simple wave shape for the sound
//       int16_t waveform[MozziADC::AUDIO_BUFFER_SIZE];
//       for (int i = 0; i < MozziADC::AUDIO_BUFFER_SIZE; i++) {
//       waveform[i] = 0;
//       }
//       waveform[0] = 10000;
//       waveform[1] = -10000;
//       // Play the sound for a short duration
//       for (int i = 0; i < 100; i++) {
//         audioWrite(waveform, MozziADC::AUDIO_BUFFER_SIZE);
//       }
//       CircuitPlayground.setPixelColor(0, 200, 100, 0);
//       break;
//     case 2:
      
//       CircuitPlayground.setPixelColor(1, 0, 255, 0);
//       break;
//     case 6:
      
//       CircuitPlayground.setPixelColor(6, 0, 0, 255);
//       break;
//     case 10:
      
//       CircuitPlayground.setPixelColor(9, 50, 250, 100);
//       break;
//   }
//   delay(100);
//   CircuitPlayground.clearPixels();
// }
