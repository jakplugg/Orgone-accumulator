void ASSIGNINCREMENTS_VSR() { //--------------------------------------------------------default

  CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047); 
  INCREMENT_PWM();

  
  analogWriteFrequency(LED_Lo, uint32_t(inputConverter)>>8);
  attachInterrupt(LED_Lo, outUpdateISR_DISTS, RISING); 
  
  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;
    case 0://break intentionally ommited

      UPDATECONTROLS_FM();


      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 2.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

      if (FMFixedOn) {
        avgcubing = (float)(averageratio / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        
        o1.phase_increment = osc_mult[0]  ;      
        o3.phase_increment = (inputConverterF   * osc_mult[0])  + detune[0];
       
        //lfo.phase_increment = inputConverterF * (osc_mult[0] / 8.0);
      }
      else {
        FMMult = ((int)((averageratio >> 8) + 1))/2.0 * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        
        o1.phase_increment = inputConverter * osc_mult[0]  ;        
        o3.phase_increment = (inputConverter  * chord[0] * osc_mult[0])  + detune[0];
        
        //lfo.phase_increment = inputConverter * (osc_mult[0] / 4.0);
      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();


      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct/2.0))));

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 512.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen


      if (FMFixedOn) {
        float avgcubing = averageratio / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001) * (aInModRatio * 8.0); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = (float)(1.0 + (mixHi * FMX_HiOffsetCont)/2048.0);
        o2.phase_increment = inputConverter * osc_mult[1] * FMX_HiOffset ;
        o4.phase_increment = inputConverter * chord[0]  * osc_mult[1] * FMX_HiOffset + detune[0] ;
        o6.phase_increment = inputConverter  * chord[1] * osc_mult[1]  * FMX_HiOffset + detune[1] ;
        o8.phase_increment = inputConverter  * chord[2] * osc_mult[1] * FMX_HiOffset + detune[2] ;
        o10.phase_increment = inputConverter * chord[3] * osc_mult[1] * FMX_HiOffset + detune[3] ;
        o1.phase_increment = inputConverterF  * osc_mult[0] ;
        o3.phase_increment = inputConverterF  * osc_mult[0] ;
        o5.phase_increment = inputConverterF * osc_mult[0] ;
        o7.phase_increment = inputConverterF * osc_mult[0] ;
        o9.phase_increment = inputConverterF * osc_mult[0] ;
        //lfo.phase_increment = inputConverterF * (osc_mult[0] / 8.0);
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);
        o2.phase_increment = inputConverter * osc_mult[1] * FMX_HiOffset ;
        o4.phase_increment = inputConverter * osc_mult[1] * chord[0] * FMX_HiOffset+ detune[0] ;
        o6.phase_increment = inputConverter * osc_mult[1] * chord[1] * FMX_HiOffset  + detune[1] ;
        o8.phase_increment = inputConverter * osc_mult[1] * chord[2] * FMX_HiOffset + detune[2] ;
        o10.phase_increment = inputConverter * osc_mult[1] * chord[3] * FMX_HiOffset + detune[3] ;
        o1.phase_increment = inputConverter * osc_mult[0] ;
        o3.phase_increment = inputConverter * osc_mult[0]  + detune[0];
        o5.phase_increment = inputConverter * osc_mult[0]  + detune[1];
        o7.phase_increment = inputConverter * osc_mult[0]  + detune[2];
        o9.phase_increment = inputConverter * osc_mult[0]  + detune[3];
        //lfo.phase_increment = inputConverter * (osc_mult[0] / 4.0);
      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();

      if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen


      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 3) / 1.1)) + 1.0) * aInModRatio; 
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
       
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = inputConverter * chord[0] * osc_mult[0] + detune[0];
        o5.phase_increment = inputConverter * chord[1] * osc_mult[0] + detune[1];
        o7.phase_increment = inputConverter * chord[2] * osc_mult[0] + detune[2];
        o9.phase_increment = inputConverter * chord[3] * osc_mult[0] + detune[3];
         o2.phase_increment =
          o4.phase_increment =
            o6.phase_increment =
              o8.phase_increment =
                o10.phase_increment = inputConverterA * osc_mult[1];
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; 
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;        
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = o2.phase_increment  * chord[0] + detune[0];
        o6.phase_increment = o2.phase_increment * chord[1] + detune[1];
        o8.phase_increment = o2.phase_increment  * chord[2] + detune[2];
        o10.phase_increment = o2.phase_increment  * chord[3] + detune[3];
        o1.phase_increment = inputConverter * osc_mult[0];
        o3.phase_increment = o1.phase_increment  * chord[0] + detune[0];
        o5.phase_increment = o1.phase_increment  * chord[1] + detune[1];
        o7.phase_increment = o1.phase_increment  * chord[2] + detune[2];
        o9.phase_increment = o1.phase_increment  * chord[3] + detune[3];
      }
      break;


    case 3://ALT CZ


      UPDATECONTROLS_CZALT();

     if (averageaInRAv > 4095) {
        ModRatioCubing = (averageaInRAv - 4095) / 256.0;
        aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
      }
      else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen



      if (FMFixedOn) {
        FMMult = (float)((((averageratio >> 3) / 1.1)) + 1.0) * aInModRatio; //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);
        o2.phase_increment =  inputConverterA * osc_mult[1]*FMX_HiOffset;
        o4.phase_increment =  inputConverterA * chord[0] * osc_mult[1]*FMX_HiOffset;
        o6.phase_increment =  inputConverterA * chord[1] * osc_mult[1]*FMX_HiOffset;
        o8.phase_increment =  inputConverterA * chord[2] * osc_mult[1]*FMX_HiOffset;
        o10.phase_increment = inputConverterA * chord[3] * osc_mult[1]*FMX_HiOffset;
        o1.phase_increment = inputConverter * osc_mult[0]*FMX_HiOffset;
        o3.phase_increment = inputConverter * chord[0] * osc_mult[0]*FMX_HiOffset + detune[0];
        o5.phase_increment = inputConverter * chord[1] * osc_mult[0]*FMX_HiOffset + detune[1];
        o7.phase_increment = inputConverter * chord[2] * osc_mult[0]*FMX_HiOffset + detune[2];
        o9.phase_increment = inputConverter * chord[3] * osc_mult[0]*FMX_HiOffset + detune[3];
        lfo.phase_increment = inputConverterF * (osc_mult[1] / 8.0);
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio;
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);
        o2.phase_increment = inputConverter * osc_mult[1];
        o4.phase_increment = o2.phase_increment  * chord[0] + detune[0];
        o6.phase_increment = o2.phase_increment * chord[1] + detune[1];
        o8.phase_increment = o2.phase_increment  * chord[2] + detune[2];
        o10.phase_increment = o2.phase_increment  * chord[3] + detune[3];
        o1.phase_increment = inputConverter * osc_mult[0]*FMX_HiOffset;
        o3.phase_increment = o1.phase_increment  * chord[0]*FMX_HiOffset + detune[0];
        o5.phase_increment = o1.phase_increment  * chord[1]*FMX_HiOffset + detune[1];
        o7.phase_increment = o1.phase_increment  * chord[2]*FMX_HiOffset + detune[2];
        o9.phase_increment = o1.phase_increment  * chord[3]*FMX_HiOffset + detune[3];
        lfo.phase_increment = inputConverter * (osc_mult[1] / 4.0);
      }

      break;

  }
}
