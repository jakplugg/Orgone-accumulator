void WRITE2EEPROM() { //only write if it is different
  if (FX != EEPROM.read(0))EEPROM.write(0, FX);
  if (IsHW2) {
    if (EffectEnOn_A != EEPROM.read(1))EEPROM.write(1, EffectEnOn_A);
    if (EffectEnOn_B != EEPROM.read(2))EEPROM.write(2, EffectEnOn_B);
    if (EffectEnOn_C != EEPROM.read(3))EEPROM.write(3, EffectEnOn_C);
    if (xModeOn != EEPROM.read(4))EEPROM.write(4, xModeOn);
    if (FMmodeOn != EEPROM.read(5))EEPROM.write(5, FMmodeOn);
    if (FMFixedOn != EEPROM.read(6))EEPROM.write(6, FMFixedOn);
    if (roundrobinOn != EEPROM.read(7))EEPROM.write(7, roundrobinOn);
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
        digitalWriteFast(LED_roundrobin, tuneLockOn);
        
      }
    }
    else {
      if (roundrobinOn != buh) {
        roundrobinOn = buh;
        digitalWriteFast(LED_roundrobin, roundrobinOn);
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
        roundrobinOn = ! roundrobinOn;
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
  

  
    switch (FX) {
      case 0:
        outUpdateTimer.end();
        o3[0].phaseOffset = o1[0].phaseOffset = 0;
        outUpdateTimer.begin(outUpdateISR_DRUM_FM, ISRrate);
        declick = 256;

        break;
      case 1:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM_DEL, ISRrate);
        declick = 256;

        break;
      case 2:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        declick = 32;
        break;
      case 3:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        declick = 32;
        break;
      case 4:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        declick = 32;
        break;
      case 5:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
        declick = 32;
        break;
      case 6:
        outUpdateTimer.end();
        outUpdateTimer.begin(outUpdateISR_DRUM, ISRrate);
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


