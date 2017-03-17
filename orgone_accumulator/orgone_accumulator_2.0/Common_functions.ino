void WRITE2EEPROM() { //only write if it is different
  if (FX != EEPROM.read(0))EEPROM.write(0, FX);
  if (IsHW2) {
    if (EffectEnOn_A != EEPROM.read(1))EEPROM.write(1, EffectEnOn_A);
    if (EffectEnOn_B != EEPROM.read(2))EEPROM.write(2, EffectEnOn_B);
    if (EffectEnOn_C != EEPROM.read(3))EEPROM.write(3, EffectEnOn_C);
    if (xModeOn != EEPROM.read(4))EEPROM.write(4, xModeOn);
    if (FMmodeOn != EEPROM.read(5))EEPROM.write(5, FMmodeOn);
    if (FMFixedOn != EEPROM.read(6))EEPROM.write(6, FMFixedOn);
    if (pulsarOn != EEPROM.read(7))EEPROM.write(7, pulsarOn);
  }
}

void ARMED_FX() {
  if (effectEnButton_A.update()) {
    if (effectEnButton_A.fallingEdge()) {
      FX = 0;
      SELECT_ISRS();      
    }
  }
  if (pulsarButton.update()) {
    if (pulsarButton.fallingEdge()) {
      FX = 1;

      SELECT_ISRS();
    }
  }
  if (effectEnButton_B.update()) {
    if (effectEnButton_B.fallingEdge()) {
      FX = 2;

      SELECT_ISRS();
    }
  }
  if (FXCycleButton.update()) {
    if (FXCycleButton.fallingEdge()) {
      FX = 3;
      SELECT_ISRS();
    }
  }
  if (effectEnButton_C.update()) {
    if (effectEnButton_C.fallingEdge()) {
      FX = 4;
      SELECT_ISRS();
    }
  }
  if (xModeButton.update()) {
    if (xModeButton.fallingEdge()) {
      FX = 5;
      SELECT_ISRS();
    }
  }
  if (FMmodeButton.update()) {
    if (FMmodeButton.fallingEdge()) {
      FX = 6;
      SELECT_ISRS();
    }
  }
  if (FMFixedButton.update()) {
    if (FMFixedButton.fallingEdge()) {
      FX = 7;
      SELECT_ISRS();
    }
  }
}



void READ_POTS() {

  if (IsHW2 == 0) {
     analogControls[8] = analogRead(potPinTable_DIY[8]);
    analogControls[ARC] = analogRead(potPinTable_DIY[ARC]);
    analogControls[5] = analogRead(potPinTable_DIY[5]);
    analogControls[4] = analogRead(potPinTable_DIY[4]);
  }//step through control knob readings one per cycle, humans are slow
  else
  {
    analogControls[8] = analogRead(potPinTable_ret[8]);
    analogControls[ARC] = analogRead(potPinTable_ret[ARC]);
    analogControls[5] = analogRead(potPinTable_ret[5]);
    analogControls[4] = analogRead(potPinTable_ret[4]);
  }
}


void TUNELOCK_TOGGLE()
{
  if (IsHW2 == 0) {

    buh = digitalReadFast(tuneLockSwitch);
    if (TUNELOCK_SWITCH == 0) {
      if (tuneLockOn != buh) {
        tuneLockOn = buh;
        digitalWriteFast(LED_TuneLock, tuneLockOn);
        
      }
    }
    else {
      if (pulsarOn != buh) {
        pulsarOn = buh;
        digitalWriteFast(LED_TuneLock, pulsarOn);
        SELECT_ISRS();
      }
    }
  }

  else {
    if (tuneLockButton.update()) {
      if (tuneLockButton.fallingEdge()) {
        tuneLockOn = !tuneLockOn;

      }
    }
  }

}

