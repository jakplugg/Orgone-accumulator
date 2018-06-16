void DODETUNING() {


  pcounter = millis() - pcounterOld;//used for LED flash
  pcounterOld = millis();

  
  switch (FX) {
    case 0: //symetrical detune - primes (bipolar)
      mixEffectUp = mixEffect * 0.77;
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      bipolarFX = (constrain((((4095 - aInEffectReading ) << 1) + (analogControls[2] - 4095)), -4095, 4095));
      aInModEffectCubing = bipolarFX / 64.0;
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing) / 8.0;
      if (bipolarFX > 0) {
        detune[1] = (int32_t)((effectScaler / 32768.0) * (inputConverter));
        detune[2] = - detune[1];
        detune[3] = (int32_t)((effectScaler / 16384.0) * (inputConverter)) ;
        detune[0] = - detune[3];
      }
      else {
        effectScaler = effectScaler * mixEffect;
        detune[0] = (int32_t)((effectScaler * primes[0]) / 100000.0) ;
        detune[1] = -(int32_t)((effectScaler * primes[1]) / 100000.0) ;
        detune[2] = (int32_t)((effectScaler * primes[2]) / 100000.0) ;
        detune[3] = -(int32_t)((effectScaler * primes[3]) / 100000.0) ;
      }
      break;

    case 1: //twin

      mixEffectUp = mixEffect * 0.77;
      mixEffectDn =  (2047 - mixEffect) * 0.97;
      GRADUALWAVE();

      o1.phaseOffset = (uint32_t)( constrain(((4095 - aInEffectReading) + (analogControls[2])), 0, 8190)) << 20; //difference between the waves.
      //o1.phaseOffset = (map(o1.phaseOffset,0,8190,7000,100))<<20;
      o1.amp = 0;//turn off folding, using same ISR
      detune[0] = 0; //while in wavetwin dont want detuning
      break;

    case 2: //crush/fold distortions 1 (bipolar)
      mixEffectUp = mixEffect * 0.97;
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      bipolarFX = (constrain((((4095 - aInEffectReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));
      if (bipolarFX > 0) {
        o1.amp = bipolarFX;
        FXMixer[0] = mixEffect;
        FXMixer[1] = 0;
        FXMixer[2] = 0;
        FXMixer[3] = 0;
      }
      else {
        monopoleFX = (uint32_t)(abs(bipolarFX) << 1);
        o1.amp = 0;
        FXMixer[0] = 0;
        FXMixer[1] = mixEffect;
        FXMixer[2] = 0;
        FXMixer[3] = 0;
        CRUSHBITS = (monopoleFX >> 10) + 8; //
        CRUSH_Remain = (monopoleFX << 22) >> 22;
      } //remainder used for mixing crush levels
      GRADUALWAVE();

      break;



    case 3: //Distortions2 (bipolar)

      mixEffectUp = mixEffect * 0.97;
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      bipolarFX = (constrain((((4095 - aInEffectReading ) << 1) + (analogControls[2] - 4095)), -4095, 4095));
      if (bipolarFX > 0) {
        o1.amp = bipolarFX;
        FXMixer[0] = 0;
        FXMixer[1] = 0;
        FXMixer[2] = mixEffect;
        FXMixer[3] = 0;
      }
      else {
        monopoleFX = (uint32_t)(abs(bipolarFX) << 1);
        o1.amp = monopoleFX;
        FXMixer[0] = 0;
        FXMixer[1] = 0;
        FXMixer[2] = 0;
        FXMixer[3] = mixEffect;
      }
      GRADUALWAVE();

    case 4: //chord allready bipolar
      mixEffectUp = mixEffect * 0.87;
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      chordArrayOffset = ((constrain(((4095 - aInEffectReading) + (analogControls[2])), 0, 8190)) >> 10) * 3;
      for (int i = 0; i <= 3; i++) {
        chord[i] = (equalTemprementTable[chordTable[i + chordArrayOffset]]);
      }
      break;

    case 5: //spectrum bipolar
      mixEffectUp = mixEffect * 0.77;
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      bipolarFX = (constrain((((4095 - aInEffectReading ) << 1) + (analogControls[2] - 4095)), -4095, 4095));
      aInModEffectCubing = bipolarFX / 64.0;
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing) / 5000.0;
      if (bipolarFX > 0) {
        FXMixer[0] = 0;
        effectScaler = (float)((effectScaler * mixEffect) / 4095.0);

        chord[0] = (float)(1.0 + ((effectScaler * primes[0]) / 1000000.0)) ;
        chord[1] = (float)(1.0 + ((effectScaler * primes[1]) / 1000000.0)) ;
        chord[2] = (float)(1.0 + ((effectScaler * primes[2]) / 1000000.0)) ;
        chord[3] = (float)(1.0 + ((effectScaler * primes[3]) / 1000000.0));
      }
      else {
        if (pulsarOn) {
          FXMixer[1] = abs(bipolarFX) * mixEffect >> 9;
          FXMixer[0] = 0;
        }
        else {
          FXMixer[0] = abs(bipolarFX) * mixEffect >> 9;
          FXMixer[1] = 0;
        }
        effectScaler = 0;
        detune[0] = detune[1] = detune[2] = detune[3] = 1;
      }

      Lbuh = (analogControls[8] >> 9) * 9;
      Mbuh =  (analogControls[5] >> 9) * 9;
      Hbuh =  (analogControls[4] >> 9) * 9;
      break;

    case 6: //delay (bipolar)

      mixEffectUp = mixEffect * 0.97;
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      GRADUALWAVE();
      o3.phaseOffset = (uint32_t)(analogControls[8]) << 20;
      delayTime = constrain(((averageaInRAv - 4065) + averageratio), 8, 8190); //For Feedback altFX ratio knob
      delayFeedback = (int32_t)((analogControls[2] >> 1) - 2048) + (int32_t)((4095 - aInEffectReading) >> 1); //detune become feedback
      delayFeedback = constrain(delayFeedback, -2046, 2046);
      break;

    case 7: //drum voice
      GRADUALWAVE_D();
      mixEffectUp = mixEffect * 0.787; //because there are 5 oscillators being mixed in the detune mix of ISR
      mixEffectDn =  (2047 - mixEffect) * 0.97;

      o8.phase_increment =  ((int32_t)(inputConverter)) >> 10; //borrow this for pitch>hold time

      if (IsHW2) {
        floats[0] = (float)((constrain(((4095 - aInModIndex ) + (analogControls[1])), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
        o1.amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
        drum_d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        drum_d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        if (pulsarOn) {
          drum_dB = 2;
        }
        else  {
          drum_dB = 0;
        }
        if (xModeOn) {
          drum_d2B = 2 ;
        }
        else {
          drum_d2B = 0;
        }
      }
      else

      {
        if (!pulsarOn) {
          floats[0] = (float)((constrain(((4095 - aInModIndex ) + analogControls[1]), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
          drum_d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        }
        else {
          floats[0] = (float)(analogControls[1] / 8192.0);
          drum_d = map((constrain(((4095 - aInModIndex)  + analogControls[5]), 0, 8191)), 1, 8191, 24000, 24); //decay 2
        }
        if (!xModeOn) {
          o1.amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
          drum_d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        }
        else { //swap CVs with x button (hw0)
          o1.amp = analogControls[0] >> 3;
          drum_d2 = map((constrain(((AInRawFilter - 4095) + analogControls[3]), 0, 8191)), 1, 8191, 32000, 24); //decaY 1
        }
        drum_dB = 0;
        drum_d2B = 0;
      }


      floats[0] =  (floats[0] * floats[0] * floats[0]) * 524288.0;
      o6.phase_increment = ((int32_t)floats[0]) >> 5; //the amount of xmod

      drum_a = EffectEnOn_B * (analogControls[5] << 10); //drum hold time

      if (EffectEnOn_A) drum_d = drum_d + (o1.phase_increment >> 12);
      drum_d = signed_multiply_32x16t((drum_d * drum_d), drum_d << 13) + (32 << 10);

      drum_d2 = signed_multiply_32x16t((drum_d2 * drum_d2), drum_d2 << 12) + (32 << 10);

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







