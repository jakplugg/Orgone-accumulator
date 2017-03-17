void TUNELOCK_TOGGLE()
{
 buh = digitalReadFast(tuneLockSwitch);
    if (tuneLockOn != buh){
      tuneLockOn = buh;
      LED_MCD = LED_MST;
      digitalWriteFast(LED_TuneLock,tuneLockOn);}}


void SELECT_ISRS(){

     LED_MCD = LED_MST;    
  
      switch (FX){
    case 0: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_MAIN,ISRrate);
      primeDetuneOn = 0;  
      break;
    case 1: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_MAIN,ISRrate); 
      primeDetuneOn =1; 
      break;
    case 2: 
       outUpdateTimer.end();
       outUpdateTimer.begin(outUpdateISR_DEL,ISRrate);
      break;
    case 3: 
      outUpdateTimer.end();
      o1.phase =        
      o2.phase =      
      o3.phase =     
      o4.phase =       
      o5.phase =       
      o6.phase =     
      o7.phase =       
      o8.phase =       
      o9.phase = 
      lfo.phase =      
      o10.phase = 0;
      outUpdateTimer.begin(outUpdateISR_PULSAR,ISRrate);
      break;
    case 4: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_CRUSH,ISRrate); 
      break;
      case 5: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_FOLD,ISRrate); 
      break; 
      case 6: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_MODMOD,ISRrate); 
      break; 
      case 7: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_CHORD,ISRrate); 
      break; 
      case 8: 
      outUpdateTimer.end();
      outUpdateTimer.begin(outUpdateISR_CHORD,ISRrate); 
      break; 
      
}}

void GRADUALWAVE(){
  switch(oscMode){
  case 0:  
  GWTlo1 = FMWTselLo[analogControls[8]>>9]; //select "from" wave
  GWTlo2 = FMWTselLo[(((analogControls[8]>>9)+1)<<27)>>27]; //select "to" wave and modulo 16
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23); //get remainder for mix amount
  
  GWTmid1 = FMWTselMid[analogControls[5]>>9];
  GWTmid2 = FMWTselMid[(((analogControls[5]>>9)+1)<<27)>>27];
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23);
  
  GWThi1 = FMWTselHi[analogControls[4]>>9];
  GWThi2 = FMWTselHi[(((analogControls[4]>>9)+1)<<27)>>27];
  GremHi = (uint32_t)((uint32_t)((analogControls[4]<<23))>>23);
  
  break;
  case 2:  
  GWTlo1 = FMAltWTselLo[analogControls[8]>>9];
  GWTlo2 = FMAltWTselLo[(((analogControls[8]>>9)+1)<<27)>>27];
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23);
  
  GWTmid1 = FMAltWTselMid[analogControls[5]>>9];
  GWTmid2 = FMAltWTselMid[(((analogControls[5]>>9)+1)<<27)>>27];
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23); 
  break;
  
  case 1:  
  GWTlo1 = CZWTselLo[analogControls[8]>>9];
  GWTlo2 = CZWTselLo[(((analogControls[8]>>9)+1)<<27)>>27];
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23);
  
  GWTmid1 = CZWTselMid[analogControls[5]>>9];
  GWTmid2 = CZWTselMid[(((analogControls[5]>>9)+1)<<27)>>27]; 
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23);
  
  GWThi1 = CZWTselHi[analogControls[4]>>9];
  GWThi2 = CZWTselHi[(((analogControls[4]>>9)+1)<<27)>>27];
  GremHi = (uint32_t)((uint32_t)((analogControls[4]<<23))>>23);
  
  break;
   case 3:  
  GWTlo1 = CZAltWTselLo[analogControls[8]>>9];
  GWTlo2 = CZAltWTselLo[(((analogControls[8]>>9)+1)<<27)>>27];
  GremLo = (uint32_t)((uint32_t)((analogControls[8]<<23))>>23);
  
  GWTmid1 = CZAltWTselMid[analogControls[5]>>9];
  GWTmid2 = CZAltWTselMid[(((analogControls[5]>>9)+1)<<27)>>27];
  GremMid = (uint32_t)((uint32_t)((analogControls[5]<<23))>>23);
  
 
  
  break;
  }
}