void FX_TOGGLES() {
  if (IsHW2 == 0) {
    EffectEnOn_A = digitalReadFast(effectSwitch_A);
    EffectEnOn_B = !digitalReadFast(effectSwitch_B);
    EffectEnOn_C = !digitalReadFast(effectSwitch_C);
  }
  else if (FXSelArmed[0] == 0) {

    if (effectEnButton_A.update()) {
      if (effectEnButton_A.fallingEdge()) {
        EffectEnOn_A = !EffectEnOn_A;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (effectEnButton_B.update()) {
      if (effectEnButton_B.fallingEdge()) {
        EffectEnOn_B = !EffectEnOn_B;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (effectEnButton_C.update()) {
      if (effectEnButton_C.fallingEdge()) {
        EffectEnOn_C = !EffectEnOn_C;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (pulsarButton.update()) {
      if (pulsarButton.fallingEdge()) {
        pulsarOn = ! pulsarOn;
        QUIET_MCD = QUIET_MST;
        SELECT_ISRS();
      }
    }

  }
}

void OSC_MODE_TOGGLES() {
  if (IsHW2 == 0) {
    FMFixedOn = digitalReadFast(FMFixedSwitch);
    xModeOn = !(digitalReadFast(xModeSwitch));
    FMmodeOn = !(digitalReadFast(FMmodeSwitch));
  }

  else if (FXSelArmed[0] == 0) {
    if (FMFixedButton.update()) {
      if (FMFixedButton.fallingEdge()) {
        FMFixedOn = !FMFixedOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (FMmodeButton.update()) {
      if (FMmodeButton.fallingEdge()) {
        FMmodeOn = !FMmodeOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    if (xModeButton.update()) {
      if (xModeButton.fallingEdge()) {
        xModeOn = !xModeOn;
        QUIET_MCD = QUIET_MST;
      }
    }

    
  }
  oscMode = ((xModeOn) << 1) + (!FMmodeOn);
}

void SELECT_ISRS() {

  if (IsHW2 == 0) {
    LED_MCD = LED_MST;
  }

  FXSelArmed[0] = 0;
  FXchangedSAVE = 1;
  chord[0] = chord[1] = chord[2] = chord[3] = 1.0;
  detune[0] = detune[1] = detune[2] = detune[3] = 0;

  if (!pulsarOn) {
    switch (FX) {
      case 0:
        outUpdateTimer.end();
        o3.phaseOffset = o1.phaseOffset = 0;
        outUpdateTimer.begin(outUpdateISR_MAIN, ISRrate);
        declick = 32;

        break;
      case 1:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_WAVE_TWIN, ISRrate);
        declick = 32;

        break;
      case 2:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DISTS, ISRrate);
        declick = 32;
        break;
      case 3:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DISTS, ISRrate);
        declick = 32;
        break;
      case 4:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_MAIN, ISRrate);
        declick = 32;
        break;
      case 5:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_SPECTRUM, ISRrate);
        declick = 32;
        break;
      case 6:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_WAVE_DELAY, ISRrate);
        declick = 32;
        break;
      case 7:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        declick = 511;
        break;
    }
  }
  else
    switch (FX) {
      case 0:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_CHORD, ISRrate);
        declick = 32;
        break;
      case 1:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_TWIN, ISRrate);
        declick = 32;
        break;
      case 2:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_DISTS, ISRrate);
        declick = 32;
        break;
      case 3:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_DISTS, ISRrate);
        declick = 32;
        break;
      case 4:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_CHORD, ISRrate);//under isr detune
        declick = 32;
        break;
      case 5:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_SPECTRUM, ISRrate);
        declick = 32;
        break;
      case 6:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_PULSAR_DELAY, ISRrate);
        declick = 32;
        break;
      case 7:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        declick = 511;
        break;


    }

}


void GRADUALWAVE_D() {
 GremLo = (uint32_t)(map((analogControls[8]%546),0,545,0,511)); //get remainder for mix amount
 GremHi = (uint32_t)(map((analogControls[4]%546),0,545,0,511));
      GWTlo1 = drumWT[analogControls[8]/ 546];
      GWTlo2 = drumWT[((analogControls[8]/ 546) + 1)];      

      GWThi1 = drumWT2[analogControls[4]/ 546];
      GWThi2 = drumWT2[((analogControls[4]/ 546) + 1)];   
}


