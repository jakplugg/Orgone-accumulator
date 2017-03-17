void FASTRUN outUpdateISR_CHORD(void){
 //noInterrupts();  

 //digitalWriteFast (oSQout,0);//temp testing OC
 
  
  oSQ.phase = oSQ.phase +  (uint32_t)oSQ.phase_increment; //square wave osc
  digitalWriteFast (oSQout,(oSQ.phase < oSQ.PW)); //pulse out 
  
  

  switch(oscMode){
    
  //-----------------------------------------------FM MODE OSCILLATORS-----------------------------------------------
  case 0:
  
   noiseTable3[0]=noiseTable3[1]=(noiseTable3[0]+NT3Rate);
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.  

    //main oscillator
    o1.phase = o1.phase + o1.phase_increment; 
    o1.phaseRemain = (o1.phase<<9)>>17;    
    o1.wave = (FMTable[o1.phase>>WTShift]);
    o1.nextwave =  (FMTable[(o1.phase+nextstep)>>WTShift]);
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);    
    o1.index = (FMIndex * o1.wave);   
    o2.phase = o2.phase +  (o2.phase_increment+o1.index);
    o2.phaseRemain = (o2.phase<<9)>>17;    
    //unisone oscillators  ------------3-4---------
    o3.phase = o3.phase + o3.phase_increment;
    o3.phaseRemain = (o3.phase<<9)>>17;       
    o3.wave = (FMTable[o3.phase>>WTShift]);
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>WTShift]);
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    o3.index = (FMIndex * o3.wave);  
    o4.phase = o4.phase +  (o4.phase_increment+o3.index);
    o4.phaseRemain = (o4.phase<<9)>>17;      
    //---------------------------------5-6------------ 
    o5.phase = o5.phase + o5.phase_increment; 
    o5.phaseRemain = (o5.phase<<9)>>17;     
    o5.wave = (FMTable[o5.phase>>WTShift]);
    o5.nextwave =  (FMTable[(o5.phase+nextstep)>>WTShift]);
    o5.wave = o5.wave+((((o5.nextwave - o5.wave)) * o5.phaseRemain) >>15); 
    o5.index = (FMIndex * o5.wave);  
    o6.phase = o6.phase + (o6.phase_increment+o5.index); 
    o6.phaseRemain = (o6.phase<<9)>>17;     
    //-------------------------------7-8-------------- 
    o7.phase = o7.phase + o7.phase_increment; 
    o7.phaseRemain = (o7.phase<<9)>>17;     
    o7.wave = (FMTable[o7.phase>>WTShift]);
    o7.nextwave =  (FMTable[(o7.phase+nextstep)>>WTShift]);
    o7.wave = o7.wave+((((o7.nextwave - o7.wave)) * o7.phaseRemain) >>15); 
    o7.index = (FMIndex * o7.wave);   
    o8.phase = o8.phase +  (o8.phase_increment+o7.index);
    o8.phaseRemain = (o8.phase<<9)>>17;    
    //------------------------------9-10-------------------
    o9.phase = o9.phase + o9.phase_increment;
    o9.phaseRemain = (o9.phase<<9)>>17;      
    o9.wave = (FMTable[o9.phase>>WTShift]);
    o9.nextwave =  (FMTable[(o9.phase+nextstep)>>WTShift]);
    o9.wave = o9.wave+((((o9.nextwave - o9.wave)) * o9.phaseRemain) >>15); 
    o9.index = (FMIndex * o9.wave);   
    o10.phase = o10.phase + (o10.phase_increment+o9.index); 
    o10.phaseRemain = (o10.phase<<9)>>17;     
    //-----------------------------------------------------------------------

    o2.wave = (((waveTableLink[o2.phase>>23]*mixHi)+(waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*mixMid)))>>11;
    o4.wave = (((waveTableLink[o4.phase>>23]*mixHi)+(waveTable2Link[o4.phase>>23]*mixLo)+(waveTableMidLink[o4.phase>>23]*mixMid)))>>11;
    o6.wave = (((waveTableLink[o6.phase>>23]*mixHi)+(waveTable2Link[o6.phase>>23]*mixLo)+(waveTableMidLink[o6.phase>>23]*mixMid)))>>11;
    o8.wave = (((waveTableLink[o8.phase>>23]*mixHi)+(waveTable2Link[o8.phase>>23]*mixLo)+(waveTableMidLink[o8.phase>>23]*mixMid)))>>11;
    o10.wave = (((waveTableLink[o10.phase>>23]*mixHi)+(waveTable2Link[o10.phase>>23]*mixLo)+(waveTableMidLink[o10.phase>>23]*mixMid)))>>11;  
  
    o2.nextwave = (((waveTableLink[(o2.phase + nextstep)>>23]*mixHi)+(waveTable2Link[(o2.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase + nextstep)>>23]*mixMid)))>>11;
    o4.nextwave = (((waveTableLink[(o4.phase + nextstep)>>23]*mixHi)+(waveTable2Link[(o4.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o4.phase + nextstep)>>23]*mixMid)))>>11;
    o6.nextwave = (((waveTableLink[(o6.phase + nextstep)>>23]*mixHi)+(waveTable2Link[(o6.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o6.phase + nextstep)>>23]*mixMid)))>>11;
    o8.nextwave = (((waveTableLink[(o8.phase + nextstep)>>23]*mixHi)+(waveTable2Link[(o8.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o8.phase + nextstep)>>23]*mixMid)))>>11;
    o10.nextwave = (((waveTableLink[(o10.phase + nextstep)>>23]*mixHi)+(waveTable2Link[(o10.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o10.phase + nextstep)>>23]*mixMid)))>>11;    
    
    o2.wave = o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15); 
    o4.wave = o4.wave+((((o4.nextwave - o4.wave)) * o4.phaseRemain) >>15); 
    o6.wave = o6.wave+((((o6.nextwave - o6.wave)) * o6.phaseRemain) >>15); 
    o8.wave = o8.wave+((((o8.nextwave - o8.wave)) * o8.phaseRemain) >>15); 
    o10.wave = o10.wave+((((o10.nextwave - o10.wave)) * o10.phaseRemain) >>15); 

    AGCtest = ((((o4.wave+o6.wave+o8.wave)>>2)*((int)mixDetuneUp))>>14)  +  (((o2.wave*((int)mixDetuneDn))>>14)); //main out and mix detune
    
    analogWrite(aout2,AGCtest+4000);
    
    
    break;  
    
    //-----------------------------------------------ALT FM MODE OSCILLATORS-----------------------------------------------
  case 2:
  
  
