void FASTRUN outUpdateISR_DRUM(void) {
  //noInterrupts();

  //digitalWriteFast (oSQout,0);//temp testing OC


  SUBMULOC();
  DECLICK_CHECK();



  noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

  NOISELIVE0();
  NOISELIVE1();

  //envs

  //--------------------first osc envelope---------------------

  o7.phase_increment += o8.phase_increment;

  if (drum_envStep[0] == 0) {
    if (drum_st == 0) {
      drum_envTemp[0] = drum_envVal[0] = drum_envVal[2] = 1 << 30;//o6.wave << 15; //use front of wave as attack
      drum_envTemp[2] = drum_envVal[0] >> 14;
      o7.phase_increment = 0;
    }
    else {      
        drum_envTemp[0] = drum_envVal[0] = drum_envVal[2] = 1 << 30;
        drum_envTemp[2] = drum_envVal[0] >> 14;
        drum_envStep[0] = 1;
      
    }
  }

  else if (drum_envStep[0] == 1) {

    
    int32_t tempt = multiply_32x32_rshift32(drum_envVal[0], drum_d<<1);
    drum_envVal[0] = drum_envVal[0] - tempt;
    drum_envTemp[0] = drum_envVal[0]; 
    
    if (o7.phase_increment > drum_a && drum_envStep[2] == 0)drum_envStep[2] = 1;
    

    if (drum_envVal[0] <= 16390) drum_envStep[0] = 2;
  }

  if (drum_envStep[0] == 2) {
    drum_envVal[0] = 0;
    drum_envTemp[0] = 0;
    
    if (o7.phase_increment > drum_a && drum_envStep[2] == 0)drum_envStep[2] = 1;//o7 phase counts up the hold on the amplitude envelope.
    
  }

  //-----------------second half of ahd amplitude. h is by time

  if (drum_envStep[2] == 1) {

    if (drum_envVal[2] > enBreak){ temph = multiply_32x32_rshift32(drum_envVal[2], drum_d);}
    else { temph = multiply_32x32_rshift32(drum_envVal[2], drum_d>>drum_dB);}
    drum_envVal[2] = drum_envVal[2] - temph;
    drum_envTemp[2] = drum_envVal[2] >> 14;
    //if (EffectEnOn_B)drum_envTemp[0] = drum_envVal[2] ;

    if (drum_envVal[2] <= 16390) drum_envStep[2] = 2;
  }

  if (drum_envStep[2] == 2) drum_envVal[2] = drum_envTemp[2] = 0;



  //--------------detuned drums envelope------------


  if (drum_envStep[1] == 0) {
    if (drum_st == 0) {
      drum_envVal[1] = 1 << 30;//o6.wave << 14;
      drum_envTemp[1] = drum_envVal[1] >> 14;
    }
    else {
      drum_envVal[1] = 1 << 30;
      drum_envTemp[1] = drum_envVal[1] >> 14;
      drum_envStep[1] = 1;      
    }
  }

  else if (drum_envStep[1] == 1) {
    drum_envTemp[1] = drum_envVal[1] >> 14;
    if (drum_envVal[1] > enBreak) {tempr = multiply_32x32_rshift32(drum_envVal[1], drum_d2);}
    else {tempr = multiply_32x32_rshift32(drum_envVal[1], drum_d2>>drum_d2B);} 
    drum_envVal[1] = drum_envVal[1] - tempr;
    drum_envTemp[1] = drum_envVal[1] >> 14;

    if (drum_envVal[1] <= 16390) drum_envStep[1] = 2;
  }

  if (drum_envStep[1] == 2) drum_envVal[1] = 0;

  drum_envTemp[0]= multiply_32x32_rshift32(o1.phase_increment, drum_envTemp[0]>>4);
   
  //oscs
  o1.phase = o1.phase + o1.phase_increment + o10.phase + (o1.amp * drum_envTemp[0]);
  o1.phaseRemain = (o1.phase << 9) >> 17;
  o6.wave = ((int32_t)(((GWTlo1[o1.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1.phase >> 23] * (GremLo)) >> 9)));
  o6.nextwave =  ((int32_t)(((GWTlo1[(o1.phase + nextstep) >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[(o1.phase + nextstep) >> 23] * (GremLo)) >> 9))) ;
  
  if (o6.wave > 30000) drum_st = 1;//trigger decay start at peak of wave 1  
  o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o1.phaseRemain) >> 15);
  o1.wave = multiply_32x32_rshift32(drum_envVal[2], o6.wave);
  
