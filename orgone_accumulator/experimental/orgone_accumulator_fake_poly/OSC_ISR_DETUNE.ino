void FASTRUN outUpdateISR_MAIN(void) {//original detuning with stepped wave selection.



  noiseTable[o1[rN].phase >> 23] = random(-32767, 32767); //replace noise cells with random values.


  DECLICK_CHECK();

  NOISELIVE0();
  NOISELIVE1();
   noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
  for (rN = 0; rN < NumVoices; rN ++) {

    switch (oscMode) {

      //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
      case 0:

       


        //main oscillator
        o1[rN].phase = o1[rN].phase + o1[rN].phase_increment;
        o1[rN].phaseRemain = (o1[rN].phase << 9) >> 17;
        o1[rN].wave = (FMTable[o1[rN].phase >> WTShiftFM]);
        o1[rN].nextwave =  (FMTable[(o1[rN].phase + nextstep) >> WTShiftFM]);
        o1[rN].wave = o1[rN].wave + ((((o1[rN].nextwave - o1[rN].wave)) * o1[rN].phaseRemain) >> 15);
        o1[rN].index = (FMIndex[rN] * o1[rN].wave);
        o2[rN].phase = o2[rN].phase +  (o2[rN].phase_increment + o1[rN].index);
        o2[rN].phaseRemain = (o2[rN].phase << 9) >> 17;
        //unisone oscillators  ------------3-4---------
        o3[rN].phase = o3[rN].phase + o3[rN].phase_increment;
        o3[rN].phaseRemain = (o3[rN].phase << 9) >> 17;
        o3[rN].wave = (FMTable[o3[rN].phase >> WTShiftFM]);
        o3[rN].nextwave =  (FMTable[(o3[rN].phase + nextstep) >> WTShiftFM]);
        o3[rN].wave = o3[rN].wave + ((((o3[rN].nextwave - o3[rN].wave)) * o3[rN].phaseRemain) >> 15);
        o3[rN].index = (FMIndex[rN] * o3[rN].wave);
        o4[rN].phase = o4[rN].phase +  (o4[rN].phase_increment + o3[rN].index);
        o4[rN].phaseRemain = (o4[rN].phase << 9) >> 17;
        //---------------------------------5-6------------
       

        //-----------------------------------------------------------------------

        o1[rN].wave = (((waveTableHiLink[o2[rN].phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o2[rN].phase >> 23] * mixLo) + (waveTableMidLink[o2[rN].phase >> 23] * mixMid))) >> 11;
        o3[rN].wave = (((waveTableHiLink[o4[rN].phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o4[rN].phase >> 23] * mixLo) + (waveTableMidLink[o4[rN].phase >> 23] * mixMid))) >> 11;
       

        o1[rN].nextwave = (((waveTableHiLink[(o2[rN].phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o2[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o2[rN].phase + nextstep) >> 23] * mixMid))) >> 11;
        o3[rN].nextwave = (((waveTableHiLink[(o4[rN].phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o4[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o4[rN].phase + nextstep) >> 23] * mixMid))) >> 11;
        
        o1[rN].wave = (o1[rN].wave + ((((o1[rN].nextwave - o1[rN].wave)) * o2[rN].phaseRemain) >> 15)) >> 3;
        o3[rN].wave = (o3[rN].wave + ((((o3[rN].nextwave - o3[rN].wave)) * o4[rN].phaseRemain) >> 15)) >> 3;
       
        break;

      //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
      case 2:


       


        //main oscillator
        o1[rN].phase = o1[rN].phase + o1[rN].phase_increment;
        o1[rN].phaseRemain = (o1[rN].phase << 9) >> 17;
        o1[rN].wave = (FMTable[o1[rN].phase >> WTShiftFM]);
        o1[rN].nextwave =  (FMTable[(o1[rN].phase + nextstep) >> WTShiftFM]);
        o1[rN].wave = o1[rN].wave + ((((o1[rN].nextwave - o1[rN].wave)) * o1[rN].phaseRemain) >> 15);
        o1[rN].index = (FMIndex[rN] * o1[rN].wave);
        o2[rN].phase = o2[rN].phase +  (o2[rN].phase_increment + o1[rN].index);
        o2[rN].phaseRemain = (o2[rN].phase << 9) >> 17;
        //unisone oscillators  ------------3-4---------
        o3[rN].phase = o3[rN].phase + o3[rN].phase_increment;
        o3[rN].phaseRemain = (o3[rN].phase << 9) >> 17;
        o3[rN].wave = (FMTable[o3[rN].phase >> WTShiftFM]);
        o3[rN].nextwave =  (FMTable[(o3[rN].phase + nextstep) >> WTShiftFM]);
        o3[rN].wave = o3[rN].wave + ((((o3[rN].nextwave - o3[rN].wave)) * o3[rN].phaseRemain) >> 15);
        o3[rN].index = (FMIndex[rN] * o3[rN].wave);
        o4[rN].phase = o4[rN].phase +  (o4[rN].phase_increment + o3[rN].index);
        o4[rN].phaseRemain = (o4[rN].phase << 9) >> 17;
        //---------------------------------5-6------------
        

        //-----------------------------------------------------------------------

        o1[rN].wave = (((waveTableLoLink[o2[rN].phase >> 23] * mixLo) + (waveTableMidLink[o2[rN].phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
        o3[rN].wave = (((waveTableLoLink[o4[rN].phase >> 23] * mixLo) + (waveTableMidLink[o4[rN].phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
       
        o1[rN].nextwave = (((waveTableLoLink[(o2[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o2[rN].phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
        o3[rN].nextwave = (((waveTableLoLink[(o4[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o4[rN].phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
        
        o1[rN].wave = (o1[rN].wave + ((((o1[rN].nextwave - o1[rN].wave)) * o2[rN].phaseRemain) >> 15)) >> 3;
        o3[rN].wave = (o3[rN].wave + ((((o3[rN].nextwave - o3[rN].wave)) * o4[rN].phaseRemain) >> 15)) >> 3;
        
        break;


      case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------


        o1[rN].phase = o1[rN].phase + o1[rN].phase_increment;
        o2[rN].phase = o2[rN].phase +  o2[rN].phase_increment;
        o2[rN].phaseRemain = (o2[rN].phase << 9) >> 17;
        o1[rN].phaseRemain = (o1[rN].phase << 9) >> 17;
        if (o1[rN].phaseOld > o1[rN].phase)o2[rN].phase = (uint32_t)((o2[rN].phase_increment * o1[rN].phase) >> Temporal_Shift_CZ);
        o1[rN].phaseOld = o1[rN].phase;

        o2[rN].phaseRemain = (o2[rN].phase << 9) >> 17;
        o1[rN].phaseRemain = (o1[rN].phase << 9) >> 17;
        
        //unisone oscillators  ------------3-4---------
        o3[rN].phase = o3[rN].phase + o3[rN].phase_increment;
        o4[rN].phase = o4[rN].phase +  o4[rN].phase_increment;
        if (o3[rN].phaseOld > o3[rN].phase) o4[rN].phase = (uint32_t)((o4[rN].phase_increment * o3[rN].phase) >> Temporal_Shift_CZ);
        o3[rN].phaseOld = o3[rN].phase;

        o4[rN].phaseRemain = (o4[rN].phase << 9) >> 17;
        o3[rN].phaseRemain = (o3[rN].phase << 9) >> 17;
        //---------------------------------5-6------------
        

        //-----------------------------------------------------------------------

        o2[rN].wave = (FMTable[o2[rN].phase >> 23]);
        o2[rN].nextwave =  (FMTable[(o2[rN].phase + nextstep) >> 23]);
        o4[rN].wave = (FMTable[o4[rN].phase >> 23]);
        o4[rN].nextwave =  (FMTable[(o4[rN].phase + nextstep) >> 23]);
      
        o1[rN].wave = (((waveTableHiLink[o1[rN].phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o1[rN].phase >> 23] * mixLo) + (waveTableMidLink[o1[rN].phase >> 23] * mixMid)) >> 4) >> 11;
        o1[rN].nextwave = (((waveTableHiLink[(o1[rN].phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o1[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o1[rN].phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;
        o3[rN].wave = (((waveTableHiLink[o3[rN].phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o3[rN].phase >> 23] * mixLo) + (waveTableMidLink[o3[rN].phase >> 23] * mixMid)) >> 4) >> 11;
        o3[rN].nextwave = (((waveTableHiLink[(o3[rN].phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o3[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o3[rN].phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;
       

        o1[rN].wave = o1[rN].wave + ((((o1[rN].nextwave - o1[rN].wave)) * o1[rN].phaseRemain) >> 15);
        o3[rN].wave = o3[rN].wave + ((((o3[rN].nextwave - o3[rN].wave)) * o3[rN].phaseRemain) >> 15);
       
        o2[rN].wave = o2[rN].wave + ((((o2[rN].nextwave - o2[rN].wave)) * o2[rN].phaseRemain) >> 15);
        o4[rN].wave = o4[rN].wave + ((((o4[rN].nextwave - o4[rN].wave)) * o4[rN].phaseRemain) >> 15);
       

        o1[rN].wave = ((o1[rN].wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o1[rN].wave) * ((o2[rN].wave * CZMix) >> 11)) >> 14));
        o3[rN].wave = ((o3[rN].wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o3[rN].wave) * ((o4[rN].wave * CZMix) >> 11)) >> 14));
        

        break;

      //----------------------------------------------ALT CZ mode-----------------------------------------
      case 3:

       
        o1[rN].phase = o1[rN].phase + (o1[rN].phase_increment);
        o2[rN].phase = o2[rN].phase +  o2[rN].phase_increment;
        if (o1[rN].phaseOld > o1[rN].phase) o2[rN].phase = (uint32_t)((o2[rN].phase_increment * o1[rN].phase) >> Temporal_Shift_CZ);
        o1[rN].phaseOld = o1[rN].phase;

        o2[rN].phaseRemain = (o2[rN].phase << 9) >> 17;
        o1[rN].phaseRemain = (o1[rN].phase << 9) >> 17;

        //unisone oscillators  ------------3-4---------
      
        o3[rN].phase = o3[rN].phase + (o3[rN].phase_increment);
        o4[rN].phase = o4[rN].phase +  o4[rN].phase_increment;
        if (o3[rN].phaseOld > o3[rN].phase) o4[rN].phase = (uint32_t)((o4[rN].phase_increment * o3[rN].phase) >> Temporal_Shift_CZ);
        o3[rN].phaseOld = o3[rN].phase;

        o4[rN].phaseRemain = (o4[rN].phase << 9) >> 17;
        o3[rN].phaseRemain = (o3[rN].phase << 9) >> 17;
        //---------------------------------5-6------------
       
        //-----------------------------------------------------------------------

        o2[rN].wave = (FMTable[o2[rN].phase >> WTShiftFM]);
        o2[rN].nextwave =  (FMTable[(o2[rN].phase + nextstep) >> WTShiftFM]);
        o4[rN].wave = (FMTable[o4[rN].phase >> WTShiftFM]);
        o4[rN].nextwave =  (FMTable[(o4[rN].phase + nextstep) >> WTShiftFM]);
        
        o1[rN].wave = (((waveTableLoLink[o1[rN].phase >> 23] * mixLo) + (waveTableMidLink[o1[rN].phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
        o1[rN].nextwave = (((waveTableLoLink[(o1[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o1[rN].phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
        o3[rN].wave = (((waveTableLoLink[o3[rN].phase >> 23] * mixLo) + (waveTableMidLink[o3[rN].phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
        o3[rN].nextwave = (((waveTableLoLink[(o3[rN].phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o3[rN].phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      

        o1[rN].wave = o1[rN].wave + ((((o1[rN].nextwave - o1[rN].wave)) * o1[rN].phaseRemain) >> 15);
        o3[rN].wave = o3[rN].wave + ((((o3[rN].nextwave - o3[rN].wave)) * o3[rN].phaseRemain) >> 15);
       
        o2[rN].wave = o2[rN].wave + ((((o2[rN].nextwave - o2[rN].wave)) * o2[rN].phaseRemain) >> 15);
        o4[rN].wave = o4[rN].wave + ((((o4[rN].nextwave - o4[rN].wave)) * o4[rN].phaseRemain) >> 15);
       
        o1[rN].wave = ((o1[rN].wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o1[rN].wave) * ((o2[rN].wave * CZMix) >> 11)) >> 14));
        o3[rN].wave = ((o3[rN].wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o3[rN].wave) * ((o4[rN].wave * CZMix) >> 11)) >> 14));
        

        break;

    }

       
    o1[rN].wave = ((((o3[rN].wave + o1[rN].wave)>>1) * (int)(mixEffectUp)) >> 7) + (((o1[rN].wave * ((int)mixEffectDn)) >> 8)); //main out and mix detune
    mixWave += o1[rN].wave;
  }
  FinalOut = (mixWave>>2); 
  mixWave = 0;
  analogWrite(aout2, FinalOut + 32000);
  SUBMULOC();
}