noiseTable3[0]=noiseTable3[1]=(noiseTable3[0]+NT3Rate);
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.  

    //main oscillator
    o1.phase = o1.phase + o1.phase_increment; 
    o1.phaseRemain = (o1.phase<<9)>>17;    
    o1.wave = (FMTable[o1.phase>>WTShift]);
    o1.nextwave =  (FMTable[(o1.phase+nextstep)>>WTShift]);
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15);    
    o1.index = (FMIndex * o1.wave);   
    o2.phase = o2.phase +  (o2.phase_increment+o1.index);
    o2.phaseRemain = (o2.phase<<9)>>17;    
    //unisone oscillators  ------------3-4---------
    o3.phase = o3.phase + o3.phase_increment;
    o3.phaseRemain = (o3.phase<<9)>>17;       
    o3.wave = (FMTable[o3.phase>>WTShift]);
    o3.nextwave =  (FMTable[(o3.phase+nextstep)>>WTShift]);
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15); 
    o3.index = (FMIndex * o3.wave);  
    o4.phase = o4.phase +  (o4.phase_increment+o3.index);
    o4.phaseRemain = (o4.phase<<9)>>17;      
    //---------------------------------5-6------------ 
    o5.phase = o5.phase + o5.phase_increment; 
    o5.phaseRemain = (o5.phase<<9)>>17;     
    o5.wave = (FMTable[o5.phase>>WTShift]);
    o5.nextwave =  (FMTable[(o5.phase+nextstep)>>WTShift]);
    o5.wave = o5.wave+((((o5.nextwave - o5.wave)) * o5.phaseRemain) >>15); 
    o5.index = (FMIndex * o5.wave);  
    o6.phase = o6.phase + (o6.phase_increment+o5.index); 
    o6.phaseRemain = (o6.phase<<9)>>17;     
    //-------------------------------7-8-------------- 
    o7.phase = o7.phase + o7.phase_increment; 
    o7.phaseRemain = (o7.phase<<9)>>17;     
    o7.wave = (FMTable[o7.phase>>WTShift]);
    o7.nextwave =  (FMTable[(o7.phase+nextstep)>>WTShift]);
    o7.wave = o7.wave+((((o7.nextwave - o7.wave)) * o7.phaseRemain) >>15); 
    o7.index = (FMIndex * o7.wave);   
    o8.phase = o8.phase +  (o8.phase_increment+o7.index);
    o8.phaseRemain = (o8.phase<<9)>>17;    
    //------------------------------9-10-------------------
    o9.phase = o9.phase + o9.phase_increment;
    o9.phaseRemain = (o9.phase<<9)>>17;      
    o9.wave = (FMTable[o9.phase>>WTShift]);
    o9.nextwave =  (FMTable[(o9.phase+nextstep)>>WTShift]);
    o9.wave = o9.wave+((((o9.nextwave - o9.wave)) * o9.phaseRemain) >>15); 
    o9.index = (FMIndex * o9.wave);   
    o10.phase = o10.phase + (o10.phase_increment+o9.index); 
    o10.phaseRemain = (o10.phase<<9)>>17;     
    //-----------------------------------------------------------------------

    o2.wave = (((waveTable2Link[o2.phase>>23]*mixLo)+(waveTableMidLink[o2.phase>>23]*(mixMid+mixHi))))>>11;
    o4.wave = (((waveTable2Link[o4.phase>>23]*mixLo)+(waveTableMidLink[o4.phase>>23]*(mixMid+mixHi))))>>11;
    o6.wave = (((waveTable2Link[o6.phase>>23]*mixLo)+(waveTableMidLink[o6.phase>>23]*(mixMid+mixHi))))>>11;
    o8.wave = (((waveTable2Link[o8.phase>>23]*mixLo)+(waveTableMidLink[o8.phase>>23]*(mixMid+mixHi))))>>11;
    o10.wave = (((waveTable2Link[o10.phase>>23]*mixLo)+(waveTableMidLink[o10.phase>>23]*(mixMid+mixHi))))>>11;  
  
    o2.nextwave = (((waveTable2Link[(o2.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o2.phase + nextstep)>>23]*(mixMid+mixHi))))>>11;
    o4.nextwave = (((waveTable2Link[(o4.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o4.phase + nextstep)>>23]*(mixMid+mixHi))))>>11;
    o6.nextwave = (((waveTable2Link[(o6.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o6.phase + nextstep)>>23]*(mixMid+mixHi))))>>11;
    o8.nextwave = (((waveTable2Link[(o8.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o8.phase + nextstep)>>23]*(mixMid+mixHi))))>>11;
    o10.nextwave = (((waveTable2Link[(o10.phase + nextstep)>>23]*mixLo)+(waveTableMidLink[(o10.phase + nextstep)>>23]*(mixMid+mixHi))))>>11;    
    
    o2.wave = o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15); 
    o4.wave = o4.wave+((((o4.nextwave - o4.wave)) * o4.phaseRemain) >>15); 
    o6.wave = o6.wave+((((o6.nextwave - o6.wave)) * o6.phaseRemain) >>15); 
    o8.wave = o8.wave+((((o8.nextwave - o8.wave)) * o8.phaseRemain) >>15); 
    o10.wave = o10.wave+((((o10.nextwave - o10.wave)) * o10.phaseRemain) >>15); 

    AGCtest = ((((o4.wave+o6.wave+o8.wave)>>2)*((int)mixDetuneUp))>>14)  +  (((o2.wave*((int)mixDetuneDn))>>14)); //main out and mix detune
            
    analogWrite(aout2,AGCtest+4000);     
   
        
    break;  
     
    
  case 1://-------------------------------------------CZ MODE OSCILLATORS-----------------------------------------------

    
    o1.phase = o1.phase + o1.phase_increment; 
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = 0; //check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;       
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
    
    //unisone oscillators  ------------3-4---------
    o3.phase = o3.phase + o3.phase_increment;  
    if (o3.phaseOld > o3.phase) o4.phase = 0;
    o3.phaseOld = o3.phase;    
    o4.phase = o4.phase +  o4.phase_increment; 
    o4.phaseRemain = (o4.phase<<9)>>17; //used for fake interpolation
    o3.phaseRemain = (o3.phase<<9)>>17;  
    //---------------------------------5-6------------ 
    o5.phase = o5.phase + o5.phase_increment; 
    if (o5.phaseOld > o5.phase) o6.phase = 0;
    o5.phaseOld = o5.phase;     
    o6.phase = o6.phase + o6.phase_increment; 
    o6.phaseRemain = (o6.phase<<9)>>17; //used for fake interpolation
    o5.phaseRemain = (o5.phase<<9)>>17;  
    //-------------------------------7-8-------------- 
    o7.phase = o7.phase + o7.phase_increment; 
    if (o7.phaseOld > o7.phase) o8.phase = 0;
    o7.phaseOld = o7.phase;       
    o8.phase = o8.phase +  o8.phase_increment; 
    o8.phaseRemain = (o8.phase<<9)>>17; //used for fake interpolation
    o7.phaseRemain = (o7.phase<<9)>>17;
    //------------------------------9-10-------------------
    o9.phase = o9.phase + o9.phase_increment; 
    if (o9.phaseOld > o9.phase) o10.phase = 0;
    o9.phaseOld = o9.phase;       
    o10.phase = o10.phase + o10.phase_increment;  
   o10.phaseRemain = (o10.phase<<9)>>17; //used for fake interpolation
    o9.phaseRemain = (o9.phase<<9)>>17; 
    
    //-----------------------------------------------------------------------
   
    o2.wave = (FMTable[o2.phase>>23]);    
    o2.nextwave =  (FMTable[(o2.phase+nextstep)>>23]);    
    o4.wave = (FMTable[o4.phase>>23]);    
    o4.nextwave =  (FMTable[(o4.phase+nextstep)>>23]); 
    o6.wave = (FMTable[o6.phase>>23]);    
    o6.nextwave =  (FMTable[(o6.phase+nextstep)>>23]); 
    o8.wave = (FMTable[o8.phase>>23]);    
    o8.nextwave =  (FMTable[(o8.phase+nextstep)>>23]); 
    o10.wave = (FMTable[o10.phase>>23]);    
    o10.nextwave =  (FMTable[(o10.phase+nextstep)>>23]); 
    
    o1.wave = (((waveTableLink[o1.phase>>23]*mixHi)+(waveTable2Link[o1.phase>>23]*mixLo)+(waveTableMidLink[o1.phase>>23]*mixMid))>>4)>>11;
    o1.nextwave = (((waveTableLink[(o1.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o1.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o1.phase+nextstep)>>23]*mixMid))>>4)>>11;
    o3.wave = (((waveTableLink[o3.phase>>23]*mixHi)+(waveTable2Link[o3.phase>>23]*mixLo)+(waveTableMidLink[o3.phase>>23]*mixMid))>>4)>>11;
    o3.nextwave = (((waveTableLink[(o3.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o3.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o3.phase+nextstep)>>23]*mixMid))>>4)>>11;
    o5.wave = (((waveTableLink[o5.phase>>23]*mixHi)+(waveTable2Link[o5.phase>>23]*mixLo)+(waveTableMidLink[o5.phase>>23]*mixMid))>>4)>>11;
    o5.nextwave = (((waveTableLink[(o5.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o5.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o5.phase+nextstep)>>23]*mixMid))>>4)>>11;
    o7.wave = (((waveTableLink[o7.phase>>23]*mixHi)+(waveTable2Link[o7.phase>>23]*mixLo)+(waveTableMidLink[o7.phase>>23]*mixMid))>>4)>>11;
    o7.nextwave = (((waveTableLink[(o7.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o7.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o7.phase+nextstep)>>23]*mixMid))>>4)>>11;
    o9.wave = (((waveTableLink[o9.phase>>23]*mixHi)+(waveTable2Link[o9.phase>>23]*mixLo)+(waveTableMidLink[o9.phase>>23]*mixMid))>>4)>>11;
    o9.nextwave = (((waveTableLink[(o9.phase+nextstep)>>23]*mixHi)+(waveTable2Link[(o9.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o9.phase+nextstep)>>23]*mixMid))>>4)>>11;
    
        
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15); 
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15);
    o5.wave = o5.wave+((((o5.nextwave - o5.wave)) * o5.phaseRemain) >>15);
    o7.wave = o7.wave+((((o7.nextwave - o7.wave)) * o7.phaseRemain) >>15);
    o9.wave = o9.wave+((((o9.nextwave - o9.wave)) * o9.phaseRemain) >>15);
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
    o6.wave = o6.wave +((((o6.nextwave - o6.wave))* o6.phaseRemain)>>15);
    o8.wave = o8.wave +((((o8.nextwave - o8.wave))* o8.phaseRemain)>>15);
    o10.wave = o10.wave +((((o10.nextwave - o10.wave))* o10.phaseRemain)>>15);
    

    
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15));    
    o3.wave = ((o3.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o3.wave) * ((o4.wave*CZMix)>>11))>>15));
    o5.wave = ((o5.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o5.wave) * ((o6.wave*CZMix)>>11))>>15));
    o7.wave = ((o7.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o7.wave) * ((o8.wave*CZMix)>>11))>>15));
    o9.wave = ((o9.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o9.wave) * ((o10.wave*CZMix)>>11))>>15)); 
   
    

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((o3.wave+o5.wave+o7.wave)>>2);
   o1.wave = ((AGCtest * ((int)mixDetuneUp))>>10)  +  (((o1.wave *((int)mixDetuneDn))>>10)); //main out and mix detune
   //o1.maxlev = max(AGCtest,o1.maxlev);
   
      
    
    analogWrite(aout2,o1.wave+4000);
  
  
  break;
  
 
  
    //----------------------------------------------ALT CZ mode-----------------------------------------
    case 3: 

   lfo.phase = lfo.phase + lfo.phase_increment;
    lfo.wave = FMTableAMX[lfo.phase>>23];    
    
    o1.phaseOffset = (FMX_HiOffset * lfo.wave);
    o1.phase = o1.phase + (o1.phase_increment + o1.phaseOffset); 
    noiseTable[o1.phase>>23]= random(-32767,32767); //replace noise cells with random values.
    if (o1.phaseOld > o1.phase)o2.phase = 0; //check for sync reset osc in CZ mode.        
    o1.phaseOld = o1.phase;       
    o2.phase = o2.phase +  o2.phase_increment; 
    o2.phaseRemain = (o2.phase<<9)>>17; //used for fake interpolation
    o1.phaseRemain = (o1.phase<<9)>>17;
    
    //unisone oscillators  ------------3-4---------
    o3.phaseOffset = (FMX_HiOffset * lfo.wave);
    o3.phase = o3.phase + (o3.phase_increment + o3.phaseOffset);  
    if (o3.phaseOld > o3.phase) o4.phase = 0;
    o3.phaseOld = o3.phase;    
    o4.phase = o4.phase +  o4.phase_increment; 
    o4.phaseRemain = (o4.phase<<9)>>17; //used for fake interpolation
    o3.phaseRemain = (o3.phase<<9)>>17;  
    //---------------------------------5-6------------ 
    o5.phaseOffset = (FMX_HiOffset * lfo.wave);
    o5.phase = o5.phase + (o5.phase_increment + o5.phaseOffset); 
    if (o5.phaseOld > o5.phase) o6.phase = 0;
    o5.phaseOld = o5.phase;     
    o6.phase = o6.phase + o6.phase_increment; 
    o6.phaseRemain = (o6.phase<<9)>>17; //used for fake interpolation
    o5.phaseRemain = (o5.phase<<9)>>17;  
    //-------------------------------7-8-------------- 
    o7.phaseOffset = (FMX_HiOffset * lfo.wave);
    o7.phase = o7.phase + (o7.phase_increment + o7.phaseOffset); 
    if (o7.phaseOld > o7.phase) o8.phase = 0;
    o7.phaseOld = o7.phase;       
    o8.phase = o8.phase +  o8.phase_increment; 
    o8.phaseRemain = (o8.phase<<9)>>17; //used for fake interpolation
    o7.phaseRemain = (o7.phase<<9)>>17;
    //------------------------------9-10-------------------
    o9.phaseOffset = (FMX_HiOffset * lfo.wave);
    o9.phase = o9.phase + (o9.phase_increment + o9.phaseOffset); 
    if (o9.phaseOld > o9.phase) o10.phase = 0;
    o9.phaseOld = o9.phase;       
    o10.phase = o10.phase + o10.phase_increment;  
   o10.phaseRemain = (o10.phase<<9)>>17; //used for fake interpolation
    o9.phaseRemain = (o9.phase<<9)>>17; 
    
    //-----------------------------------------------------------------------
   
    o2.wave = (FMTable[o2.phase>>23]);    
    o2.nextwave =  (FMTable[(o2.phase+nextstep)>>23]);    
    o4.wave = (FMTable[o4.phase>>23]);    
    o4.nextwave =  (FMTable[(o4.phase+nextstep)>>23]); 
    o6.wave = (FMTable[o6.phase>>23]);    
    o6.nextwave =  (FMTable[(o6.phase+nextstep)>>23]); 
    o8.wave = (FMTable[o8.phase>>23]);    
    o8.nextwave =  (FMTable[(o8.phase+nextstep)>>23]); 
    o10.wave = (FMTable[o10.phase>>23]);    
    o10.nextwave =  (FMTable[(o10.phase+nextstep)>>23]); 
    
    o1.wave = (((waveTable2Link[o1.phase>>23]*mixLo)+(waveTableMidLink[o1.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o1.nextwave = (((waveTable2Link[(o1.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o1.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    o3.wave = (((waveTable2Link[o3.phase>>23]*mixLo)+(waveTableMidLink[o3.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o3.nextwave = (((waveTable2Link[(o3.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o3.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    o5.wave = (((waveTable2Link[o5.phase>>23]*mixLo)+(waveTableMidLink[o5.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o5.nextwave = (((waveTable2Link[(o5.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o5.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    o7.wave = (((waveTable2Link[o7.phase>>23]*mixLo)+(waveTableMidLink[o7.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o7.nextwave = (((waveTable2Link[(o7.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o7.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    o9.wave = (((waveTable2Link[o9.phase>>23]*mixLo)+(waveTableMidLink[o9.phase>>23]*(mixMid+mixHi)))>>4)>>11;
    o9.nextwave = (((waveTable2Link[(o9.phase+nextstep)>>23]*mixLo)+(waveTableMidLink[(o9.phase+nextstep)>>23]*(mixMid+mixHi)))>>4)>>11;
    
        
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15); 
    o3.wave = o3.wave+((((o3.nextwave - o3.wave)) * o3.phaseRemain) >>15);
    o5.wave = o5.wave+((((o5.nextwave - o5.wave)) * o5.phaseRemain) >>15);
    o7.wave = o7.wave+((((o7.nextwave - o7.wave)) * o7.phaseRemain) >>15);
    o9.wave = o9.wave+((((o9.nextwave - o9.wave)) * o9.phaseRemain) >>15);
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
    o6.wave = o6.wave +((((o6.nextwave - o6.wave))* o6.phaseRemain)>>15);
    o8.wave = o8.wave +((((o8.nextwave - o8.wave))* o8.phaseRemain)>>15);
    o10.wave = o10.wave +((((o10.nextwave - o10.wave))* o10.phaseRemain)>>15);
    

    
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15));    
    o3.wave = ((o3.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o3.wave) * ((o4.wave*CZMix)>>11))>>15));
    o5.wave = ((o5.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o5.wave) * ((o6.wave*CZMix)>>11))>>15));
    o7.wave = ((o7.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o7.wave) * ((o8.wave*CZMix)>>11))>>15));
    o9.wave = ((o9.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o9.wave) * ((o10.wave*CZMix)>>11))>>15));  
    

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((((o7.wave+o5.wave+o3.wave)>>2)*((int)mixDetuneUp))>>10)  +  (((o1.wave *((int)mixDetuneDn))>>10)); //main out and mix detune
      
    
    analogWrite(aout2,AGCtest+4000);
  
    break;   
  
  }
   
 //digitalWriteFast (oSQout,1);//temp testing OC 
}