//   if (o1.phase >> 31 == 0) o1.pulseAdd = o6.wave;
//  else o1.pulseAdd = 0;
//  o1.pulseAdd = multiply_32x32_rshift32(drum_envVal[1], o1.pulseAdd);
  o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o1.phaseRemain) >> 15);
  
  //o1.wave = o1.wave * (drum_envVal[0] >> 14) >> 15;

  
  o6.phase =  EffectEnOn_C * ((o1.amp * drum_envTemp[1])); //borrowed unused osc 6 variable for drum pitch. turns on env 2 > pitch > oscs 2
  
  if (FMmodeOn) o9.phase_increment = multiply_32x32_rshift32(drum_envVal[1], (o6.phase_increment<<2)); //make the envelope modulate the complexity amount with FM pressed.
  else o9.phase_increment = o6.phase_increment;

  //oscs 2------------------------------------------

  o2.phase = o2.phase + o2.phase_increment + o6.phase  +(o9.phase_increment * o6.wave);
  o2.phaseRemain = (o2.phase << 9) >> 17;
  o8.wave = ((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) ;
  o8.nextwave =  ((int32_t)(((GWThi1[(o2.phase+nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o2.phase+nextstep) >> 23] * (GremHi)) >> 9)));
  o8.wave = o8.wave + ((((o8.nextwave - o8.wave)) * o2.phaseRemain) >> 15);
  o2.wave = multiply_32x32_rshift32(drum_envVal[1], o8.wave);

  o3.phase = o3.phase + o3.phase_increment + o6.phase +(o9.phase_increment * o8.wave);
  o3.phaseRemain = (o3.phase << 9) >> 17;
  o9.wave = ((int32_t)(((GWThi1[o3.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o3.phase >> 23] * (GremHi)) >> 9))) ;
  o9.nextwave =  ((int32_t)(((GWThi1[(o3.phase+nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o3.phase+nextstep) >> 23] * (GremHi)) >> 9)));
  o9.wave = o9.wave + ((((o9.nextwave - o9.wave)) * o3.phaseRemain) >> 15);
  o3.wave = multiply_32x32_rshift32(drum_envVal[1], o9.wave);

  o4.phase = o4.phase + o4.phase_increment + o6.phase +(o9.phase_increment * o9.wave);
  o4.phaseRemain = (o4.phase << 9) >> 17;
  o10.wave = ((int32_t)(((GWThi1[o4.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o4.phase >> 23] * (GremHi)) >> 9))) ;
  o10.nextwave =  ((int32_t)(((GWThi1[(o4.phase+nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o4.phase+nextstep) >> 23] * (GremHi)) >> 9)));
  o10.wave = o10.wave + ((((o10.nextwave - o10.wave)) * o4.phaseRemain) >> 15);
  o4.wave = multiply_32x32_rshift32(drum_envVal[1], o10.wave);


  o5.phase = o5.phase + o5.phase_increment + o6.phase +(o9.phase_increment * o10.wave);
  o5.phaseRemain = (o5.phase << 9) >> 17;
  o12.wave = (sinTable[o5.phase >> WTShiftMid]);//because noiselive sometimes wont trigger properly
  if (o12.wave > 30000) drum_st = 1; //start envelope at top of wave, o5 is the highest pitch so will get there first..
  o7.wave = ((int32_t)(((GWThi1[o5.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o5.phase >> 23] * (GremHi)) >> 9))) ;
  o7.nextwave = ((GWThi1[(o5.phase + nextstep) >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[(o5.phase + nextstep) >> 23] * (GremHi)) >> 9);
  o7.wave = o7.wave + ((((o7.nextwave - o7.wave)) * o5.phaseRemain) >> 15);
  o5.wave = multiply_32x32_rshift32(drum_envVal[1], o7.wave);



  o8.wave = ((o5.wave + o2.wave + o3.wave + o4.wave) >> 2);

  o1.wave = ((((o1.wave) * (2047 - CZMix))) >> 9) + ((o8.wave * CZMix) >> 9);
  
  FinalOut = declickValue + ((o1.wave * declickRampIn) >> 12);
  
  analogWrite(aout2, FinalOut + 32750);



}