void FASTRUN GRADUALWAVE() {
//run declick if control moves fast (e-g sequencer) and that wave is being used.
if ((mixLo > 256) && ((max(analogControls[8],LoOld)- min(analogControls[8],LoOld)) > smooth_declick_threshold))declick_ready = 1;
if ((mixMid > 256) && ((max(analogControls[5],MidOld)- min(analogControls[5],MidOld)) > smooth_declick_threshold))declick_ready = 1;
if ((mixHi > 256) && ((max(analogControls[4],HiOld)- min(analogControls[4],HiOld)) > smooth_declick_threshold))declick_ready = 1;

//histCount ++;
//if (histCount >= histMax) histCount = 0;
//
//  Lo_accumulator = Lo_accumulator - Lo_wave_hist[histCount];
//  Mid_accumulator = Mid_accumulator - Mid_wave_hist[histCount];
//  Hi_accumulator = Hi_accumulator - Hi_wave_hist[histCount];
//  
//  Lo_wave_hist[histCount] = analogControls[8];
//  Mid_wave_hist[histCount] = analogControls[5];
//  Hi_wave_hist[histCount] = analogControls[4];
//  
//  Lo_accumulator = Lo_accumulator + Lo_wave_hist[histCount];
//  Mid_accumulator = Mid_accumulator + Mid_wave_hist[histCount];
//  Hi_accumulator = Hi_accumulator + Hi_wave_hist[histCount];
 
 LoOld = analogControls[8];
 MidOld = analogControls[5];
 HiOld = analogControls[4];


 uGremLo = (LoOld & 0x03FF);//mask off unwanted bits, power of 2 modulo.
 uGremMid = (MidOld & 0x03FF);
 uGremHi = (HiOld & 0x03FF);

 GremLo = (abs (int32_t(511-(uGremLo))));     // make triangle wave from pot remainder
 GremMid = (abs (int32_t(511-(uGremMid)))); 
 GremHi = (abs (int32_t(511-(uGremHi)))); 

  uint16_t divLo = (LoOld>>10)<<1;  
  uint16_t divLo2 = smoothStepTable[LoOld>>9];
  uint16_t divMid =(MidOld>>10)<<1;
  uint16_t divMid2 =smoothStepTable[MidOld>>9];
  uint16_t divHi = (HiOld>>10)<<1;
  uint16_t divHi2 = smoothStepTable[HiOld>>9]; 
 
  
  switch (oscMode) {
    case 0:    
      GWTlo1 = FMWTselLo[divLo]; //select "from" wave /546 gives 15 steps
      GWTlo2 = FMWTselLo[divLo2]; //select "to"        

      GWTmid1 = FMWTselMid[divMid];
      GWTmid2 = FMWTselMid[divMid2];      

      GWThi1 = FMWTselHi[divHi];
      GWThi2 = FMWTselHi[divHi2];            
      break;
      
    case 2:
      GWTlo1 = FMAltWTselLo[divLo];
      GWTlo2 = FMAltWTselLo[divLo2];      

      GWTmid1 = FMAltWTselMid[divMid];
      GWTmid2 = FMAltWTselMid[divMid2];      
      break;

    case 1:
      GWTlo1 = CZWTselLo[divLo];
      GWTlo2 = CZWTselLo[divLo2];      

      GWTmid1 = CZWTselMid[divMid];
      GWTmid2 = CZWTselMid[divMid2];     

      GWThi1 = CZWTselHi[divHi];
      GWThi2 = CZWTselHi[divHi2];     

      break;
    case 3:
      GWTlo1 = CZAltWTselLo[divLo];
      GWTlo2 = CZAltWTselLo[divLo2];
      
      GWTmid1 = CZAltWTselMid[divMid];
      GWTmid2 = CZAltWTselMid[divMid2];
      

      break;
  }
}



