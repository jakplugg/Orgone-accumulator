void FASTRUN outUpdateISR_MAIN(void) {//original detuning with stepped wave selection.

  SUBMULOC();

  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.


  DECLICK_CHECK();

  NOISELIVE0();
  NOISELIVE1();


  switch (oscMode) {

    //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
    case 0:

      noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);


      //main oscillator
      o1.phase = o1.phase + o1.phase_increment;
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;
      //unisone oscillators  ------------3-4---------
      o3.phase = o3.phase + o3.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> WTShiftFM]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> WTShiftFM]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = (FMIndex * o3.wave);
      o4.phase = o4.phase +  (o4.phase_increment + o3.index);
      o4.phaseRemain = (o4.phase << 9) >> 17;
      //---------------------------------5-6------------
      o5.phase = o5.phase + o5.phase_increment;
      o5.phaseRemain = (o5.phase << 9) >> 17;
      o5.wave = (FMTable[o5.phase >> WTShiftFM]);
      o5.nextwave =  (FMTable[(o5.phase + nextstep) >> WTShiftFM]);
      o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);
      o5.index = (FMIndex * o5.wave);
      o6.phase = o6.phase + (o6.phase_increment + o5.index);
      o6.phaseRemain = (o6.phase << 9) >> 17;
      //-------------------------------7-8--------------
      o7.phase = o7.phase + o7.phase_increment;
      o7.phaseRemain = (o7.phase << 9) >> 17;
      o7.wave = (FMTable[o7.phase >> WTShiftFM]);
      o7.nextwave =  (FMTable[(o7.phase + nextstep) >> WTShiftFM]);
      o7.wave = o7.wave + ((((o7.nextwave - o7.wave)) * o7.phaseRemain) >> 15);
      o7.index = (FMIndex * o7.wave);
      o8.phase = o8.phase +  (o8.phase_increment + o7.index);
      o8.phaseRemain = (o8.phase << 9) >> 17;
      //------------------------------9-10-------------------
      o9.phase = o9.phase + o9.phase_increment;
      o9.phaseRemain = (o9.phase << 9) >> 17;
      o9.wave = (FMTable[o9.phase >> WTShiftFM]);
      o9.nextwave =  (FMTable[(o9.phase + nextstep) >> WTShiftFM]);
      o9.wave = o9.wave + ((((o9.nextwave - o9.wave)) * o9.phaseRemain) >> 15);
      o9.index = (FMIndex * o9.wave);
      o10.phase = o10.phase + (o10.phase_increment + o9.index);
      o10.phaseRemain = (o10.phase << 9) >> 17;
      //-----------------------------------------------------------------------

      o1.wave = (((waveTableHiLink[o2.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o2.phase >> 23] * mixLo) + (waveTableMidLink[o2.phase >> 23] * mixMid))) >> 11;
      o3.wave = (((waveTableHiLink[o4.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o4.phase >> 23] * mixLo) + (waveTableMidLink[o4.phase >> 23] * mixMid))) >> 11;
      o5.wave = (((waveTableHiLink[o6.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o6.phase >> 23] * mixLo) + (waveTableMidLink[o6.phase >> 23] * mixMid))) >> 11;
      o7.wave = (((waveTableHiLink[o8.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o8.phase >> 23] * mixLo) + (waveTableMidLink[o8.phase >> 23] * mixMid))) >> 11;
      o9.wave = (((waveTableHiLink[o10.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o10.phase >> 23] * mixLo) + (waveTableMidLink[o10.phase >> 23] * mixMid))) >> 11;

      o1.nextwave = (((waveTableHiLink[(o2.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o2.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o2.phase + nextstep) >> 23] * mixMid))) >> 11;
      o3.nextwave = (((waveTableHiLink[(o4.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o4.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o4.phase + nextstep) >> 23] * mixMid))) >> 11;
      o5.nextwave = (((waveTableHiLink[(o6.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o6.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o6.phase + nextstep) >> 23] * mixMid))) >> 11;
      o7.nextwave = (((waveTableHiLink[(o8.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o8.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o8.phase + nextstep) >> 23] * mixMid))) >> 11;
      o9.nextwave = (((waveTableHiLink[(o10.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o10.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o10.phase + nextstep) >> 23] * mixMid))) >> 11;

      o1.wave = (o1.wave + ((((o1.nextwave - o1.wave)) * o2.phaseRemain) >> 15)) >> 3;
      o3.wave = (o3.wave + ((((o3.nextwave - o3.wave)) * o4.phaseRemain) >> 15)) >> 3;
      o5.wave = (o5.wave + ((((o5.nextwave - o5.wave)) * o6.phaseRemain) >> 15)) >> 3;
      o7.wave = (o7.wave + ((((o7.nextwave - o7.wave)) * o8.phaseRemain) >> 15)) >> 3;
      o9.wave = (o9.wave + ((((o9.nextwave - o9.wave)) * o10.phaseRemain) >> 15)) >> 3;


      break;

    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
    case 2:


      noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);

      
      //main oscillator
      o1.phase = o1.phase + o1.phase_increment;
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o1.index = (FMIndex * o1.wave);
      o2.phase = o2.phase +  (o2.phase_increment + o1.index);
      o2.phaseRemain = (o2.phase << 9) >> 17;
      //unisone oscillators  ------------3-4---------
      o3.phase = o3.phase + o3.phase_increment;
      o3.phaseRemain = (o3.phase << 9) >> 17;
      o3.wave = (FMTable[o3.phase >> WTShiftFM]);
      o3.nextwave =  (FMTable[(o3.phase + nextstep) >> WTShiftFM]);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o3.index = (FMIndex * o3.wave);
      o4.phase = o4.phase +  (o4.phase_increment + o3.index);
      o4.phaseRemain = (o4.phase << 9) >> 17;
      //---------------------------------5-6------------
      o5.phase = o5.phase + o5.phase_increment;
      o5.phaseRemain = (o5.phase << 9) >> 17;
      o5.wave = (FMTable[o5.phase >> WTShiftFM]);
      o5.nextwave =  (FMTable[(o5.phase + nextstep) >> WTShiftFM]);
      o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);
      o5.index = (FMIndex * o5.wave);
      o6.phase = o6.phase + (o6.phase_increment + o5.index);
      o6.phaseRemain = (o6.phase << 9) >> 17;
      //-------------------------------7-8--------------
      o7.phase = o7.phase + o7.phase_increment;
      o7.phaseRemain = (o7.phase << 9) >> 17;
      o7.wave = (FMTable[o7.phase >> WTShiftFM]);
      o7.nextwave =  (FMTable[(o7.phase + nextstep) >> WTShiftFM]);
      o7.wave = o7.wave + ((((o7.nextwave - o7.wave)) * o7.phaseRemain) >> 15);
      o7.index = (FMIndex * o7.wave);
      o8.phase = o8.phase +  (o8.phase_increment + o7.index);
      o8.phaseRemain = (o8.phase << 9) >> 17;
      //------------------------------9-10-------------------
      o9.phase = o9.phase + o9.phase_increment;
      o9.phaseRemain = (o9.phase << 9) >> 17;
      o9.wave = (FMTable[o9.phase >> WTShiftFM]);
      o9.nextwave =  (FMTable[(o9.phase + nextstep) >> WTShiftFM]);
      o9.wave = o9.wave + ((((o9.nextwave - o9.wave)) * o9.phaseRemain) >> 15);
      o9.index = (FMIndex * o9.wave);
      o10.phase = o10.phase + (o10.phase_increment + o9.index);
      o10.phaseRemain = (o10.phase << 9) >> 17;
      //-----------------------------------------------------------------------

      o1.wave = (((waveTableLoLink[o2.phase >> 23] * mixLo) + (waveTableMidLink[o2.phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o3.wave = (((waveTableLoLink[o4.phase >> 23] * mixLo) + (waveTableMidLink[o4.phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o5.wave = (((waveTableLoLink[o6.phase >> 23] * mixLo) + (waveTableMidLink[o6.phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o7.wave = (((waveTableLoLink[o8.phase >> 23] * mixLo) + (waveTableMidLink[o8.phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o9.wave = (((waveTableLoLink[o10.phase >> 23] * mixLo) + (waveTableMidLink[o10.phase >> WTShiftMid] * (mixMid + mixHi)))) >> 11;

      o1.nextwave = (((waveTableLoLink[(o2.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o2.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o3.nextwave = (((waveTableLoLink[(o4.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o4.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o5.nextwave = (((waveTableLoLink[(o6.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o6.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o7.nextwave = (((waveTableLoLink[(o8.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o8.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;
      o9.nextwave = (((waveTableLoLink[(o10.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o10.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi)))) >> 11;

      o1.wave = (o1.wave + ((((o1.nextwave - o1.wave)) * o2.phaseRemain) >> 15)) >> 3;
      o3.wave = (o3.wave + ((((o3.nextwave - o3.wave)) * o4.phaseRemain) >> 15)) >> 3;
      o5.wave = (o5.wave + ((((o5.nextwave - o5.wave)) * o6.phaseRemain) >> 15)) >> 3;
      o7.wave = (o7.wave + ((((o7.nextwave - o7.wave)) * o8.phaseRemain) >> 15)) >> 3;
      o9.wave = (o9.wave + ((((o9.nextwave - o9.wave)) * o10.phaseRemain) >> 15)) >> 3;

      break;


    case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------


      o1.phase = o1.phase + o1.phase_increment;     
      o2.phase = o2.phase +  o2.phase_increment;
      o2.phaseRemain = (o2.phase << 9) >> 17; 
      o1.phaseRemain = (o1.phase << 9) >> 17;
       if (o1.phaseOld > o1.phase)o2.phase = (uint32_t)((o2.phase_increment * o1.phase)>>Temporal_Shift_CZ);  
      o1.phaseOld = o1.phase;

       o2.phaseRemain = (o2.phase << 9) >> 17; 
      o1.phaseRemain = (o1.phase << 9) >> 17;
      //unisone oscillators  ------------3-4---------
      o3.phase = o3.phase + o3.phase_increment + o7.phase_increment2;
      o4.phase = o4.phase +  o4.phase_increment;
      if (o3.phaseOld > o3.phase) o4.phase = (uint32_t)((o4.phase_increment * o3.phase)>>Temporal_Shift_CZ);
      o3.phaseOld = o3.phase;
      
      o4.phaseRemain = (o4.phase << 9) >> 17; 
      o3.phaseRemain = (o3.phase << 9) >> 17;
      //---------------------------------5-6------------
      o5.phase = o5.phase + o5.phase_increment;
      o6.phase = o6.phase + o6.phase_increment;
      if (o5.phaseOld > o5.phase) o6.phase = (uint32_t)((o6.phase_increment * o5.phase)>>Temporal_Shift_CZ);
      o5.phaseOld = o5.phase;
      
      o6.phaseRemain = (o6.phase << 9) >> 17; 
      o5.phaseRemain = (o5.phase << 9) >> 17;
      //-------------------------------7-8--------------
      o7.phase = o7.phase + o7.phase_increment;
      o8.phase = o8.phase +  o8.phase_increment;
      if (o7.phaseOld > o7.phase) o8.phase = (uint32_t)((o8.phase_increment * o7.phase)>>Temporal_Shift_CZ);
      o7.phaseOld = o7.phase;      
      o8.phaseRemain = (o8.phase << 9) >> 17; 
      o7.phaseRemain = (o7.phase << 9) >> 17;
      //------------------------------9-10-------------------
      o9.phase = o9.phase + o9.phase_increment;
      o10.phase = o10.phase + o10.phase_increment;
      if (o9.phaseOld > o9.phase) o10.phase = (uint32_t)((o10.phase_increment * o9.phase)>>Temporal_Shift_CZ);
      o9.phaseOld = o9.phase;      
      o10.phaseRemain = (o10.phase << 9) >> 17; 
      o9.phaseRemain = (o9.phase << 9) >> 17;

      //-----------------------------------------------------------------------

      o2.wave = (FMTable[o2.phase >> 23]);
      o2.nextwave =  (FMTable[(o2.phase + nextstep) >> 23]);
      o4.wave = (FMTable[o4.phase >> 23]);
      o4.nextwave =  (FMTable[(o4.phase + nextstep) >> 23]);
      o6.wave = (FMTable[o6.phase >> 23]);
      o6.nextwave =  (FMTable[(o6.phase + nextstep) >> 23]);
      o8.wave = (FMTable[o8.phase >> 23]);
      o8.nextwave =  (FMTable[(o8.phase + nextstep) >> 23]);
      o10.wave = (FMTable[o10.phase >> 23]);
      o10.nextwave =  (FMTable[(o10.phase + nextstep) >> 23]);

      o1.wave = (((waveTableHiLink[o1.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o1.phase >> 23] * mixLo) + (waveTableMidLink[o1.phase >> 23] * mixMid)) >> 4) >> 11;
      o1.nextwave = (((waveTableHiLink[(o1.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o1.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o1.phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;
      o3.wave = (((waveTableHiLink[o3.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o3.phase >> 23] * mixLo) + (waveTableMidLink[o3.phase >> 23] * mixMid)) >> 4) >> 11;
      o3.nextwave = (((waveTableHiLink[(o3.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o3.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o3.phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;
      o5.wave = (((waveTableHiLink[o5.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o5.phase >> 23] * mixLo) + (waveTableMidLink[o5.phase >> 23] * mixMid)) >> 4) >> 11;
      o5.nextwave = (((waveTableHiLink[(o5.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o5.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o5.phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;
      o7.wave = (((waveTableHiLink[o7.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o7.phase >> 23] * mixLo) + (waveTableMidLink[o7.phase >> 23] * mixMid)) >> 4) >> 11;
      o7.nextwave = (((waveTableHiLink[(o7.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o7.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o7.phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;
      o9.wave = (((waveTableHiLink[o9.phase >> WTShiftHi] * mixHi) + (waveTableLoLink[o9.phase >> 23] * mixLo) + (waveTableMidLink[o9.phase >> 23] * mixMid)) >> 4) >> 11;
      o9.nextwave = (((waveTableHiLink[(o9.phase + nextstep) >> WTShiftHi] * mixHi) + (waveTableLoLink[(o9.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o9.phase + nextstep) >> 23] * mixMid)) >> 4) >> 11;


      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);
      o7.wave = o7.wave + ((((o7.nextwave - o7.wave)) * o7.phaseRemain) >> 15);
      o9.wave = o9.wave + ((((o9.nextwave - o9.wave)) * o9.phaseRemain) >> 15);

      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      o4.wave = o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15);
      o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o6.phaseRemain) >> 15);
      o8.wave = o8.wave + ((((o8.nextwave - o8.wave)) * o8.phaseRemain) >> 15);
      o10.wave = o10.wave + ((((o10.nextwave - o10.wave)) * o10.phaseRemain) >> 15);


      o1.wave = ((o1.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 14));
      o3.wave = ((o3.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o3.wave) * ((o4.wave * CZMix) >> 11)) >> 14));
      o5.wave = ((o5.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o5.wave) * ((o6.wave * CZMix) >> 11)) >> 14));
      o7.wave = ((o7.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o7.wave) * ((o8.wave * CZMix) >> 11)) >> 14));
      o9.wave = ((o9.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o9.wave) * ((o10.wave * CZMix) >> 11)) >> 14));


      break;

    //----------------------------------------------ALT CZ mode-----------------------------------------
    case 3:

      lfo.phase = lfo.phase + lfo.phase_increment;
      lfo.wave = FMTableAMX[lfo.phase >> 23];
      //o1.phaseOffset = (FMX_HiOffset * lfo.wave);
      o1.phase = o1.phase + (o1.phase_increment);
      o2.phase = o2.phase +  o2.phase_increment;
      if (o1.phaseOld > o1.phase) o2.phase = (uint32_t)((o2.phase_increment * o1.phase)>>Temporal_Shift_CZ);         
      o1.phaseOld = o1.phase;
      
      o2.phaseRemain = (o2.phase << 9) >> 17; 
      o1.phaseRemain = (o1.phase << 9) >> 17;

      //unisone oscillators  ------------3-4---------
      //o3.phaseOffset = (FMX_HiOffset * lfo.wave);
      o3.phase = o3.phase + (o3.phase_increment);
      o4.phase = o4.phase +  o4.phase_increment;
      if (o3.phaseOld > o3.phase) o4.phase = (uint32_t)((o4.phase_increment * o3.phase)>>Temporal_Shift_CZ);
      o3.phaseOld = o3.phase;
      
      o4.phaseRemain = (o4.phase << 9) >> 17; 
      o3.phaseRemain = (o3.phase << 9) >> 17;
      //---------------------------------5-6------------
      //o5.phaseOffset = (FMX_HiOffset * lfo.wave);
      o5.phase = o5.phase + (o5.phase_increment);
      o6.phase = o6.phase + o6.phase_increment;
      if (o5.phaseOld > o5.phase) o6.phase = (uint32_t)((o6.phase_increment * o5.phase)>>Temporal_Shift_CZ);
      o5.phaseOld = o5.phase;
      
      o6.phaseRemain = (o6.phase << 9) >> 17; 
      o5.phaseRemain = (o5.phase << 9) >> 17;
      //-------------------------------7-8--------------
      //o7.phaseOffset = (FMX_HiOffset * lfo.wave);
      o7.phase = o7.phase + (o7.phase_increment);
      o8.phase = o8.phase +  o8.phase_increment;
      if (o7.phaseOld > o7.phase) o8.phase = (uint32_t)((o8.phase_increment * o7.phase)>>Temporal_Shift_CZ);
      o7.phaseOld = o7.phase;
      
      o8.phaseRemain = (o8.phase << 9) >> 17; 
      o7.phaseRemain = (o7.phase << 9) >> 17;
      //------------------------------9-10-------------------
      //o9.phaseOffset = (FMX_HiOffset * lfo.wave);
      o9.phase = o9.phase + (o9.phase_increment);
      o10.phase = o10.phase + o10.phase_increment;
      if (o9.phaseOld > o9.phase) o10.phase = (uint32_t)((o10.phase_increment * o9.phase)>>Temporal_Shift_CZ);
      o9.phaseOld = o9.phase;
      
      o10.phaseRemain = (o10.phase << 9) >> 17; 
      o9.phaseRemain = (o9.phase << 9) >> 17;

      //-----------------------------------------------------------------------

      o2.wave = (FMTable[o2.phase >> WTShiftFM]);
      o2.nextwave =  (FMTable[(o2.phase + nextstep) >> WTShiftFM]);
      o4.wave = (FMTable[o4.phase >> WTShiftFM]);
      o4.nextwave =  (FMTable[(o4.phase + nextstep) >> WTShiftFM]);
      o6.wave = (FMTable[o6.phase >> WTShiftFM]);
      o6.nextwave =  (FMTable[(o6.phase + nextstep) >> WTShiftFM]);
      o8.wave = (FMTable[o8.phase >> WTShiftFM]);
      o8.nextwave =  (FMTable[(o8.phase + nextstep) >> WTShiftFM]);
      o10.wave = (FMTable[o10.phase >> WTShiftFM]);
      o10.nextwave =  (FMTable[(o10.phase + nextstep) >> WTShiftFM]);

      o1.wave = (((waveTableLoLink[o1.phase >> 23] * mixLo) + (waveTableMidLink[o1.phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o1.nextwave = (((waveTableLoLink[(o1.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o1.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o3.wave = (((waveTableLoLink[o3.phase >> 23] * mixLo) + (waveTableMidLink[o3.phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o3.nextwave = (((waveTableLoLink[(o3.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o3.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o5.wave = (((waveTableLoLink[o5.phase >> 23] * mixLo) + (waveTableMidLink[o5.phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o5.nextwave = (((waveTableLoLink[(o5.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o5.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o7.wave = (((waveTableLoLink[o7.phase >> 23] * mixLo) + (waveTableMidLink[o7.phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o7.nextwave = (((waveTableLoLink[(o7.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o7.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o9.wave = (((waveTableLoLink[o9.phase >> 23] * mixLo) + (waveTableMidLink[o9.phase >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;
      o9.nextwave = (((waveTableLoLink[(o9.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o9.phase + nextstep) >> WTShiftMid] * (mixMid + mixHi))) >> 4) >> 11;


      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);
      o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
      o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);
      o7.wave = o7.wave + ((((o7.nextwave - o7.wave)) * o7.phaseRemain) >> 15);
      o9.wave = o9.wave + ((((o9.nextwave - o9.wave)) * o9.phaseRemain) >> 15);

      o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
      o4.wave = o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15);
      o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o6.phaseRemain) >> 15);
      o8.wave = o8.wave + ((((o8.nextwave - o8.wave)) * o8.phaseRemain) >> 15);
      o10.wave = o10.wave + ((((o10.nextwave - o10.wave)) * o10.phaseRemain) >> 15);

      o1.wave = ((o1.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o1.wave) * ((o2.wave * CZMix) >> 11)) >> 14));
      o3.wave = ((o3.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o3.wave) * ((o4.wave * CZMix) >> 11)) >> 14));
      o5.wave = ((o5.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o5.wave) * ((o6.wave * CZMix) >> 11)) >> 14));
      o7.wave = ((o7.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o7.wave) * ((o8.wave * CZMix) >> 11)) >> 14));
      o9.wave = ((o9.wave * (2047 - CZMix)) >> 10)  +  ((int32_t)(((o9.wave) * ((o10.wave * CZMix) >> 11)) >> 14));




      break;

  }
//  if (FX == 4) {
//    o3.wave = (int32_t)(ssat13((((o7.wave + o5.wave + o3.wave) >> 2) * 1500)) >> 11)>>1;//chord effect
//  }
//  else {
    o3.wave = (ssat13((((o9.wave + o7.wave + o5.wave + o3.wave) >> 2) * 1700) >> 11))>>1;//detune effect
//  }

  o9.wave = (o3.wave>>3);
  o9.wave = (-((o9.wave * o9.wave *o9.wave)>>15))+(o3.wave+(o3.wave>>1));//soft clipping replaces AGC

  o1.wave = ((o9.wave*(int)(mixEffectUp))>>7) + (((o1.wave * ((int)mixEffectDn)) >> 8)); //main out and mix detune
 
  
  FinalOut = declickValue + ((o1.wave * declickRampIn) >> 12);
  analogWrite(aout2, FinalOut + 32000);
}

void FASTRUN outUpdateISR_PULSAR_CHORD(void) {

 SUBMULOC();
  DECLICK_CHECK();

  noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

  NOISELIVE0();
  NOISELIVE1();


  //-------------------------------------pulse1
  o1.phase = o1.phase + o1.phase_increment;
  o2.phase = o2.phase +  o2.phase_increment ;
  if (o1.phaseOld > o1.phase) {
    o3.phase = (uint32_t)((o3.phase_increment * o1.phase)>>Temporal_Shift_CZ);
    o2.phase = (uint32_t)((o2.phase_increment * o1.phase)>>Temporal_Shift_CZ); 
  }
  o1.phaseOld = o1.phase;
  
  o2.phaseRemain = (o2.phase << 9) >> 17; 

  if (o3.phase >> 31 == 0) {
        o3.phase = o3.phase + o3.phase_increment ;
        o3.wave = (PENV[o3.phase >> 23]);
        o3.nextwave =  (PENV[(o3.phase + nextstep) >> 23]);
      }
      else {
        o3.wave = 0;
        o3.nextwave =  0;
      }
  
  o3.phaseRemain = (o3.phase << 9) >> 17;


  //---------------------------------pulse2
  o4.phase = o4.phase + o4.phase_increment;
  o5.phase = o5.phase +  o5.phase_increment ;
  if (o4.phaseAdd > o4.phase) {
     o5.phase = (uint32_t)((o5.phase_increment * o4.phase)>>Temporal_Shift_CZ);
    o6.phase = (uint32_t)((o6.phase_increment * o4.phase)>>Temporal_Shift_CZ); 
  }
  o4.phaseAdd = o4.phase;
  
  o5.phaseRemain = (o5.phase << 9) >> 17;

  if (o6.phase >> 31 == 0) {
        o6.phase = o6.phase + o6.phase_increment ;
        o6.wave = (PENV[o6.phase >> 23]);
        o6.nextwave =  (PENV[(o6.phase + nextstep) >> 23]);
      }
      else {
        o6.wave = 0;
        o6.nextwave =  0;
      }
 
  o6.phaseRemain = (o6.phase << 9) >> 17;


  //-----------------------------pulse3
  o7.phase = o7.phase + o7.phase_increment;
  o8.phase = o8.phase +  o8.phase_increment;
  if (o7.phaseOld > o7.phase) {
    o9.phase = (uint32_t)((o9.phase_increment * o7.phase)>>Temporal_Shift_CZ);
    o8.phase = (uint32_t)((o8.phase_increment * o7.phase)>>Temporal_Shift_CZ); 
  }
  o7.phaseOld = o7.phase;
  
  o8.phaseRemain = (o8.phase << 9) >> 17;

 if (o9.phase >> 31 == 0) {
        o9.phase = o9.phase + o9.phase_increment ;
        o9.wave = (PENV[o9.phase >> 23]);
        o9.nextwave =  (PENV[(o9.phase + nextstep) >> 23]);
      }
      else {
        o9.wave = 0;
        o9.nextwave =  0;
      }
  
  o9.phaseRemain = (o9.phase << 9) >> 17;

  //-----------------------------pulse4
  o10.phase = o10.phase + o10.phase_increment;
  o11.phase = o11.phase +  o11.phase_increment;
  if (o10.phaseOld > o10.phase) {
    o12.phase = (uint32_t)((o12.phase_increment * o10.phase)>>Temporal_Shift_CZ);
    o11.phase = (uint32_t)((o11.phase_increment * o10.phase)>>Temporal_Shift_CZ); 
  }
  o10.phaseOld = o10.phase;
  
  o11.phaseRemain = (o11.phase << 9) >> 17;

if (o12.phase >> 31 == 0) {
        o12.phase = o12.phase + o12.phase_increment ;
        o12.wave = (PENV[o12.phase >> 23]);
        o12.nextwave =  (PENV[(o12.phase + nextstep) >> 23]);
      }
      else {
        o12.wave = 0;
        o12.nextwave =  0;
      }
  
  o12.phaseRemain = (o12.phase << 9) >> 17;



  if (xModeOn) {
    o2.wave = (((waveTableLoLink[o2.phase >> 23] * mixLo) + (waveTableMidLink[o2.phase >> 23] * (mixMid + mixHi)))) >> 11;
    o5.wave = (((waveTableLoLink[o5.phase >> 23] * mixLo) + (waveTableMidLink[o5.phase >> 23] * (mixMid + mixHi)))) >> 11;
    o8.wave = (((waveTableLoLink[o8.phase >> 23] * mixLo) + (waveTableMidLink[o8.phase >> 23] * (mixMid + mixHi)))) >> 11;
    o11.wave = (((waveTableLoLink[o11.phase >> 23] * mixLo) + (waveTableMidLink[o11.phase >> 23] * (mixMid + mixHi)))) >> 11;


    o2.nextwave = (((waveTableLoLink[(o2.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o2.phase + nextstep) >> 23] * (mixMid + mixHi)))) >> 11;
    o5.nextwave = (((waveTableLoLink[(o5.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o5.phase + nextstep) >> 23] * (mixMid + mixHi)))) >> 11;
    o8.nextwave = (( (waveTableLoLink[(o8.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o8.phase + nextstep) >> 23] * (mixMid + mixHi)))) >> 11;
    o11.nextwave = (( (waveTableLoLink[(o11.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o11.phase + nextstep) >> 23] * (mixMid + mixHi)))) >> 11;
  }
  else {
    o2.wave = (((waveTableHiLink[o2.phase >> 23] * mixHi) + (waveTableLoLink[o2.phase >> 23] * mixLo) + (waveTableMidLink[o2.phase >> 23] * mixMid))) >> 11;
    o5.wave = (((waveTableHiLink[o5.phase >> 23] * mixHi) + (waveTableLoLink[o5.phase >> 23] * mixLo) + (waveTableMidLink[o5.phase >> 23] * mixMid))) >> 11;
    o8.wave = (((waveTableHiLink[o8.phase >> 23] * mixHi) + (waveTableLoLink[o8.phase >> 23] * mixLo) + (waveTableMidLink[o8.phase >> 23] * mixMid))) >> 11;
    o11.wave = (((waveTableHiLink[o11.phase >> 23] * mixHi) + (waveTableLoLink[o11.phase >> 23] * mixLo) + (waveTableMidLink[o11.phase >> 23] * mixMid))) >> 11;


    o2.nextwave = (((waveTableHiLink[(o2.phase + nextstep) >> 23] * mixHi) + (waveTableLoLink[(o2.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o2.phase + nextstep) >> 23] * mixMid))) >> 11;
    o5.nextwave = (((waveTableHiLink[(o5.phase + nextstep) >> 23] * mixHi) + (waveTableLoLink[(o5.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o5.phase + nextstep) >> 23] * mixMid))) >> 11;
    o8.nextwave = (((waveTableHiLink[(o8.phase + nextstep) >> 23] * mixHi) + (waveTableLoLink[(o8.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o8.phase + nextstep) >> 23] * mixMid))) >> 11;
    o11.nextwave = (((waveTableHiLink[(o11.phase + nextstep) >> 23] * mixHi) + (waveTableLoLink[(o11.phase + nextstep) >> 23] * mixLo) + (waveTableMidLink[(o11.phase + nextstep) >> 23] * mixMid))) >> 11;
  }




  o2.wave = o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15);
  o3.wave = o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15);
  o5.wave = o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15);
  o6.wave = o6.wave + ((((o6.nextwave - o6.wave)) * o6.phaseRemain) >> 15);
  o8.wave = o8.wave + ((((o8.nextwave - o8.wave)) * o8.phaseRemain) >> 15);
  o9.wave = o9.wave + ((((o9.nextwave - o9.wave)) * o9.phaseRemain) >> 15);
  o11.wave = o11.wave + ((((o11.nextwave - o11.wave)) * o11.phaseRemain) >> 15);
  o12.wave = o12.wave + ((((o12.nextwave - o12.wave)) * o12.phaseRemain) >> 15);


//
  o1.wave =   (o2.wave * o3.wave) >> 15;
  o4.wave =   (o5.wave * o6.wave) >> 15;
  o7.wave =   (o8.wave * o9.wave) >> 15;
  o10.wave =   (o11.wave * o12.wave) >> 15;



  o8.wave = (ssat13((o4.wave + o7.wave + o10.wave + o1.wave)>>4))>>1; 
  o9.wave = (o8.wave>>3);
  o9.wave = (int32_t)((-((o9.wave * o9.wave *o9.wave)>>14))+(o8.wave + (o8.wave>>1)));
  o8.wave = ((int32_t)(o9.wave * mixEffectUp) >> 7) + (((int32_t)(o1.wave * mixEffectDn)) >> 11);

  //FinalOut = declickValue + (int32_t)((o8.wave * declickRampIn) >> 12);
  FinalOut = declickValue + ((o8.wave * declickRampIn) >> 12);
  analogWrite(aout2, FinalOut + 32000);


}




