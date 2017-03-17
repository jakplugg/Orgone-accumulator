void DODETUNING() {

  //Serial.println(oscMode);


  pcounter = millis() - pcounterOld;//used for LED flash
  pcounterOld = millis();

  
  switch (FX) {
    default: //symetrical detune - primes (bipolar)
      mixEffectUp = mixEffect * 0.77;
      mixEffectDn =  (2047 - mixEffect) * 0.97;
       fixedWave = 1;

      bipolarFX = (constrain((((4095 - aInEffectReading ) << 1) + (analogControls[2] - 4095)), -4095, 4095));
      aInModEffectCubing = bipolarFX / 64.0;
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing) / 8.0;
      if (bipolarFX > 0) {
        detune[0] = (int32_t)((effectScaler / 65536.0) * (inputConverter[rr]));        
      }
      else {
        effectScaler = effectScaler * mixEffect;
        detune[0] = ((int32_t)((effectScaler * primes[1]) / 10000.0)) ;       
      }
      break;

//    case 1: //twin
//
//      mixEffectUp = mixEffect * 0.77;
//      mixEffectDn =  (2047 - mixEffect) * 0.97;
//      GRADUALWAVE();      
//      fixedWave = 0;
//
//      o1[rr].phaseOffset = (uint32_t)( constrain(((4095 - aInEffectReading) + (analogControls[2])), 0, 8190)) << 20; //difference between the waves.
//      //o1.phaseOffset = (map(o1.phaseOffset,0,8190,7000,100))<<20;
//      o1[rr].amp = 0;//turn off folding, using same ISR
//      detune[0] = 0; //while in wavetwin dont want detuning
//      break;
//
//    case 2: //crush/fold distortions 1 (bipolar)
//      mixEffectUp = mixEffect * 0.97;
//      mixEffectDn =  (2047 - mixEffect) * 0.97;
//
//      bipolarFX = (constrain((((4095 - aInEffectReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));
//      if (bipolarFX > 0) {
//        o1[rr].amp = bipolarFX;
//        FXMixer[0] = mixEffect;
//        FXMixer[1] = 0;
//        FXMixer[2] = 0;
//        FXMixer[3] = 0;
//      }
//      else {
//        monopoleFX = (uint32_t)(abs(bipolarFX) << 1);
//        o1[rr].amp = 0;
//        FXMixer[0] = 0;
//        FXMixer[1] = mixEffect;
//        FXMixer[2] = 0;
//        FXMixer[3] = 0;
//        CRUSHBITS = (monopoleFX >> 10) + 8; //
//        CRUSH_Remain = (monopoleFX << 22) >> 22;
//      } //remainder used for mixing crush levels
//      GRADUALWAVE();
//       fixedWave = 0;
//
//      break;
//
//
//
//    case 3: //Distortions2 (bipolar)
//
//      mixEffectUp = mixEffect * 0.97;
//      mixEffectDn =  (2047 - mixEffect) * 0.97;
//
//      bipolarFX = (constrain((((4095 - aInEffectReading ) << 1) + (analogControls[2] - 4095)), -4095, 4095));
//      if (bipolarFX > 0) {
//        o1[rr].amp = bipolarFX;
//        FXMixer[0] = 0;
//        FXMixer[1] = 0;
//        FXMixer[2] = mixEffect;
//        FXMixer[3] = 0;
//      }
//      else {
//        monopoleFX = (uint32_t)(abs(bipolarFX) << 1);
//        o1[rr].amp = monopoleFX;
//        FXMixer[0] = 0;
//        FXMixer[1] = 0;
//        FXMixer[2] = 0;
//        FXMixer[3] = mixEffect;
//      }
//      GRADUALWAVE();
//       fixedWave = 0;
//
//    case 4: //chord allready bipolar
//     fixedWave = 1;
//      mixEffectUp = mixEffect * 0.87;
//      mixEffectDn =  (2047 - mixEffect) * 0.97;
//
//      chordArrayOffset = ((constrain(((4095 - aInEffectReading) + (analogControls[2])), 0, 8190)) >> 10) * 3;
//     
//      break;
//
//    case 5: //spectrum bipolar
//     fixedWave = 1;
//      mixEffectUp = mixEffect * 0.77;
//      mixEffectDn =  (2047 - mixEffect) * 0.97;
//
//      bipolarFX = (constrain((((4095 - aInEffectReading ) << 1) + (analogControls[2] - 4095)), -4095, 4095));
//      aInModEffectCubing = bipolarFX / 64.0;
//      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing) / 5000.0;
//      if (bipolarFX > 0) {
//        FXMixer[0] = 0;
//        effectScaler = (float)((effectScaler * mixEffect) / 4095.0);
//
//       
//      
//      }
//      else {
//        if (pulsarOn) {
//          FXMixer[1] = abs(bipolarFX) * mixEffect >> 9;
//          FXMixer[0] = 0;
//        }
//        else {
//          FXMixer[0] = abs(bipolarFX) * mixEffect >> 9;
//          FXMixer[1] = 0;
//        }
//        effectScaler = 0;
//        detune[0] = detune[1] = detune[2] = detune[3] = 1;
//      }
//
//      Lbuh = (analogControls[8] >> 9) * 9;
//      Mbuh =  (analogControls[5] >> 9) * 9;
//      Hbuh =  (analogControls[4] >> 9) * 9;
//      break;
//
//    case 6: //delay (bipolar)
//
//      mixEffectUp = mixEffect * 0.97;
//      mixEffectDn =  (2047 - mixEffect) * 0.97;
//
//      GRADUALWAVE();
//       fixedWave = 0;
//      o3[rr].phaseOffset = (uint32_t)(analogControls[8]) << 20;
//      delayTime = constrain(((averageaInRAv - 4065) + averageratio), 8, 8190); //For Feedback altFX ratio knob
//      delayFeedback = (int32_t)((analogControls[2] >> 1) - 2048) + (int32_t)((4095 - aInEffectReading) >> 1); //detune become feedback
//      delayFeedback = constrain(delayFeedback, -2046, 2046);
//      break;
//
    case 7: //drum voice
       fixedWave = 1;
      mixEffectUp = mixEffect * 0.787; 
      mixEffectDn =  (2047 - mixEffect) * 0.97;
      delayFB0[rr] = analogControls[4] >> 2;
      o4[rr].phase_increment =  ((int32_t)(inputConverter[rr])) >> 10; //borrow this for pitch>hold time      
      if (IsHW2) {
        floats[0] = (float)((constrain(((4095 - aInModIndex ) + (analogControls[1])), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
        o1[rr].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
        twang[rr].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        twang[rr].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        if (pulsarOn) {
          twang[rr].dB = 2;
        }
        else  {
          twang[rr].dB = 0;
        }
        if (xModeOn) {
          twang[rr].d2B = 2 ;
        }
        else {
          twang[rr].d2B = 0;
        }
      }
      else

      {
        if (!pulsarOn) {
          floats[0] = (float)((constrain(((4095 - aInModIndex ) + analogControls[1]), 0.0, 8191.0)) / 8192.0); //make a log pot of index.
          twang[rr].d = map(( analogControls[5]), 1, 8191, 24000, 24); //decaY 1
        }
        else {
          floats[0] = (float)(analogControls[1] / 8192.0);
          twang[rr].d = map((constrain(((4095 - aInModIndex)  + analogControls[5]), 0, 8191)), 1, 8191, 24000, 24); //decay 2
        }
        if (!xModeOn) {
          o1[rr].amp = (constrain(((AInRawFilter - 4095) + analogControls[0]), 0, 8191)) >> 3; //amount of pbend on fm freq pot
          twang[rr].d2 = map( analogControls[3], 1, 8191, 32000, 24); //decay 2
        }
        else { //swap CVs with x button (hw0)
          o1[rr].amp = analogControls[0] >> 3;
          twang[rr].d2 = map((constrain(((AInRawFilter - 4095) + analogControls[3]), 0, 8191)), 1, 8191, 32000, 24); //decaY 1
        }
        twang[rr].dB = 2;
        twang[rr].d2B = 2;
      }


      floats[0] =  (floats[0] * floats[0] * floats[0]) * 524288.0;
      o6[rr].phase_increment = ((int32_t)floats[0]) >> 5; //the amount of xmod

      twang[rr].a = EffectEnOn_B * (analogControls[5] << 10); //drum hold time

      if (EffectEnOn_A) twang[rr].d = twang[rr].d + (o1[rr].phase_increment >> 12);
      twang[rr].d = signed_multiply_32x16t((twang[rr].d * twang[rr].d), twang[rr].d << 13) + (32 << 10);

      twang[rr].d2 = signed_multiply_32x16t((twang[rr].d2 * twang[rr].d2), twang[rr].d2 << 12) + (32 << 10);

      bipolarFX = (constrain((((4095 - aInEffectReading) << 1) + (analogControls[2] - 4095)), -4095, 4095));//detune amounts
      aInModEffectCubing = (float)((abs(bipolarFX) / 9000.0));
      effectScaler = (aInModEffectCubing * aInModEffectCubing * aInModEffectCubing);
      //effectScaler = 0;

      
      break;
  }
}







