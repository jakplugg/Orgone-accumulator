void FASTRUN outUpdateISR_TWANG(void) {
 

  noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
  noiseTable[o1[0].phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

  NOISELIVE0();
  NOISELIVE1();

 
  delayCounter = delayCounter + 32;
  delayCounterShift = delayCounter >> 5 ;
  
  for (rN = 0;rN < NumVoices;rN ++){

    delayTimeShift0[rN] = uint16_t(delayCounter - (delayTime0[rN] << 4)) >> 5;
  
    //--------------------osc envelope---------------------

  o3[rN].phase_increment += o4[rN].phase_increment;

  if (twang[rN].envStep[0] == 0) {
    if (twang[rN].st == 0) {
      twang[rN].envTemp[0] = twang[rN].envVal[0] = twang[rN].envVal[2] = 1 << 30;//o6[rN].wave << 15; //use front of wave as attack
      twang[rN].envTemp[2] = twang[rN].envVal[0] >> 14;
      o3[rN].phase_increment = 0;
    }
    else {      
        twang[rN].envTemp[0] = twang[rN].envVal[0] = twang[rN].envVal[2] = 1 << 30;
        twang[rN].envTemp[2] = twang[rN].envVal[0] >> 14;
        twang[rN].envStep[0] = 1;
      
    }
  }

  else if (twang[rN].envStep[0] == 1) {

    
    int32_t tempt = multiply_32x32_rshift32(twang[rN].envVal[0], twang[rN].d<<1);
    twang[rN].envVal[0] = twang[rN].envVal[0] - tempt;
    twang[rN].envTemp[0] = twang[rN].envVal[0]; 
    
    if (o3[rN].phase_increment > twang[rN].a && twang[rN].envStep[2] == 0)twang[rN].envStep[2] = 1;
    

    if (twang[rN].envVal[0] <= 16390) twang[rN].envStep[0] = 2; 
  }

  if (twang[rN].envStep[0] == 2) {
    twang[rN].envVal[0] = 0;
    twang[rN].envTemp[0] = 0;    
    
    if (o3[rN].phase_increment > twang[rN].a && twang[rN].envStep[2] == 0)twang[rN].envStep[2] = 1;//o7 phase counts up the hold on the amplitude envelope.
    
  }

  //-----------------second half of ahd amplitude. h is by time

  if (twang[rN].envStep[2] == 1) {

    if (twang[rN].envVal[2] > enBreak){ twang[rN].temph = multiply_32x32_rshift32(twang[rN].envVal[2], twang[rN].d);}
    else { twang[rN].temph = multiply_32x32_rshift32(twang[rN].envVal[2], twang[rN].d>>twang[rN].dB);}
    twang[rN].envVal[2] = twang[rN].envVal[2] - twang[rN].temph;
    twang[rN].envTemp[2] = twang[rN].envVal[2] >> 14;
    //if (EffectEnOn_B)twang[rN].envTemp[0] = twang[rN].envVal[2] ;

    if (twang[rN].envVal[2] <= 16390) twang[rN].envStep[2] = 2;
  }

  if (twang[rN].envStep[2] == 2){
    twang[rN].envVal[2] = twang[rN].envTemp[2] = 0;
    o1[rN].phase = 0;
  }

  twang[rN].envTemp[0]= multiply_32x32_rshift32(o1[rN].phase_increment, twang[rN].envTemp[0]>>4);

    //oscs
     o1[rN].phase = o1[rN].phase + o1[rN].phase_increment ;
  o1[rN].phaseRemain = (o1[rN].phase << 9) >> 17;
  o6[rN].wave = (int32_t)waveTableLoLink[o1[rN].phase >> 23] ;
  o6[rN].nextwave =  (int32_t)waveTableLoLink[(o1[rN].phase + nextstep) >> 23] ;
  
  if (o6[rN].wave > 26000) twang[rN].st = 1;//trigger decay start at peak of wave 1  
  o6[rN].wave = o6[rN].wave + ((((o6[rN].nextwave - o6[rN].wave)) * o1[rN].phaseRemain) >> 15);
  o2[rN].wave = multiply_32x32_rshift32(twang[rN].envVal[2], o6[rN].wave);
  
  
  o6[rN].phase =  EffectEnOn_C * ((o1[rN].amp * twang[rN].envTemp[1])); //borrowed unused osc 6 variable for drum pitch. turns on env 2 > pitch > oscs 2
  
  

    //oscs 2------------------------------------------

   delayTable0[rN][delayCounterShift] = (o2[rN].wave>> 4) + ((delayTable0[rN][delayTimeShift0[rN]] * delayFB0[rN]) >> 11);

    o1[rN].wave = ((((o2[rN].wave) * (2047 - CZMix))) >> 9) + ((delayTable0[rN][delayTimeShift0[rN]] * CZMix) >> 9);
  }

  FinalOut = (o1[0].wave + o1[1].wave + o1[2].wave+ o1[3].wave);

  analogWrite(aout2, FinalOut + 32750);



}



