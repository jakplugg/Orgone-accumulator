//neutron orgone accumulator config file. 

#define TUNEMULT 73750  
//this is the base frequency. halving it will lower the entire oscillator by 1 octave 

#define NOTESIZE 72.0 
// note resolution. lower value will give wider oscillator range, higher will give better resolution
//you will need to recalibrate the v/oct trimmer if you adjust this. decimal is important, even if zero.

#define LED_COMP 1000 //dim the LEDSs higher number = lower brightness.

#define LED_MODESWITCH_TIME 5000 //time LEDs stay on when mode is switched in main loop cycles, about 2-3000 per second depending on am/fm effects etc.

//LED compensation. adjusts how the LEDs fade across positions

#define FX_SWITCH 0

//0 = momentary
//1 = toggle

#define FX_N 7 //7 max (actually 8 due to binary counting)

//assign effects to slots in the rotation

#define FX0 0
#define FX1 1
#define FX2 3
#define FX3 2
#define FX4 4
#define FX5 5
#define FX6 6
#define FX7 8

//0  original orgone detune 
//1 original orgone detune with prime
//2 delay effect
//3 pulsar
//4 bit crush
//5 wave folding
//6 modmod the modulation waveform can be changed with FX and FX CV
//7 chords (equal temprement)
//8 chords (just tuning)


#define PWM_SUB 2

//divider to use the PWM as a sub oscillator. DO NOT ENTER ZERO.
//1 = same as main.
//2 = 1 octave down
//4 = 2 octaves etc. 

#define PWM_MINIMUM 4

//128ths of a cycle the thinnest pulse can be. 0 will allow silence to fall.

#define PWM_CONTROL 1

//0 = position control and CV controls PWM across range
//1 = index controls PWM minimum PW to 50%, modified by index CV

#define FX_SELECT_EXT 0

//do not change, for effect select sub panel.





 




 
