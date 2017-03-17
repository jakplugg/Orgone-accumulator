void UPDATE_POSITION_LEDS() {

  if (LED_MCD == 0)  {
    switch (ARC + 1) {
      case 1:
        analogWrite(LED_Lo, (mixLo << 5) - conf_LED_comp);
        break;
      case 2:
        analogWrite(LED_Mid, (mixMid << 5) - conf_LED_comp);
        break;
      case 3:
        analogWrite(LED_Hi, (mixHi << 5) - conf_LED_comp);
        break;
    }
  }

  else {
    if (IsHW2 == 0) {
      switch (ARC + 1) {
        case 1:
          analogWrite(LED_Lo, (bitRead(FX, 2) * 64000));
          break;
        case 2:
          analogWrite(LED_Mid, (bitRead(FX, 1) * 64000));
          break;
        case 3:
          analogWrite(LED_Hi, (bitRead(FX, 0) * 64000));
          break;

      }
    }
  }
}

void OFF_prog_LEDS() {
  digitalWriteFast(SEL_LED_ARRAY[0], LOW);
  //pinMode(LED_pulsarON, INPUT); 
  digitalWriteFast(SEL_LED_ARRAY[1], LOW);
  digitalWriteFast(SEL_LED_ARRAY[2], LOW);
  digitalWriteFast(SEL_LED_ARRAY[3], HIGH); //this LED is inverted because pin33 can not be grounded on boot.
  digitalWriteFast(SEL_LED_ARRAY[4], LOW);
  digitalWriteFast(SEL_LED_ARRAY[5], LOW);
  digitalWriteFast(SEL_LED_ARRAY[6], LOW);
  digitalWriteFast(SEL_LED_ARRAY[7], LOW);
}


void UPDATE_prog_LEDS() {
  if (LED_MCD > 0) {
    switch (ARC + 1) {
      case 4:
        OFF_prog_LEDS();
        break;
      case 5:
        uint8_t microByte = pcounterOld >> 7;
        if (bitRead(microByte, (1 - (FX >> 3)))) {
          if (FX == 3) digitalWriteFast(SEL_LED_ARRAY[FX], LOW);
                    
          else  {
          //if (FX == 1) {pinMode(LED_pulsarON, OUTPUT);} 
          digitalWriteFast(SEL_LED_ARRAY[FX], HIGH);}
        }
        break;

    }
  }

  else {
    
    digitalWriteFast(LED_FXSelUp, !gateState);  

    
    switch (ARC + 1) {
      case 1:
        if(TUNELOCK_SWITCH == 0 || IsHW2)digitalWriteFast(LED_TuneLock, tuneLockOn); //hardware2 has separate button
        else digitalWriteFast(LED_TuneLock, pulsarOn ^ gateState);
        break;
      case 2:
        digitalWriteFast(LED_LoSel, EffectEnOn_A);
        break;
      case 3:
        digitalWriteFast(LED_MidSel, EffectEnOn_B);
        break;
      case 4:
        digitalWriteFast(LED_HiSel, EffectEnOn_C);
        break;
      case 5:
        digitalWriteFast(LED_FixSel, FMFixedOn);
        break;
      case 6:
        digitalWriteFast(LED_CZSel, FMmodeOn);
        break;
      case 7:
        digitalWriteFast(LED_xSel, xModeOn);
        break;
      case 8:        
        break;
      case 9:
      digitalWriteFast(LED_pulsarON, pulsarOn);
        break;

    }
  }
}


