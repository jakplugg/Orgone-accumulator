void FASTRUN outUpdateISR_DRUM_DEL(void) {
 
  DECLICK_CHECK();

  noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
  noiseTable[o1[0].phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

  NOISELIVE0();
  NOISELIVE1();

 
  delayCounter = delayCounter + 32;
  delayCounterShift = delayCounter >> 5 ;
  
  for (RrN = 0;RrN < 2;RrN ++){

    delayTimeShift0[RrN] = uint16_t(delayCounter - (delayTime0[RrN] << 4)) >> 5;
  
    //--------------------first osc envelope---------------------

  o7[RrN].phase_increment += o8[RrN].phase_increment;

  if (drum[RrN].envStep[0] == 0) {
    if (drum[RrN].st == 0) {
      drum[RrN].envTemp[0] = drum[RrN].envVal[0] = drum[RrN].envVal[2] = 1 << 30;//o6[RrN].wave << 15; //use front of wave as attack
      drum[RrN].envTemp[2] = drum[RrN].envVal[0] >> 14;
      o7[RrN].phase_increment = 0;
    }
    else {      
        drum[RrN].envTemp[0] = drum[RrN].envVal[0] = drum[RrN].envVal[2] = 1 << 30;
        drum[RrN].envTemp[2] = drum[RrN].envVal[0] >> 14;
        drum[RrN].envStep[0] = 1;
      
    }
  }

  else if (drum[RrN].envStep[0] == 1) {

    
    int32_t tempt = multiply_32x32_rshift32(drum[RrN].envVal[0], drum[RrN].d<<1);
    drum[RrN].envVal[0] = drum[RrN].envVal[0] - tempt;
    drum[RrN].envTemp[0] = drum[RrN].envVal[0]; 
    
    if (o7[RrN].phase_increment > drum[RrN].a && drum[RrN].envStep[2] == 0)drum[RrN].envStep[2] = 1;
    

    if (drum[RrN].envVal[0] <= 16390) drum[RrN].envStep[0] = 2;
  }

  if (drum[RrN].envStep[0] == 2) {
    drum[RrN].envVal[0] = 0;
    drum[RrN].envTemp[0] = 0;
    
    if (o7[RrN].phase_increment > drum[RrN].a && drum[RrN].envStep[2] == 0)drum[RrN].envStep[2] = 1;//o7 phase counts up the hold on the amplitude envelope.
    
  }

  //-----------------second half of ahd amplitude. h is by time

  if (drum[RrN].envStep[2] == 1) {

    if (drum[RrN].envVal[2] > enBreak){ drum[RrN].temph = multiply_32x32_rshift32(drum[RrN].envVal[2], drum[RrN].d);}
    else { drum[RrN].temph = multiply_32x32_rshift32(drum[RrN].envVal[2], drum[RrN].d>>drum[RrN].dB);}
    drum[RrN].envVal[2] = drum[RrN].envVal[2] - drum[RrN].temph;
    drum[RrN].envTemp[2] = drum[RrN].envVal[2] >> 14;
    //if (EffectEnOn_B)drum[RrN].envTemp[0] = drum[RrN].envVal[2] ;

    if (drum[RrN].envVal[2] <= 16390) drum[RrN].envStep[2] = 2;
  }

  if (drum[RrN].envStep[2] == 2) drum[RrN].envVal[2] = drum[RrN].envTemp[2] = 0;

  drum[RrN].envTemp[0]= multiply_32x32_rshift32(o1[RrN].phase_increment, drum[RrN].envTemp[0]>>4);

    //oscs
     o1[RrN].phase = o1[RrN].phase + o1[RrN].phase_increment + (o1[RrN].amp * drum[RrN].envTemp[0]);
  o1[RrN].phaseRemain = (o1[RrN].phase << 9) >> 17;
  o6[RrN].wave = ((int32_t)(((GWTlo1[o1[RrN].phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1[RrN].phase >> 23] * (GremLo)) >> 9)));
  o6[RrN].nextwave =  ((int32_t)(((GWTlo1[(o1[RrN].phase + nextstep) >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[(o1[RrN].phase + nextstep) >> 23] * (GremLo)) >> 9))) ;
  
  if (o6[RrN].wave > 26000) drum[RrN].st = 1;//trigger decay start at peak of wave 1  
  o6[RrN].wave = o6[RrN].wave + ((((o6[RrN].nextwave - o6[RrN].wave)) * o1[RrN].phaseRemain) >> 15);
  o1[RrN].wave = multiply_32x32_rshift32(drum[RrN].envVal[2], o6[RrN].wave); 

  
  //o1[RrN].wave = o1[RrN].wave * (drum[RrN].envVal[0] >> 14) >> 15;

  
  o6[RrN].phase =  EffectEnOn_C * ((o1[RrN].amp * drum[RrN].envTemp[1])); //borrowed unused osc 6 variable for drum pitch. turns on env 2 > pitch > oscs 2
  
  

    //oscs 2------------------------------------------

   delayTable0[RrN][delayCounterShift] = o1[RrN].wave + ((delayTable0[RrN][delayTimeShift0[RrN]] * delayFB0[RrN]) >> 11);

    o1[RrN].wave = ((((o1[RrN].wave) * (2047 - CZMix))) >> 9) + ((delayTable0[RrN][delayTimeShift0[RrN]] * CZMix) >> 9);
  }

  FinalOut = declickValue + (((o1[0].wave + o1[1].wave) * declickRampIn) >> 12);

  analogWrite(aout2, FinalOut + 32750);



}



