void FASTRUN outUpdateISR_DEL(void){
 
  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((8192-delayTime)<<3))>>4;
 
  
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
     
    //-----------------------------------------------------------------------

    o2.wave = (
    (((int32_t)(((GWThi1[o2.phase>>23]*(511-GremHi))>>9) + ((GWThi2[o2.phase>>23]*(GremHi))>>9)))*mixHi)+
    (((int32_t)(((GWTlo1[o2.phase>>23]*(511-GremLo))>>9) + ((GWTlo2[o2.phase>>23]*(GremLo))>>9))) *mixLo)+
    (((int32_t)(((GWTmid1[o2.phase>>23]*(511-GremMid))>>9) + ((GWTmid2[o2.phase>>23]*(GremMid))>>9)))*mixMid))>>11;
    
    o2.nextwave = (
    (((int32_t)(((GWThi1[(o2.phase+nextstep)>>23]*(511-GremHi))>>9)  +  ((GWThi2[(o2.phase+nextstep)>>23]*(GremHi))>>9)))*mixHi)+
    (((int32_t)(((GWTlo1[(o2.phase+nextstep)>>23]*(511-GremLo))>>9)  +  ((GWTlo2[(o2.phase+nextstep)>>23]*(GremLo))>>9))) *mixLo)+
    (((int32_t)(((GWTmid1[(o2.phase+nextstep)>>23]*(511-GremMid))>>9)  +  ((GWTmid2[(o2.phase+nextstep)>>23]*(GremMid))>>9)))*mixMid))>>11;
    
    
    o2.wave = (o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15))>>4; 

    o4.wave = o2.wave  +  ((o3.wave * delayFeedback)>>11);
    
    
    delayTable[delayCounterShift] = o4.wave;
    
    o3.wave = delayTable[delayTimeShift]; 
    
    
   

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((((o3.wave+o2.wave)>>1)*((int)mixDetuneUp))>>10)  +  (((o2.wave *((int)mixDetuneDn))>>10)); //main out and mix detune 


    
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
    
    
    //-----------------------------------------------------------------------

    o2.wave = (
    
    (((int32_t)(((GWTlo1[o2.phase>>23]*(511-GremLo))>>9) + ((GWTlo2[o2.phase>>23]*(GremLo))>>9))) *mixLo)+
    (((int32_t)(((GWTmid1[o2.phase>>23]*(511-GremMid))>>9) + ((GWTmid2[o2.phase>>23]*(GremMid))>>9)))*(mixMid+mixHi)))>>11;
    
    o2.nextwave = (
    
    (((int32_t)(((GWTlo1[(o2.phase+nextstep)>>23]*(511-GremLo))>>9)  +  ((GWTlo2[(o2.phase+nextstep)>>23]*(GremLo))>>9))) *mixLo)+
    (((int32_t)(((GWTmid1[(o2.phase+nextstep)>>23]*(511-GremMid))>>9)  +  ((GWTmid2[(o2.phase+nextstep)>>23]*(GremMid))>>9)))*(mixMid+mixHi)))>>11; 
   
    
    o2.wave = (o2.wave+((((o2.nextwave - o2.wave)) * o2.phaseRemain) >>15))>>4; 

    o4.wave = o2.wave  +  ((o3.wave * delayFeedback)>>11);
    
    
    delayTable[delayCounterShift] = o4.wave;
    
    o3.wave = delayTable[delayTimeShift]; 
   

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((((o3.wave+o2.wave)>>1)*((int)mixDetuneUp))>>10)  +  (((o2.wave *((int)mixDetuneDn))>>10)); //main out and mix detune 
    
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
    
      
    //-----------------------------------------------------------------------
   
    o2.wave = (FMTable[o2.phase>>23]);    
    o2.nextwave =  (FMTable[(o2.phase+nextstep)>>23]);    
   
    
    o1.wave = ((
    (((int32_t)(((GWThi1[o1.phase>>23]*(511-GremHi))>>9) + ((GWThi2[o1.phase>>23]*(GremHi))>>9)))*mixHi)   +
    (((int32_t)(((GWTlo1[o1.phase>>23]*(511-GremLo))>>9) + ((GWTlo2[o1.phase>>23]*(GremLo))>>9)))*mixLo)   +
    (((int32_t)(((GWTmid1[o1.phase>>23]*(511-GremMid))>>9) + ((GWTmid2[o1.phase>>23]*(GremMid))>>9)))*mixMid)
    )>>4)>>11;
    
    o1.nextwave = ((
    (((int32_t)(((GWThi1[(o1.phase+nextstep)>>23]*(511-GremHi))>>9)  +  ((GWThi2[(o1.phase+nextstep)>>23]*(GremHi))>>9)))*mixHi)   +
    (((int32_t)(((GWTlo1[(o1.phase+nextstep)>>23]*(511-GremLo))>>9)  +  ((GWTlo2[(o1.phase+nextstep)>>23]*(GremLo))>>9)))*mixLo)   +
    (((int32_t)(((GWTmid1[(o1.phase+nextstep)>>23]*(511-GremMid))>>9)  +  ((GWTmid2[(o1.phase+nextstep)>>23]*(GremMid))>>9)))*mixMid)
    )>>4)>>11;
        
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15); 
    
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
    //o4.wave = o4.wave +((((o4.nextwave - o4.wave))* o4.phaseRemain)>>15);
   

    
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15));    
    
    
    
    o4.wave = o1.wave  +  ((o3.wave * delayFeedback)>>11);
    
    
    delayTable[delayCounterShift] = o4.wave;
    
    o3.wave = delayTable[delayTimeShift]; 
   

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((((o3.wave+o1.wave)>>1)*((int)mixDetuneUp))>>10)  +  (((o1.wave *((int)mixDetuneDn))>>10)); //main out and mix detune
      
    
    analogWrite(aout2,AGCtest+4000);
  
  
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
    
   
       
    //-----------------------------------------------------------------------
   
    o2.wave = (FMTable[o2.phase>>23]);    
    o2.nextwave =  (FMTable[(o2.phase+nextstep)>>23]);    
   
   
    
    o1.wave = ((
    
    (((int32_t)(((GWTlo1[o1.phase>>23]*(511-GremLo))>>9) + ((GWTlo2[o1.phase>>23]*(GremLo))>>9)))*mixLo)   +
    (((int32_t)(((GWTmid1[o1.phase>>23]*(511-GremMid))>>9) + ((GWTmid2[o1.phase>>23]*(GremMid))>>9)))*(mixMid+mixHi))
    )>>4)>>11;
    
    o1.nextwave = ((
    
    (((int32_t)(((GWTlo1[(o1.phase+nextstep)>>23]*(511-GremLo))>>9)  +  ((GWTlo2[(o1.phase+nextstep)>>23]*(GremLo))>>9)))*mixLo)   +
    (((int32_t)(((GWTmid1[(o1.phase+nextstep)>>23]*(511-GremMid))>>9)  +  ((GWTmid2[(o1.phase+nextstep)>>23]*(GremMid))>>9)))*(mixMid+mixHi))
    )>>4)>>11;
    
        
    o1.wave = o1.wave+((((o1.nextwave - o1.wave)) * o1.phaseRemain) >>15); 
        
    
    o2.wave = o2.wave +((((o2.nextwave - o2.wave))* o2.phaseRemain)>>15);
       
    o1.wave = ((o1.wave *(2047-CZMix))>>11)  +  ((int32_t)(((o1.wave) * ((o2.wave*CZMix)>>11))>>15));    
    o4.wave = o1.wave  +  ((o3.wave * delayFeedback)>>11);
    
    
    delayTable[delayCounterShift] = o4.wave;
    
    o3.wave = delayTable[delayTimeShift]; 
   

  //  AGCtest = o1.wave >>13; 
   AGCtest = ((((o3.wave+o1.wave)>>1)*((int)mixDetuneUp))>>10)  +  (((o1.wave *((int)mixDetuneDn))>>10)); //main out and mix detune
    
    analogWrite(aout2,AGCtest+4000);
  
    break;   
  
  }
   
 //digitalWriteFast (oSQout,1);//temp testing OC 
}



