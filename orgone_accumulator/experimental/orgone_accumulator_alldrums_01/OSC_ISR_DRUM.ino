void FASTRUN outUpdateISR_DRUM(void) {
  //noInterrupts();

  //digitalWriteFast (oSQout,0);//temp testing OC



  DECLICK_CHECK();



  noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
  noiseTable[o1[0].phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

  NOISELIVE0();
  NOISELIVE1();

  //envs

  //--------------------first osc envelope---------------------
  for (RrN = 0;RrN < 2;RrN ++){

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



  //--------------detuned drums envelope------------


  if (drum[RrN].envStep[1] == 0) {
    if (drum[RrN].st == 0) {
      drum[RrN].envVal[1] = 1 << 30;//o6[RrN].wave << 14;
      drum[RrN].envTemp[1] = drum[RrN].envVal[1] >> 14;
    }
    else {
      drum[RrN].envVal[1] = 1 << 30;
      drum[RrN].envTemp[1] = drum[RrN].envVal[1] >> 14;
      drum[RrN].envStep[1] = 1;      
    }
  }

  else if (drum[RrN].envStep[1] == 1) {
    drum[RrN].envTemp[1] = drum[RrN].envVal[1] >> 14;
    if (drum[RrN].envVal[1] > enBreak) {drum[RrN].tempr = multiply_32x32_rshift32(drum[RrN].envVal[1], drum[RrN].d2);}
    else {drum[RrN].tempr = multiply_32x32_rshift32(drum[RrN].envVal[1], drum[RrN].d2>>drum[RrN].d2B);} 
    drum[RrN].envVal[1] = drum[RrN].envVal[1] - drum[RrN].tempr;
    drum[RrN].envTemp[1] = drum[RrN].envVal[1] >> 14;

    if (drum[RrN].envVal[1] <= 16390) drum[RrN].envStep[1] = 2;
  }

  if (drum[RrN].envStep[1] == 2) drum[RrN].envVal[1] = 0;

  drum[RrN].envTemp[0]= multiply_32x32_rshift32(o1[RrN].phase_increment, drum[RrN].envTemp[0]>>4);
   
  //oscs
  o1[RrN].phase = o1[RrN].phase + o1[RrN].phase_increment + o10[RrN].phase + (o1[RrN].amp * drum[RrN].envTemp[0]);
  o1[RrN].phaseRemain = (o1[RrN].phase << 9) >> 17;
  o6[RrN].wave = ((int32_t)(((GWTlo1[o1[RrN].phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1[RrN].phase >> 23] * (GremLo)) >> 9)));
  o6[RrN].nextwave =  ((int32_t)(((GWTlo1[(o1[RrN].phase + nextstep) >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[(o1[RrN].phase + nextstep) >> 23] * (GremLo)) >> 9))) ;
  
  if (o6[RrN].wave > 26000) drum[RrN].st = 1;//trigger decay start at peak of wave 1  
  o6[RrN].wave = o6[RrN].wave + ((((o6[RrN].nextwave - o6[RrN].wave)) * o1[RrN].phaseRemain) >> 15);
  o1[RrN].wave = multiply_32x32_rshift32(drum[RrN].envVal[2], o6[RrN].wave);

  
  o6[RrN].phase =  EffectEnOn_C * ((o1[RrN].amp * drum[RrN].envTemp[1])); //borrowed unused osc 6 variable for drum pitch. turns on env 2 > pitch > oscs 2
  
  if (FMmodeOn) o9[RrN].phase_increment = multiply_32x32_rshift32(drum[RrN].envVal[1], (o6[RrN].phase_increment<<2)); //make the envelope modulate the complexity amount with FM pressed.
  else o9[RrN].phase_increment = o6[RrN].phase_increment;

  //oscs 2------------------------------------------

  o2[RrN].phase = o2[RrN].phase + o2[RrN].phase_increment + o6[RrN].phase  +(o9[RrN].phase_increment * o6[RrN].wave);
  o2[RrN].phaseRemain = (o2[RrN].phase << 9) >> 17;
  o8[RrN].wave = ((int32_t)(((GWThi1[o2[RrN].phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2[RrN].phase >> 23] * (GremHi)) >> 9))) ;
  o8[RrN].nextwave =  ((int32_t)(((GWThi1[(o2[RrN].phase+nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o2[RrN].phase+nextstep) >> 23] * (GremHi)) >> 9)));
  o8[RrN].wave = o8[RrN].wave + ((((o8[RrN].nextwave - o8[RrN].wave)) * o2[RrN].phaseRemain) >> 15);
  o2[RrN].wave = multiply_32x32_rshift32(drum[RrN].envVal[1], o8[RrN].wave);

  o3[RrN].phase = o3[RrN].phase + o3[RrN].phase_increment + o6[RrN].phase +(o9[RrN].phase_increment * o8[RrN].wave);
  o3[RrN].phaseRemain = (o3[RrN].phase << 9) >> 17;
  o9[RrN].wave = ((int32_t)(((GWThi1[o3[RrN].phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o3[RrN].phase >> 23] * (GremHi)) >> 9))) ;
  o9[RrN].nextwave =  ((int32_t)(((GWThi1[(o3[RrN].phase+nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o3[RrN].phase+nextstep) >> 23] * (GremHi)) >> 9)));
  o9[RrN].wave = o9[RrN].wave + ((((o9[RrN].nextwave - o9[RrN].wave)) * o3[RrN].phaseRemain) >> 15);
  o3[RrN].wave = multiply_32x32_rshift32(drum[RrN].envVal[1], o9[RrN].wave);

  o4[RrN].phase = o4[RrN].phase + o4[RrN].phase_increment + o6[RrN].phase +(o9[RrN].phase_increment * o9[RrN].wave);
  o4[RrN].phaseRemain = (o4[RrN].phase << 9) >> 17;
  o10[RrN].wave = ((int32_t)(((GWThi1[o4[RrN].phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o4[RrN].phase >> 23] * (GremHi)) >> 9))) ;
  o10[RrN].nextwave =  ((int32_t)(((GWThi1[(o4[RrN].phase+nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o4[RrN].phase+nextstep) >> 23] * (GremHi)) >> 9)));
  o10[RrN].wave = o10[RrN].wave + ((((o10[RrN].nextwave - o10[RrN].wave)) * o4[RrN].phaseRemain) >> 15);
  o4[RrN].wave = multiply_32x32_rshift32(drum[RrN].envVal[1], o10[RrN].wave);


  o5[RrN].phase = o5[RrN].phase + o5[RrN].phase_increment + o6[RrN].phase +(o9[RrN].phase_increment * o10[RrN].wave);
  o5[RrN].phaseRemain = (o5[RrN].phase << 9) >> 17;
  o12[RrN].wave = (sinTable[o5[RrN].phase >> WTShiftMid]);//because noiselive sometimes wont trigger properly
  if (o12[RrN].wave > 30000) drum[RrN].st = 1; //start envelope at top of wave, o5 is the highest pitch so will get there first..
  o7[RrN].wave = ((int32_t)(((GWThi1[o5[RrN].phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o5[RrN].phase >> 23] * (GremHi)) >> 9))) ;
  o7[RrN].nextwave = ((GWThi1[(o5[RrN].phase + nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o5[RrN].phase + nextstep) >> 23] * (GremHi)) >> 9);
  o7[RrN].wave = o7[RrN].wave + ((((o7[RrN].nextwave - o7[RrN].wave)) * o5[RrN].phaseRemain) >> 15);
  o5[RrN].wave = multiply_32x32_rshift32(drum[RrN].envVal[1], o7[RrN].wave);



  o8[RrN].wave = ((o5[RrN].wave + o2[RrN].wave + o3[RrN].wave + o4[RrN].wave) >> 2);

  o1[RrN].wave = ((((o1[RrN].wave) * (2047 - CZMix))) >> 9) + ((o8[RrN].wave * CZMix) >> 9);
  }
  
  FinalOut = declickValue + (((o1[0].wave + o1[1].wave)* declickRampIn) >> 12);
  
  analogWrite(aout2, FinalOut + 32750);



}



