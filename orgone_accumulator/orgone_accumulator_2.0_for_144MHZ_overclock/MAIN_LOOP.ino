void loop() {
  //histCount ++;
  //if(histCount >= histMax){histCount = 0;}
  
  if (loopReset == 1)goto evilGoto; //these will jump to the same place in the loop after a gateISR happens for better consistancy of retriggered events.

  if (LED_MCD > 0)LED_MCD = LED_MCD - 1;
  if (LED_MCD == 1){WRITE2EEPROM();FXSelArmed[0] = 0;}
  if (QUIET_MCD > 0)QUIET_MCD = QUIET_MCD - 1;
  if (QUIET_MCD == 1){WRITE2EEPROM();FXSelArmed[0] = 0;}

  
  //slow generated signals
  noiseTable2[random(0, 512)] = random(-32767, 32767); //hypnotoad noise (noiseTable2)

    
  if (loopReset == 1)goto evilGoto;
  SWC ++;
  fuh = analogControls[0] >> 6;
  if (SWC > fuh) {
    NT3Rate = (random(-7, 8)) - (noiseTable3[0] / 4198); //LF noise (noiseTable3)
    SWC = 0;
  }

  if (loopReset == 1)goto evilGoto;
  ARC ++;
  if ((ARC == 7 || ARC == 9) && tuneLockOn) ARC ++; //skip reading tuning knobs if tunelock is on.
  if (ARC > 9) {
    ARC = 0;
  }  //cycle through analog controls. skip tuning controls if tunelock is on.
  
  if (loopReset == 1)goto evilGoto;
  //--------------------------------------------------------
  inCVraw = (float)(analogRead(A0)); //main v/oct CV in. only use 13 bits of analog in SEPERATE AINS WITH CODE  
  //--------------------------------------------------------
  if (loopReset == 1)goto evilGoto;
  //______________TUNING OPTIONS  
  dtuner = (float)((((int)(analogControls[9]/227)) * (conf_NoteSize * tuneStep)) + ((int)(analogControls[7] / 28))); //coarse and fine tuning
  tuner = (float)(inCV + dtuner);
  //comment out above line and uncomment following line for analog style non stepped tuning
  //tuner = inCV+(analogControls[9]>>1)+(analogControls[7]>>4);
  //_____________END TUNINGOPTIONS


  if (loopReset == 1)goto evilGoto;
  inputScaler = float(tuner / octaveSize);
  if (loopReset == 1)goto evilGoto;

  //______________________________CONVERSION OPTIONS
  //digitalWriteFast (oSQout,0);//temp testing OC
  //inputVOct = powf(2.0,inputScaler); //uncomment for slightly more accurate v/oct conversion (but it is slower)
  inputVOct = fastpow2(inputScaler); //"real time" exponentiation of CV input! (powf is single precision float power function) comment out if using powf version above
  //digitalWriteFast (oSQout,1);//temp testing OC
  //______________________________END CONVERSION OPTIONS


  //inputVOct = sq(inputScaler);
  if (loopReset == 1)goto evilGoto;
  inputConverter = inputVOct * conf_TuneMult; //<-----------------------------number is MASTER TUNING also affected by ISR speed
  //divide by 2 if you want it play 1 octave lower, 4 for 2 octaves etc.
  //you can also fine tune it to just how you like it by tweaking the number up and down.

  if (loopReset == 1)goto evilGoto;
  //---------------------------------------------------------------------

  READ_POTS();

  //----------------------------------------------------------------------
  if (loopReset == 1)goto evilGoto;
  //running average filter of ratio CV and index CV they are sensetive to noise.
  totalaInRAv = totalaInRAv - readingsaInRAv[indexaInRAv];
  totalaInIAv = totalaInIAv - readingsaInIAv[indexaInRAv];
  totalInCV = totalInCV - readingsaInCV[indexInCV];

  readingsaInRAv[indexaInRAv] = AInRawFilter = (8191 - analogRead(A17)); //adjust numreadingsaInRAv on first page for filtering.
  readingsaInIAv[indexaInRAv] = aInModIndex;
  readingsaInCV[indexInCV] = inCVraw;

  totalaInRAv = totalaInRAv + readingsaInRAv[indexaInRAv];
  totalaInIAv = totalaInIAv + readingsaInIAv[indexaInRAv];
  totalInCV = totalInCV + readingsaInCV[indexInCV];


  indexaInRAv = indexaInRAv + 1;
  if (indexaInRAv >= numreadingsaInRAv) indexaInRAv = 0;
  indexInCV = indexInCV + 1;
  if (indexInCV >= numreadingsCV) indexInCV = 0;

  averageaInRAv = (totalaInRAv / numreadingsaInRAv);
  averageaInIAvCubing = (4095 - (totalaInIAv / numreadingsaInRAv)) / 512.0;
  averageaInIAv = totalaInIAv / numreadingsaInRAv;
  inCV = totalInCV / numreadingsCV;


evilGoto:


  //------------------------------Position CV---------------------
  aInPos = 4095 - ((analogRead(A16))) ;
  //------------------------------------------------------------------
  loopReset = 0;
  envVal = constrain((aInPos + mixPos), 0, 4095); //mix the position knob with the modulation from the CV input (fix for bipolar)

  mixMid = constrain((2047 - abs(envVal - 2047)), 0, 2047); //sets the level of the midpoint wave
  mixHi = constrain((((envVal)) - 2047), 0, 2047); //sets the level of the high wave
  mixLo = constrain((2047 - ((envVal))), 0, 2047); //sets the level of the low wave
  mixEffect = (mixLo * EffectEnOn_A) + (mixMid * EffectEnOn_B) + (mixHi * EffectEnOn_C);


  if (loopReset == 1)goto evilGoto;
  //---------------------------Detune CV----------------
  aInEffectReading = analogRead(A12);
  aInModEffect = ((4095 - aInEffectReading) << 1);
  //--------------------------------------------------

  DODETUNING();

 

  if (loopReset == 1)goto evilGoto;
  //---------------------------Index CV---------------------------------
  aInModIndex = analogRead(A15);
  //----------------------------------------------------------------------

   if (pulsarOn){
   switch (FX){
     
   case 5:
  ASSIGNINCREMENTS_SPECTRUM();//spectral
  break;  
  
  case 7:
  ASSIGNINCREMENTS_DRUM();//drum
  break;   
    
  default:
   ASSIGNINCREMENTS_P();
   }}

   
   else
   switch (FX){
     
  case 5:
  ASSIGNINCREMENTS_SPECTRUM();//spectral
  break;
  
  case 6:
  ASSIGNINCREMENTS_D();//delay
  break;
  
  case 7:
  ASSIGNINCREMENTS_DRUM();//drum
  break;
     
  default:
   ASSIGNINCREMENTS();
   }



  if (loopReset == 1)goto evilGoto;
  UPDATE_POSITION_LEDS();
  
  UPDATE_prog_LEDS();

  if (IsHW2) {
    
    
 if (FXSelArmed[0] == 0){  
    if (FXCycleButton.update()) {
      if (FXCycleButton.fallingEdge()) {
          FXSelArmed[0] = 1; //arm effect selection          
          LED_MCD = LED_MST;
      }
    }   
  }
  else ARMED_FX();

  }

  else {//DIY FX button cycle move
    if (FXCycleButton.update()) {
      if (tuneLockOn) {
        if (FXCycleButton.fallingEdge()) {
          FX = FX - 1;
          if (FX < 0) FX = FX_Count;         
          SELECT_ISRS();
        }
        if (FXSw == 1 && FXCycleButton.risingEdge()) {
          FX = FX - 1;
          if (FX < 0) FX = FX_Count;         
          SELECT_ISRS();
        }
      }


      else {
        if (FXCycleButton.fallingEdge()) {
          FX = FX + 1;
          if (FX > FX_Count) FX = 0;         
          SELECT_ISRS();
        }
        if (FXSw == 1 && FXCycleButton.risingEdge()) {
          FX = FX + 1;
          if (FX > FX_Count) FX = 0;         
          SELECT_ISRS();
        }
      }
    }
  }//end of DIY FX button cycle
  
  // ----------------------------------
  monitorSerialReception();
  if(requestForData) {
    requestForData = false;
    sendBroadcastPacket();
  }
    
//  if(monitorSerialReception) 
//  if(BROADCAST != 0) {  
//    static int pace = 0;
//    if (++pace > 20) {
//      pace = 0;
//      sendBroadcastPacket();
//    }
//  }
  // ----------------------------------



}







