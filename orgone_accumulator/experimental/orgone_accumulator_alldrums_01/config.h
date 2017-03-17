//neutron orgone accumulator alldrums config file. 


#define TUNEMULT 159000 
//#define TUNEMULT 5900000
//this is the base frequency. halving it will lower the entire oscillator by 1 octave 
//real frequency is sent to the broadcast application for tuning

extern const int tuneStep = 1;//this is how many semitones the tuning knob steps in.

#define NOTESIZE 72.0 
// note resolution. lower value will give wider oscillator range, higher will give better resolution
//you will need to recalibrate the v/oct trimmer if you adjust this. decimal is important, even if zero.

#define LED_COMP 1000 //dim the LEDSs higher number = lower brightness. (only for the position LEDs)

//DIY hardware 1.x boards--------------------------------------------------------------------start

#define LED_MODESWITCH_TIME 3000 //time LEDs stay on when effect is switched in main loop cycles, about 2-3000 per second depending on am/fm effects etc.

//LED compensation. adjusts how the LEDs fade across positions

//DIY hardware 1.x boards--------------------------------------------------------------------end
//everyone gets all effects now.

#define FX_SWITCH 0 //dont change for HW2!

//0 = momentary
//1 = toggle

extern const int TUNELOCK_SWITCH = 1;
//0 = tune lock
//1 = pulsar  replaces tune lock with pulsar, reducing FX steps back to 8






