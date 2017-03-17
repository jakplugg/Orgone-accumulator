
//#include "SPI.h"
#include "ADC.h"
#include "ADC_Module.h"
//#include "RingBuffer.h"
//#include "RingBufferDMA.h"

/* ----------------------------------Description-------------------------------
 *              Lo Fi Mushroom delay firmware for DIY orgone only 0.01 
 *                                BY NEUTRON SOUND
 *  
 *                                    *                 
 *                 suggested patch. audio source > scan position 
 *                 v/oct from sequencer or keyboard > v/oct
 *                 gate from sequencer or keyboard > reset/gate input               
 *                 main out > output
 *                 
 *                 controls
 *                 lo wave select > delay multiplier (bug at max)
 *                 scan position attenuverter > audio input level
 *                 scan position pot > delay mix
 *                 tune and fine same as normal
 *                 no CVs yet.
 *             
  
 this will only work half decent at overclock = 144Mhz, still a bit crap at high pitches.
 this is a "playable" delay prototype adapted to DIY orgone accumulator.
 the clock for the delay is 1v/octave. reset is "hold"
 pitch and fine tune delay time

 scan position is audio input you might want to remove the capacitor c
 detune/effect is feedback

 if you want better audio then you need to remove C26 which is a band limiter for the scan position CV input,
 or as a compromise,  replace it with 1n
*/ 
   


// Includes

#define Hi_counter_pin 11
#define Voct_pin 14
#define Coarse_tune_pin A11
#define Fine_tune_pin 23
#define Audio_input_pin 27
#define Delay_counts_pin A10
#define Delay_mix_pin 22
#define Double_mix_pin 21
#define Double_time_pin 20
#define Diffuse_mix_pin 17
#define Delay_feedback_pin 18
#define gateIn 12
#define diffuse_button 1

#define cast_uint32_t static_cast<uint32_t>

ADC *adc = new ADC();
const uint8_t ISRrate = 8;
const uint8_t diffuser_table = 4;
uint8_t ARC,INC,Ntest0,Nold0,Ntest1,Nold1;
uint16_t ftune;
uint8_t gateOn = 0,diffuseMode;
uint32_t Hi_count0 = 0,Hi_count1 = 0,doubleTime;
uint32_t Hi_count0_rate = 0,Hi_count1_rate = 0;
int32_t audioIn0,finalOut0,delayOut0,delayMix0,diffuseMix,diffuseOut;
int32_t audioIn1,finalOut1,delayOut1,delayMix1,finalOut;
uint8_t Monitor = 0;

float dtuner,inCV,inCVraw,inputScaler,tuner,inputVOct;

int16_t delayTable0[4096],delayTable1[4096];
uint16_t delayCounter0 = 0,delayCounter1 = 0;
uint16_t delayFeedback = 0;
uint16_t delayCounterShift0 = 0,delayCounterShift1 = 0;
uint16_t delayTimeShift0 = 0,delayTimeShift1 = 0;
uint16_t delayCounts = 512;

uint16_t diffuseCountShift[4]; 
uint16_t diffuseCount[] = {2,3,5,7,11,13,17,19,23,29,31,37};
uint16_t diffuseTimeShift[4];

const int numreadingsCV = 16; 
float readingsaInCV[numreadingsCV];
int indexInCV = 0;
float totalInCV;
float averageaInCV;

IntervalTimer Sample_timer;

//void Delay_increment(void);
void Hi_counter(void); 
static inline float fasterpow2 (float p);
static inline float fastpow2 (float p);
void READSLOW(void);

void setup() {
  if (Monitor) {
    Serial.begin(115200);
  }


  adc->setAveraging(32  , ADC_0); // set number of averages    8
  adc->setResolution(12 , ADC_0); // set bits of resolution    10
  adc->setAveraging(2  , ADC_1); // set number of averages    8
  adc->setResolution(12 , ADC_1); // set bits of resolution    10
  adc->setConversionSpeed(ADC_VERY_HIGH_SPEED , ADC_0);  // ADC_VERY_HIGH_SPEED lower speeds are more accurate, try med speed if it warbles too much.
  adc->setSamplingSpeed(ADC_VERY_HIGH_SPEED  , ADC_0);  // ADC_LOW_SPEED
  adc->setConversionSpeed(ADC_VERY_HIGH_SPEED , ADC_1);  // ADC_HIGH_SPEED
  adc->setSamplingSpeed(ADC_VERY_HIGH_SPEED  , ADC_1);  // ADC_MED_SPEED
  adc->enableDMA(ADC_0);
  adc->enableDMA(ADC_1);
  
  //adc->startContinuous(LFO1_width_POT);
   adc->setReference(ADC_REF_EXT, ADC_0);
  adc->setReference(ADC_REF_EXT, ADC_1);

  //pinMode(Audio_input_pin  , INPUT);
  pinMode(A14  , OUTPUT);
  pinMode(Hi_counter_pin  , OUTPUT);
  pinMode(gateIn , INPUT);
  pinMode(diffuse_button , INPUT);

  analogWriteResolution (16);
 Sample_timer.priority(64); 

  Sample_timer.begin(Hi_counter, ISRrate);
  //attachInterrupt(Hi_counter_pin,Delay_increment, RISING);
    attachInterrupt(gateIn, gateISR, CHANGE);

    adc->startContinuous(Audio_input_pin);
}

void loop() {
  ARC ++;
  if (ARC >= 8) ARC = 0; 
  READSLOW();
 
  inCVraw = (float)(adc->analogRead(Voct_pin)*2.0); //v/oct input
  
  tuner = (float)(inCV + dtuner); 
   
  inputScaler = float(tuner / 864.0);

  inputVOct = fastpow2(inputScaler); //"real time" exponentiation of CV input! (powf is single precision float power function) comment out if using powf version above

   Hi_count0_rate = inputVOct * 5900000;  
   Hi_count1_rate = Hi_count0_rate - (doubleTime<<5);  

   //Serial.println(inCV);

   totalInCV = totalInCV - readingsaInCV[indexInCV];
  readingsaInCV[indexInCV] = inCVraw; 
  totalInCV = totalInCV + readingsaInCV[indexInCV];  
  indexInCV = indexInCV + 1;
  if (indexInCV >= numreadingsCV) indexInCV = 0;  
  inCV = totalInCV / numreadingsCV;

  for (INC = 0;INC < 4;INC ++){
    diffuseCountShift[INC] = (diffuseCount[INC] * delayCounts)<<4;
  }
 
  
}//end of main loop


