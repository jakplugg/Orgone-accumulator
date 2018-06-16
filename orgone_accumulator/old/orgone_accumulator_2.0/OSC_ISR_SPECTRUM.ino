void FASTRUN outUpdateISR_SPECTRUM(void) {

  SUBMULOC();
  DECLICK_CHECK();
   NOISELIVE0();
  NOISELIVE1();


    noiseTable3[0] = noiseTable3[1] = (noiseTable3[0] + NT3Rate);
      noiseTable[o1.phase >> 23] = random(-32767, 32767); //replace noise cells with random values.

      //FM oscillator spectrum mode has only 1.
      o1.phase = o1.phase + o1.phase_increment;     
      o1.phaseRemain = (o1.phase << 9) >> 17;
      o1.wave = (FMTable[o1.phase >> WTShiftFM]);
      o1.nextwave =  (FMTable[(o1.phase + nextstep) >> WTShiftFM]);
      o1.wave = o1.wave + ((((o1.nextwave - o1.wave)) * o1.phaseRemain) >> 15);     
      
     


      o2.phase = o2.phase +  (o2.phase_increment + o1.index) ;
       if (o1.phaseOld > o2.phase) {
        //lfo.phase = 0; 
        if(!FMmodeOn)o1.phase=0;
      }     
      o1.phaseOld = o2.phase;
      o2.phaseRemain = (o2.phase << 9) >> 17; //ROOT

       
        lfo.phase = lfo.phase + lfo.phase_increment;
        lfo.wave = (PENV[lfo.phase >> 23]);
        lfo.nextwave =  (PENV[(lfo.phase + nextstep) >> 23]);
     
     
      

      //harmonic oscillators  ------------3-10---------
      o3.phase = o3.phase +  (o3.phase_increment + o1.index) + (FXMixer[0] * o2.wave) + (FXMixer[1] * o4.wave) + o1.phaseOffset;
      o3.phaseRemain = (o3.phase << 9) >> 17; //5th

      o4.phase = o4.phase +  (o4.phase_increment + o1.index) + (FXMixer[0] * o3.wave) + (FXMixer[1] * o5.wave) + o1.phaseOffset;
      o4.phaseRemain = (o4.phase << 9) >> 17; //OCT

      o5.phase = o5.phase +  (o5.phase_increment + o1.index) + (FXMixer[0] * o4.wave) + (FXMixer[1] * o6.wave) + o1.phaseOffset;
      o5.phaseRemain = (o5.phase << 9) >> 17; //3rd harm

      o6.phase = o6.phase + (o6.phase_increment + o1.index) + (FXMixer[0] * o5.wave) + (FXMixer[1] * o3.wave) + o1.phaseOffset;
      o6.phaseRemain = (o6.phase << 9) >> 17; //4th harm

      o7.phase = o7.phase +  (o7.phase_increment + o1.index) + (FXMixer[0] * o6.wave) + (FXMixer[1] * o2.wave) + o1.phaseOffset;
      o7.phaseRemain = (o7.phase << 9) >> 17; //5th harm

      o8.phase = o8.phase +  (o8.phase_increment + o1.index) + (FXMixer[0] * o7.wave) + (FXMixer[1] * o7.wave) + o1.phaseOffset;
      o8.phaseRemain = (o8.phase << 9) >> 17; //6th harm

      o9.phase = o9.phase +  (o9.phase_increment + o1.index) + (FXMixer[0] * o8.wave) + (FXMixer[1] * o8.wave) + o1.phaseOffset;
      o9.phaseRemain = (o9.phase << 9) >> 17; //7th harm

      o10.phase = o10.phase + (o10.phase_increment + o1.index) + (FXMixer[0] * o9.wave) + (FXMixer[1] * o9.wave) + o1.phaseOffset;
      o10.phaseRemain = (o10.phase << 9) >> 17;//8th harm
      //-----------------------------------------------------------------------


      o2.wave = FMTable[o2.phase >> 23];
      o3.wave = FMTable[o3.phase >> 23];
      o4.wave = FMTable[o4.phase >> 23];
      o5.wave = FMTable[o5.phase >> 23];
      o6.wave = FMTable[o6.phase >> 23];
      o7.wave = FMTable[o7.phase >> 23];
      o8.wave = FMTable[o8.phase >> 23];
      o9.wave = FMTable[o9.phase >> 23];
      o10.wave = FMTable[o10.phase >> 23];


      o2.nextwave = FMTable[(o2.phase + nextstep) >> 23];
      o3.nextwave = FMTable[(o3.phase + nextstep) >> 23];
      o4.nextwave = FMTable[(o4.phase + nextstep) >> 23];
      o5.nextwave = FMTable[(o5.phase + nextstep) >> 23];
      o6.nextwave = FMTable[(o6.phase + nextstep) >> 23];
      o7.nextwave = FMTable[(o7.phase + nextstep) >> 23];
      o8.nextwave = FMTable[(o8.phase + nextstep) >> 23];
      o9.nextwave = FMTable[(o9.phase + nextstep) >> 23];
      o10.nextwave = FMTable[(o10.phase + nextstep) >> 23];


      o2.wave = (o2.wave + ((((o2.nextwave - o2.wave)) * o2.phaseRemain) >> 15));
      o3.wave = (o3.wave + ((((o3.nextwave - o3.wave)) * o3.phaseRemain) >> 15));
      o4.wave = (o4.wave + ((((o4.nextwave - o4.wave)) * o4.phaseRemain) >> 15));
      o5.wave = (o5.wave + ((((o5.nextwave - o5.wave)) * o5.phaseRemain) >> 15));
      o6.wave = (o6.wave + ((((o6.nextwave - o6.wave)) * o6.phaseRemain) >> 15));
      o7.wave = (o7.wave + ((((o7.nextwave - o7.wave)) * o7.phaseRemain) >> 15));
      o8.wave = (o8.wave + ((((o8.nextwave - o8.wave)) * o8.phaseRemain) >> 15));
      o9.wave = (o9.wave + ((((o9.nextwave - o9.wave)) * o9.phaseRemain) >> 15));
      o10.wave = (o10.wave + ((((o10.nextwave - o10.wave)) * o10.phaseRemain) >> 15));
      lfo.wave = (lfo.wave + ((((lfo.nextwave - lfo.wave)) * lfo.phaseRemain) >> 15));
      
      o1.phaseOffset = o2.wave>>3;
      
      o12.wave = (o2.wave *o2.index)>>12;
      o3.wave = (o3.wave *o3.index)>>12;
      o4.wave = (o4.wave *o4.index)>>12;
      o5.wave = (o5.wave *o5.index)>>12;
      o6.wave = (o6.wave *o6.index)>>12;
      o7.wave = (o7.wave *o7.index)>>12;
      o8.wave = (o8.wave *o8.index)>>12;
      o9.wave = (o9.wave *o9.index)>>12;
      o10.wave = (o10.wave *o10.index)>>12;
      
      
      
      
      

     if (pulsarOn) {
     o4.wave = (o10.wave + o4.wave + o6.wave + o8.wave + o3.wave + o5.wave + o7.wave + o9.wave); //main out and mix detune     
     o4.wave = (o4.wave * max(o2.wave,0))>>14;
     }
     else o4.wave = (o10.wave + o4.wave + o6.wave + o8.wave + o12.wave + o3.wave + o5.wave + o7.wave + o9.wave); //main out and mix detune
//     
     
     if (!FMmodeOn){ o4.wave = (o4.wave*(2047-CZMix)>>11)+((((o4.wave*o1.wave)>>13) * CZMix) >> 13);}
     o1.index = (FMIndex * o1.wave);
     //else o1.phaseOffset = (int32_t)((o4.wave * CZMix) >> 11) ; //FM modulator
    
     
      
      FinalOut = declickValue + ((o4.wave * declickRampIn) >> 12);

      analogWrite(aout2, FinalOut + 32000);

 

  //digitalWriteFast (oSQout,1);//temp testing OC
}



