void FASTRUN outUpdateISR_PULSAR_TWIN(void) {

  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((8192 - delayTime) << 3)) >> 4;


  SUBMULOC();
  DECLICK_CHECK();
  NOISELIVE0();
  NOISELIVE1();


 o1.phase = o1.phase + o1.phase_increment;
            
      o4.phase = o1.phase + o1.phaseOffset;
      
      if (o1.phaseOld > o1.phase) {
        o3.phase = (uint32_t)((o3.phase_increment * o1.phase) >> Temporal_Shift_CZ);
        o2.phase = (uint32_t)((o2.phase_increment * o1.phase) >> Temporal_Shift_CZ);
      }
      if (o4.phase < (o1.phase_increment<<1)) {
       o5.phase =  (uint32_t)((o2.phase_increment * o4.phase) >> Temporal_Shift_CZ);
    o6.phase =  (uint32_t)((o6.phase_increment * o4.phase) >> Temporal_Shift_CZ);
      }
      o1.phaseOld = o1.phase;
      o4.phaseOld = o4.phase;
      

      o2.phase = o2.phase +  o2.phase_increment + ((o10.wave<<10) * FMmodeOn);
      o2.phaseRemain = (o2.phase << 9) >> 17; //used for fake interpolation
     

     if (o3.phase < 2147483647) {
        o3.phase = o3.phase + o3.phase_increment ;
        o3.wave = (PENV[o3.phase >> 23]);
        o3.nextwave =  (PENV[(o3.phase + nextstep) >> 23]);
      }
      else {
        o3.wave = 0;
        o3.nextwave =  0;
      }
        
    
    

      o3.phaseRemain = (o3.phase << 9) >> 17;


      o5.phase = o5.phase +  o2.phase_increment + ((o10.wave<<10) * FMmodeOn);
      o5.phaseRemain = (o5.phase << 9) >> 17; //used for fake interpolation
      //o4.phaseRemain = (o4.phase << 9) >> 17;

      if (o6.phase < 2147483647) {
        o6.phase = o6.phase + o6.phase_increment ;
        o6.wave = (PENV[o6.phase >> 23]);
        o6.nextwave =  (PENV[(o6.phase + nextstep) >> 23]);
      }
      else {
        o6.wave = 0;
        o6.nextwave =  0;
      }
     

      o6.phaseRemain = (o6.phase << 9) >> 17;


  switch (oscMode) {

    //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
    case 0:


      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o5.wave = (
                  (((int32_t)(((GWThi1[o5.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o5.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o5.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o5.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o5.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o5.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o5.nextwave = (
                      (((int32_t)(((GWThi1[(o5.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o5.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o5.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o5.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o5.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o5.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      break;

    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
    case 2:

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o5.wave = (

                  (((int32_t)(((GWTlo1[o5.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o5.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o5.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o5.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o5.nextwave = (

                      (((int32_t)(((GWTlo1[(o5.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o5.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o5.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o5.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      break;

    //-----------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------
    case 1:



      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o5.wave = (
                  (((int32_t)(((GWThi1[o5.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o5.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o5.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o5.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o5.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o5.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;

      o5.nextwave = (
                      (((int32_t)(((GWThi1[(o5.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o5.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o5.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o5.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o5.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o5.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 15;


      break;

    //-----------------------------------------------ALT CZ MODE OSCILLATORS-----------------------------------------------
    case 3:

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o5.wave = (

                  (((int32_t)(((GWTlo1[o5.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o5.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o5.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o5.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o5.nextwave = (

                      (((int32_t)(((GWTlo1[(o5.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o5.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o5.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o5.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      break;

  }

  o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
  o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
  o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);
  o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o6.phaseRemain) >> 15);

  o1.wave =   (o2.wave * o3.wave) >> 11;
  o4.wave =   (o5.wave * o6.wave) >> 11;

  o9.wave = ((32767- abs(o3.wave )) * mixEffect) >> 11; //get remaining headroom from pulse envelope

  o8.wave = (-o1.wave ) + ((o4.wave * o9.wave) >> 15); //add delayed wave in remaining headroom.

  FinalOut = declickValue + ((o8.wave * declickRampIn) >> 12);
  analogWrite(aout2, FinalOut + 32000);
}

void FASTRUN outUpdateISR_WAVE_TWIN(void) {

  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((8192 - delayTime) << 3)) >> 4;

  SUBMULOC();
  DECLICK_CHECK();
  NOISELIVE0();
  NOISELIVE1();


  switch (oscMode) {
    //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
    case 0:

      noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

      //main oscillator
      o1.phase = o1.phase + o1.phase_increment;
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;

      o3.phase = o3.phase + o3.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> WTShiftFM]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> WTShiftFM]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = (FMIndex * o3.wave);
      o4.phase = o2.phase +  o3.index + o1.phaseOffset;
      o4.phaseRemain = (o4.phase << 9) >> 17;


      //-----------------------------------------------------------------------

      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o4.wave = (
                  (((int32_t)(((GWThi1[o4.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o4.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o4.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o4.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o4.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o4.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o4.nextwave = (
                      (((int32_t)(((GWThi1[(o4.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o4.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o4.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o4.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o4.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o4.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o2.wave = (o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15)) >> 1;
      o4.wave = (o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15)) >> 1;
      break;

    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
    case 2:


      noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);


      //main oscillator
      o1.phase = o1.phase + o1.phase_increment;
      if (o1.phaseOld > o1.phase) {
        noiseLive1[0] = random(-32767, 32767);
      }
      o1.phaseOld = o1.phase;
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index );
      o2.phaseRemain = (o2.phase << 9) >> 17;

      o3.phase = o3.phase + o3.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> WTShiftFM]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> WTShiftFM]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = (FMIndex * o3.wave);
      o4.phase = o2.phase +  o3.index + o1.phaseOffset;
      o4.phaseRemain = (o4.phase << 9) >> 17;

      //-----------------------------------------------------------------------

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o4.wave = (

                  (((int32_t)(((GWTlo1[o4.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o4.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o4.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o4.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o4.nextwave = (

                      (((int32_t)(((GWTlo1[(o4.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o4.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o4.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o2.wave = (o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15)) >> 1;
      o4.wave = (o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15)) >> 1;


      break;


    case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------






      o1.phase = o1.phase + (o1.phase_increment );
      o2.phase = o2.phase +  o2.phase_increment;
      if (o1.phaseOld > o1.phase)o2.phase = (uint32_t)((o2.phase_increment * o1.phase) >> Temporal_Shift_CZ);;
      o1.phaseOld = o1.phase;
      o2.phaseRemain = (o2.phase << 9) >> 17;
      o1.phaseRemain = (o1.phase << 9) >> 17;

      
      o3.phase = o1.phase + (o1.phaseOffset);
      o4.phase = o4.phase +  o4.phase_increment;
      if (o3.phase < (o1.phase_increment<<1))o4.phase = (uint32_t)((o4.phase_increment * o3.phase) >> Temporal_Shift_CZ);
      o3.phaseOld = o3.phase;
      o4.phaseRemain = (o4.phase << 9) >> 17;
      o3.phaseRemain = (o3.phase << 9) >> 17;

      //-----------------------------------------------------------------------

      o2.wave = (FMTable[o2.phase >> 23]);
      o2.nextwave =  (FMTable[(o2.phase + nextstep) >> 23]);
      o4.wave = (FMTable[o4.phase >> 23]);
      o4.nextwave =  (FMTable[(o4.phase + nextstep) >> 23]);


      o1.wave = ((
                   (((int32_t)(((GWThi1[o1.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o1.phase >> 23] * (GremHi)) >> 9))) * mixHi)   +
                   (((int32_t)(((GWTlo1[o1.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o1.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o1.phase >> 23] * (GremMid)) >> 9))) * mixMid)
                 ) >> 4) >> 11;

      o1.nextwave = ((
                       (((int32_t)(((GWThi1[(o1.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o1.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi)   +
                       (((int32_t)(((GWTlo1[(o1.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o1.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o1.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o1.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)
                     ) >> 4) >> 11;

      o3.wave = ((
                   (((int32_t)(((GWThi1[o3.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o3.phase >> 23] * (GremHi)) >> 9))) * mixHi)   +
                   (((int32_t)(((GWTlo1[o3.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o3.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o3.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o3.phase >> 23] * (GremMid)) >> 9))) * mixMid)
                 ) >> 4) >> 11;

      o3.nextwave = ((
                       (((int32_t)(((GWThi1[(o3.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o3.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi)   +
                       (((int32_t)(((GWTlo1[(o3.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o3.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o3.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o3.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)
                     ) >> 4) >> 11;

      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o4.wave = o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);

      o2.wave = ((o1.wave * (2047 - CZMix)) >> 8)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 12));  //cz mixer
      o4.wave = ((o3.wave * (2047 - CZMix)) >> 8)  +  ((int32_t)(((o3.wave) * ((o4.wave * CZMix) >> 11)) >> 12));  //cz mixer



      break;



    //----------------------------------------------ALT CZ mode-----------------------------------------
    case 3:

     o1.phase = o1.phase + (o1.phase_increment );
      o2.phase = o2.phase +  o2.phase_increment;
      if (o1.phaseOld > o1.phase)o2.phase = (uint32_t)((o2.phase_increment * o1.phase) >> Temporal_Shift_CZ);;
      o1.phaseOld = o1.phase;
      o2.phaseRemain = (o2.phase << 9) >> 17;
      o1.phaseRemain = (o1.phase << 9) >> 17;

      
      o3.phase = o1.phase + (o1.phaseOffset);
      o4.phase = o4.phase +  o4.phase_increment;
      if (o3.phase < (o1.phase_increment<<1))o4.phase = (uint32_t)((o4.phase_increment * o3.phase) >> Temporal_Shift_CZ);
      o3.phaseOld = o3.phase;
      o4.phaseRemain = (o4.phase << 9) >> 17;
      o3.phaseRemain = (o3.phase << 9) >> 17;



      //-----------------------------------------------------------------------

      o2.wave = (FMTable[o2.phase >> 23]);
      o2.nextwave =  (FMTable[(o2.phase + nextstep) >> 23]);
      o4.wave = (FMTable[o4.phase >> 23]);
      o4.nextwave =  (FMTable[(o4.phase + nextstep) >> 23]);


      o1.wave = ((

                   (((int32_t)(((GWTlo1[o1.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o1.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o1.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                 ) >> 4) >> 11;

      o1.nextwave = ((

                       (((int32_t)(((GWTlo1[(o1.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o1.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o1.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o1.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                     ) >> 4) >> 11;

      o3.wave = ((

                   (((int32_t)(((GWTlo1[o3.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o3.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o3.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o3.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                 ) >> 4) >> 11;

      o3.nextwave = ((

                       (((int32_t)(((GWTlo1[(o3.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o3.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o3.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o3.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                     ) >> 4) >> 11;


      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o4.wave = o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);

      o2.wave = ((o1.wave * (2047 - CZMix)) >> 8)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 12));  //cz mixer
      o4.wave = ((o3.wave * (2047 - CZMix)) >> 8)  +  ((int32_t)(((o3.wave) * ((o4.wave * CZMix) >> 11)) >> 12));  //cz mixer




      break;

  }

  o1.wave = (int32_t)(o2.wave >> 3) + (o4.wave >> 3);
  o1.wave = (int32_t)(o1.wave * mixEffect) >> 8;
  o1.wave = o1.wave + ((int32_t)(o2.wave * mixEffectDn) >> 10);

  FinalOut = declickValue + ((o1.wave * declickRampIn) >> 12);

  analogWrite(aout2, FinalOut + 32000);

  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

}





