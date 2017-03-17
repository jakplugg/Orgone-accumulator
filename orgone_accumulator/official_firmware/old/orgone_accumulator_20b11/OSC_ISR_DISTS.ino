void FASTRUN outUpdateISR_DISTS(void) {
  //noInterrupts();

  //digitalWriteFast (oSQout,0);//temp testing OC


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
     // o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = Interp512(o1.wave,o1.nextwave,o1.phase);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index + o3.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;

      o3.phase = o3.phase + o2.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> WTShiftFM]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> WTShiftFM]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = ((o3.wave * o1.amp) >> 14) * FXMixer[2];

      //-----------------------------------------------------------------------

      o2.wave = (
                  (((int32_t)(((GWThi1[o2.phase >> 23] * (511 - GremHi)) >> 9) + ((GWThi2[o2.phase >> 23] * (GremHi)) >> 9))) * mixHi) +
                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o2.nextwave = (
                      (((int32_t)(((GWThi1[(o2.phase + nextstep) >> 23] * (511 - GremHi)) >> 9)  +  ((GWThi2[(o2.phase + nextstep) >> 23] * (GremHi)) >> 9))) * mixHi) +
                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * mixMid)) >> 11;

      o2.wave = Interp512(o2.wave,o2.nextwave,o2.phase)>>1;

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
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = Interp512(o1.wave,o1.nextwave,o1.phase);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index + o3.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;

      o3.phase = o3.phase + o2.phase_increment;      
      o3.wave = (FMTable[o3.phase >> WTShiftFM]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> WTShiftFM]);
      o3.wave = Interp512(o3.wave,o3.nextwave,o3.phase);
      o3.index = ((o3.wave * o1.amp) >> 16) * FXMixer[2];


      //-----------------------------------------------------------------------

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 11;

      o2.wave = Interp512(o2.wave,o2.nextwave,o2.phase)>>1;


      break;


    case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------



      o1.phase = o1.phase + o1.phase_increment + o3.index;
      o2.phase = o2.phase +  o2.phase_increment;
      if (o1.phaseOld > o1.phase)o2.phase = (uint32_t)((o2.phase_increment * o1.phase) >> Temporal_Shift_CZ);;
      o1.phaseOld = o1.phase;
      o2.phaseRemain = (o2.phase << 9) >> 17; 
      o1.phaseRemain = (o1.phase << 9) >> 17;

      //dummy wave for self mod effect
      o3.phase = o3.phase + o1.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> 23]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> 23]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = ((o3.wave * o1.amp) >> 16) * FXMixer[2];


      //-----------------------------------------------------------------------

      o2.wave = (FMTable[o2.phase >> 23]);
      o2.nextwave =  (FMTable[(o2.phase + nextstep) >> 23]);


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

      o2.wave = Interp512(o2.wave,o2.nextwave,o2.phase);
      o1.wave = Interp512(o1.wave,o1.nextwave,o1.phase);

      o2.wave = ((o1.wave * (2047 - CZMix)) >> 8)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 12));  //cz mixer


      break;



    //----------------------------------------------ALT CZ mode-----------------------------------------
    case 3:

      o1.phase = o1.phase + (o1.phase_increment + o3.index);
      o2.phase = (uint32_t)((((uint64_t)o1.phase) * ((uint64_t)o2.phase_increment))>>25); //different way, experimental
      //if (o1.phaseOld > o1.phase)o2.phase = ((o1.phase * o2.phase_increment)>>Temporal_Shift_CZ); 
      //o1.phaseOld = o1.phase;
      
      

      //dummy self mod wave
      o3.phase = o3.phase + o1.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> 23]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> 23]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = (int32_t)(((o3.wave * o1.amp) >> 15) * FXMixer[2]);


      //-----------------------------------------------------------------------

      o2.wave = (FMTable[o2.phase >> 23]);
      o2.nextwave =  (FMTable[(o2.phase + nextstep) >> 23]);


      o1.wave = ((

                   (((int32_t)(((GWTlo1[o1.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o1.phase >> 23] * (GremLo)) >> 9))) * mixLo)   +
                   (((int32_t)(((GWTmid1[o1.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o1.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                 ) >> 4) >> 11;

      o1.nextwave = ((

                       (((int32_t)(((GWTlo1[(o1.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o1.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo)   +
                       (((int32_t)(((GWTmid1[(o1.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o1.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))
                     ) >> 4) >> 11;


      o2.wave = Interp512(o2.wave,o2.nextwave,o2.phase);
      o1.wave = Interp512(o1.wave,o1.nextwave,o1.phase);



      o2.wave = ((o1.wave * (2047 - CZMix)) >> 8)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 12));


      break;

  }

  o6.wave = ((o2.wave * (4095 - o1.amp)) >> 11) + (((o2.wave ^ (o3.wave)) * o1.amp) >> 13) ;

  o7.wave = ((o2.wave * (4095 - o1.amp)) >> 11) + ((o1.amp * (FMTable[abs(o2.wave) >> 6])) >> 12); //lookup

  o1.wave = (((((o2.wave >> (CRUSHBITS)) << (CRUSHBITS))) * (CRUSH_Remain)) >> 10) + (((((o2.wave >> (CRUSHBITS - 1)) << (CRUSHBITS - 1))) * (1023 - CRUSH_Remain)) >> 10);


  o3.wave = (o2.wave + (((o2.wave) * o1.amp) >> 10)) >> 2 ; //start of folding

  o4.wave = (o3.wave << 19) >> 19;


  if (o3.wave > 0) {
    if ((((o3.wave) >> 12) & 0x01) == 0) o4.wave = -o4.wave;
  }
  else {
    if ((((o3.wave) >> 12) & 0x01) == 1) o4.wave = -o4.wave;
  }

  o1.wave =
    (((o2.wave * ((int)mixEffectDn)) >> 10)) //undistorted
    + (((-o4.wave) * ((int)FXMixer[0])) >> 8) //dists 1 fold
    + (((o1.wave) * ((int)FXMixer[1])) >> 10)  //dists 1 crush
    + (((o6.wave) * ((int)FXMixer[3])) >> 11) //dists2 XORrible
    + (((o7.wave * ((int)FXMixer[2])) >> 11))  ; //dists 2 waveshaper

  FinalOut = declickValue + ((o1.wave * declickRampIn) >> 12);

  analogWrite(aout2, FinalOut + 32000);

  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

}

void FASTRUN outUpdateISR_PULSAR_DISTS(void) {

  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((8192 - delayTime) << 3)) >> 4;


  SUBMULOC();
  DECLICK_CHECK();
  NOISELIVE0();
  NOISELIVE1();




  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

  o1.phase = o1.phase + o1.phase_increment;
  o2.phase = o2.phase +  o2.phase_increment;

  if (o1.phaseOld > o1.phase) {
    o3.phase = (uint32_t)((o3.phase_increment * o1.phase)>>Temporal_Shift_CZ);
    o2.phase = (uint32_t)((o2.phase_increment * o1.phase)>>Temporal_Shift_CZ); 
  }
  o1.phaseOld = o1.phase;

  
  o2.phaseRemain = (o2.phase << 9) >> 17; 


  if (o3.phase >> 31 == 0) {
    o3.phase = o3.phase + o3.phase_increment;
    o3.wave = (PENV[o3.phase >> 23]);
    o3.nextwave =  (PENV[(o3.phase + nextstep) >> 23]);
  }
  else {
    o3.wave = 0;
    o3.nextwave =  0;
  }

  o3.phaseRemain = (o3.phase << 9) >> 17;


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



      break;

    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
    case 2:

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;


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




      break;

    //-----------------------------------------------ALT CZ MODE OSCILLATORS-----------------------------------------------
    case 3:

      o2.wave = (

                  (((int32_t)(((GWTlo1[o2.phase >> 23] * (511 - GremLo)) >> 9) + ((GWTlo2[o2.phase >> 23] * (GremLo)) >> 9))) * mixLo) +
                  (((int32_t)(((GWTmid1[o2.phase >> 23] * (511 - GremMid)) >> 9) + ((GWTmid2[o2.phase >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;

      o2.nextwave = (

                      (((int32_t)(((GWTlo1[(o2.phase + nextstep) >> 23] * (511 - GremLo)) >> 9)  +  ((GWTlo2[(o2.phase + nextstep) >> 23] * (GremLo)) >> 9))) * mixLo) +
                      (((int32_t)(((GWTmid1[(o2.phase + nextstep) >> 23] * (511 - GremMid)) >> 9)  +  ((GWTmid2[(o2.phase + nextstep) >> 23] * (GremMid)) >> 9))) * (mixMid + mixHi))) >> 15;


      break;

  }

  o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
  o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);

  o2.wave =   (o2.wave * o3.wave) >> 12;  //15 bits

  o6.wave = ((o2.wave * (4095 - o1.amp)) >> 11) + (((o2.wave ^ (o3.wave)) * o1.amp) >> 13) ;

  o7.wave = ((o2.wave * (4095 - o1.amp)) >> 11) + ((o1.amp * (FMTable[abs(o2.wave) >> 6])) >> 12); //lookup

  o1.wave = (((((o2.wave >> (CRUSHBITS)) << (CRUSHBITS))) * (CRUSH_Remain)) >> 10) + (((((o2.wave >> (CRUSHBITS - 1)) << (CRUSHBITS - 1))) * (1023 - CRUSH_Remain)) >> 10);


  o3.wave = (o2.wave + (((o2.wave) * o1.amp) >> 10)) >> 2 ; //start of folding

  o4.wave = (o3.wave << 19) >> 19;


  if (o3.wave > 0) {
    if ((((o3.wave) >> 12) & 0x01) == 0) o4.wave = -o4.wave;
  }
  else {
    if ((((o3.wave) >> 12) & 0x01) == 1) o4.wave = -o4.wave;
  }

  o1.wave =
    (((o2.wave * ((int)mixEffectDn)) >> 10)) //undistorted
    + (((-o4.wave) * ((int)FXMixer[0])) >> 8) //dists 1 fold
    + (((o1.wave) * ((int)FXMixer[1])) >> 10)  //dists 1 crush
    + (((o6.wave) * ((int)FXMixer[3])) >> 11) //dists2 XORrible
    + (((o7.wave * ((int)FXMixer[2])) >> 11))  ; //dists 2 waveshaper

  FinalOut = declickValue + ((o1.wave * declickRampIn) >> 12);

  analogWrite(aout2, FinalOut + 32000);



}





