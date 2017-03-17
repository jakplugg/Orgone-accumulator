void DODETUNING() {

  //Serial.println(oscMode);


  pcounter = millis() - pcounterOld;//used for LED flash
  pcounterOld = millis();

  
  switch (FX) {
    case 0: //------------------------------------------------fm drum
    GRADUALWAVE_D();
       fixedWave = 0;
      mixEffectUp = mixEffect * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      o8[drumNum].phase_increment =  ((int32_t)(inputConverter)) >> 10; //borrow this for pitch>hold time

      if (IsHW2) {
        floats[0] = (float)((constrain(((4095 - aInModIndex ) + (analogControls[1])), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
        o1[drumNum].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
        drum[drumNum].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        drum[drumNum].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        if (roundrobinOn) {
          drum[drumNum].dB = 2;
        }
        else  {
          drum[drumNum].dB = 0;
        }
        if (xModeOn) {
          drum[drumNum].d2B = 2 ;
        }
        else {
          drum[drumNum].d2B = 0;
        }
      }
      else

      {
        if (!roundrobinOn) {
          floats[0] = (float)((constrain(((4095 - aInModIndex ) + analogControls[1]), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
          drum[drumNum].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        }
        else {
          floats[0] = (float)(analogControls[1] / 8192.0);
          drum[drumNum].d = map((constrain(((4095 - aInModIndex)  + analogControls[5]), 0, 8191)), 1, 8191, 24000, 24); //decay 2
        }
        if (!xModeOn) {
          o1[drumNum].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
          drum[drumNum].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        }
        else { //swap CVs with x button (hw0)
          o1[drumNum].amp = analogControls[0] >> 3;
          drum[drumNum].d2 = map((constrain(((AInRawFilter - 4095) + analogControls[3]), 0, 8191)), 1, 8191, 32000, 24); //decaY 1
        }
        drum[drumNum].dB = 1;
        drum[drumNum].d2B = 1;
      }


      floats[0] =  (floats[0] * floats[0] * floats[0]) * 524288.0;
      o6[drumNum].phase_increment = ((int32_t)floats[0]) >> 5; //the amount of xmod

      drum[drumNum].a = EffectEnOn_B * (analogControls[5] << 10); //drum hold time

      if (EffectEnOn_A) drum[drumNum].d = drum[drumNum].d + (o1[drumNum].phase_increment >> 12);
      drum[drumNum].d = signed_multiply_32x16t((drum[drumNum].d * drum[drumNum].d), drum[drumNum].d << 13) + (32 << 10);

      drum[drumNum].d2 = signed_multiply_32x16t((drum[drumNum].d2 * drum[drumNum].d2), drum[drumNum].d2 << 12) + (32 << 10);

      bipolarFX = (constrain((((4095 - aInEffectReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));//detune amounts
      aInModEffectCubing = (float)((abs(bipolarFX) / 9000.0));
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing);
      //effectScaler = 0;
      chord[0] = ((effectScaler * primes[0]) + 1 );
      if (bipolarFX < 0) {
        o2[drumNum].amp = o6[drumNum].phase_increment;
      }
      else o2[drumNum].amp = 0;
        
        
       
    
      break;
      
      case 1: //delay drum
      GRADUALWAVE_D();
       fixedWave = 0;
      mixEffectUp = mixEffect * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixEffectDn =  (2047 - mixEffect) * 0.97;
      delayFB0[drumNum] = analogControls[4] >> 2;
      o8[drumNum].phase_increment =  ((int32_t)(inputConverter)) >> 10; //borrow this for pitch>hold time      
      if (IsHW2) {
        floats[0] = (float)((constrain(((4095 - aInModIndex ) + (analogControls[1])), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
        o1[drumNum].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
        drum[drumNum].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        drum[drumNum].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        if (roundrobinOn) {
          drum[drumNum].dB = 2;
        }
        else  {
          drum[drumNum].dB = 0;
        }
        if (xModeOn) {
          drum[drumNum].d2B = 2 ;
        }
        else {
          drum[drumNum].d2B = 0;
        }
      }
      else

      {
        if (!roundrobinOn) {
          floats[0] = (float)((constrain(((4095 - aInModIndex ) + analogControls[1]), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
          drum[drumNum].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        }
        else {
          floats[0] = (float)(analogControls[1] / 8192.0);
          drum[drumNum].d = map((constrain(((4095 - aInModIndex)  + analogControls[5]), 0, 8191)), 1, 8191, 24000, 24); //decay 2
        }
        if (!xModeOn) {
          o1[drumNum].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
          drum[drumNum].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        }
        else { //swap CVs with x button (hw0)
          o1[drumNum].amp = analogControls[0] >> 3;
          drum[drumNum].d2 = map((constrain(((AInRawFilter - 4095) + analogControls[3]), 0, 8191)), 1, 8191, 32000, 24); //decaY 1
        }
        drum[drumNum].dB = 2;
        drum[drumNum].d2B = 2;
      }


      floats[0] =  (floats[0] * floats[0] * floats[0]) * 524288.0;
      o6[drumNum].phase_increment = ((int32_t)floats[0]) >> 5; //the amount of xmod

      drum[drumNum].a = EffectEnOn_B * (analogControls[5] << 10); //drum hold time

      if (EffectEnOn_A) drum[drumNum].d = drum[drumNum].d + (o1[drumNum].phase_increment >> 12);
      drum[drumNum].d = signed_multiply_32x16t((drum[drumNum].d * drum[drumNum].d), drum[drumNum].d << 13) + (32 << 10);

      drum[drumNum].d2 = signed_multiply_32x16t((drum[drumNum].d2 * drum[drumNum].d2), drum[drumNum].d2 << 12) + (32 << 10);

      bipolarFX = (constrain((((4095 - aInEffectReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));//detune amounts
      aInModEffectCubing = (float)((abs(bipolarFX) / 9000.0));
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing);
      //effectScaler = 0;

      if (bipolarFX > 0) {
        chord[0] = ((effectScaler * primes[0]) + 1 );
        chord[1] = ((effectScaler * primes[1]) + 1 );
        chord[2] = ((effectScaler * primes[2]) + 1);
        chord[3] = ((effectScaler * primes[3]) + 1);
      }
      else {
        chord[0] = ((effectScaler * fibi[0] * 55.0) + 1);
        chord[1] = ((effectScaler * fibi[1] * 55.0) + 1 );
        chord[2] = ((effectScaler * fibi[2] * 55.0) + 1);
        chord[3] = ((effectScaler * fibi[3] * 55.0) + 1);
      }
      break;
//    case 2: 
//    case 3:     
//    case 4: 
//    case 6: 
    default: //drum voice
      GRADUALWAVE_D();
       fixedWave = 0;
      mixEffectUp = mixEffect * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      o8[drumNum].phase_increment =  ((int32_t)(inputConverter)) >> 10; //borrow this for pitch>hold time

      if (IsHW2) {
        floats[0] = (float)((constrain(((4095 - aInModIndex ) + (analogControls[1])), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
        o1[drumNum].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
        drum[drumNum].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        drum[drumNum].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        if (roundrobinOn) {
          drum[drumNum].dB = 2;
        }
        else  {
          drum[drumNum].dB = 0;
        }
        if (xModeOn) {
          drum[drumNum].d2B = 2 ;
        }
        else {
          drum[drumNum].d2B = 0;
        }
      }
      else

      {
        if (!roundrobinOn) {
          floats[0] = (float)((constrain(((4095 - aInModIndex ) + analogControls[1]), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
          drum[drumNum].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        }
        else {
          floats[0] = (float)(analogControls[1] / 8192.0);
          drum[drumNum].d = map((constrain(((4095 - aInModIndex)  + analogControls[5]), 0, 8191)), 1, 8191, 24000, 24); //decay 2
        }
        if (!xModeOn) {
          o1[drumNum].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
          drum[drumNum].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        }
        else { //swap CVs with x button (hw0)
          o1[drumNum].amp = analogControls[0] >> 3;
          drum[drumNum].d2 = map((constrain(((AInRawFilter - 4095) + analogControls[3]), 0, 8191)), 1, 8191, 32000, 24); //decaY 1
        }
        drum[drumNum].dB = 0;
        drum[drumNum].d2B = 0;
      }


      floats[0] =  (floats[0] * floats[0] * floats[0]) * 524288.0;
      o6[drumNum].phase_increment = ((int32_t)floats[0]) >> 5; //the amount of xmod

      drum[drumNum].a = EffectEnOn_B * (analogControls[5] << 10); //drum hold time

      if (EffectEnOn_A) drum[drumNum].d = drum[drumNum].d + (o1[drumNum].phase_increment >> 12);
      drum[drumNum].d = signed_multiply_32x16t((drum[drumNum].d * drum[drumNum].d), drum[drumNum].d << 13) + (32 << 10);

      drum[drumNum].d2 = signed_multiply_32x16t((drum[drumNum].d2 * drum[drumNum].d2), drum[drumNum].d2 << 12) + (32 << 10);

      bipolarFX = (constrain((((4095 - aInEffectReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));//detune amounts
      aInModEffectCubing = (float)((abs(bipolarFX) / 9000.0));
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing);
      //effectScaler = 0;

      if (bipolarFX > 0) {
        chord[0] = ((effectScaler * primes[0]) + 1 );
        chord[1] = ((effectScaler * primes[1]) + 1 );
        chord[2] = ((effectScaler * primes[2]) + 1);
        chord[3] = ((effectScaler * primes[3]) + 1);
      }
      else {
        chord[0] = ((effectScaler * fibi[0] * 55.0) + 1);
        chord[1] = ((effectScaler * fibi[1] * 55.0) + 1 );
        chord[2] = ((effectScaler * fibi[2] * 55.0) + 1);
        chord[3] = ((effectScaler * fibi[3] * 55.0) + 1);
      }
      break;
  }
}







