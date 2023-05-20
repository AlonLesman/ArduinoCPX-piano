/*
The InstrumentalCup 
  Demonstrates a musical instrument that plays from a cup using 
  hand movements, light exposure and touch. The playing is done using the Mozzi libarary
  and 3 different oscilators, which together result in a tool that plays different sounds 
  depending on the movement of the player's hands towards the cup and touch. 
  
  The instrument uses 3 inputs: 
    1. light sensor - the value read from the analog input is mapped
    to a range that is used in the 3rd oscilator 
    2. Capacitance sensor - Input pin A5 is used to read input and 
    use value to set frequency for the carrier oscilator 
    3. 
  The output is the speaker on the board which is attached to an amplifier
  
  you are welcome to watch an example of live performance at the link!
  Video link: https://youtu.be/jXHM_VImgRk  
  Created By:
  Student1_Alon_Lesman #208608018
  Student2_Kim_Walfisz #206557357
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template 
#include <tables/cos2048_int8.h> // table for oscillators to play 
#include <Smooth.h>
#include <AutoMap.h> // maps inputs to a range
#include <Adafruit_CircuitPlayground.h>


// map AutoRanged analog inputs to desired ranges 
AutoMap kMapCarrierFreq(0, 1023, 22, 440); // desired carrier frequency 
// values are inverted for reverse dynamics
AutoMap kMapIntensity(0, 1023, 700, 10); // desired intensity
AutoMap kMapModSpeed(0,1023, 10000, 1);

//set up oscilators
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aCarrier(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aModulator(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kIntensityMod(COS2048_DATA);

#define TOUCH_SENSOR_INPUT A5 // set input for capacitive sensor to analog pin A5
#define LIGHT_INPUT A8 // set input for light sensor to A8 
int mod_ratio = 5; // brightness 
long fm_intensity; // carries control info from updateControl to updateAudio

// smoothing for intensity to remove clicks on transitions
float smoothness = 0.95f;
Smooth <long> aSmoothIntensity(smoothness);

void setup(){
  startMozzi(); 
  CircuitPlayground.begin();
}

void updateControl(){
  int input_value = mozziAnalogRead(TOUCH_SENSOR_INPUT); // read value from pin 
  int carrier_frequency = kMapCarrierFreq(input_value); // map the input to carrier frequency
  int modulator_frequency = carrier_frequency * mod_ratio; //calculate the modulation frequency to stay in ratio

  // set the FM oscillator frequencies
  aCarrier.setFreq(carrier_frequency);
  aModulator.setFreq(modulator_frequency);
  
  int lightSensorValue = (int)analogRead(LIGHT_INPUT); // read the light sensor value 
  int mapped_lightValue = kMapIntensity(lightSensorValue);

  // calculate the fm_intensity
  fm_intensity = ((long)mapped_lightValue * (kIntensityMod.next()+128))>>8; // shift back to range after 8 bit multiply
  // read the touch sensor input pin
  int TouchSensor_value= (int)analogRead(TOUCH_SENSOR_INPUT); // value is 0-1023
  float mod_speed = (float)kMapModSpeed(TouchSensor_value)/1000;
  kIntensityMod.setFreq(mod_speed);
}

int updateAudio(){
  long modulation = aSmoothIntensity.next(fm_intensity) * aModulator.next();
  return aCarrier.phMod(modulation);
}

void loop(){
  audioHook();
}