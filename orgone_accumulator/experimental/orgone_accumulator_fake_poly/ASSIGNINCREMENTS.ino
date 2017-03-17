

void ASSIGNINCREMENTS() { //--------------------------------------------------------default

  CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047); 
 
  switch (oscMode) { //switches which oscs get changed by FM and how much multiplier ;
    case 0://break intentionally ommited

      UPDATECONTROLS_FM();


      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex[rr] = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + 
      (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * ((inputConverter[rr] / conf_TuneMult) / 2.0))));

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
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1]  ;
        o4[rr].phase_increment = (inputConverter[rr]  * osc_mult[1]) + detune[0];
        
        o1[rr].phase_increment = inputConverterF * osc_mult[0] ;
        o3[rr].phase_increment = (inputConverterF   * osc_mult[0])  + detune[0];
        
      }
      else {
        FMMult = ((int)((averageratio >> 8) + 1))/2.0 * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1]  ;
        o4[rr].phase_increment = ((inputConverter[rr] ) * osc_mult[1]) + detune[0];
       
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0] ;
        o3[rr].phase_increment = (inputConverter[rr]  *  osc_mult[0])  + detune[0];
       
        //lfo[rr].phase_increment = inputConverter[rr] * (osc_mult[0] / 4.0);
      }
      break;



    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).


      UPDATECONTROLS_FMALT();


      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex[rr] = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) 
      + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * ((inputConverter[rr] / conf_TuneMult)/2.0))));

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
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1] * FMX_HiOffset ;
        o4[rr].phase_increment = inputConverter[rr] * osc_mult[1] * FMX_HiOffset + detune[0] ;
       
        o1[rr].phase_increment = inputConverterF  * osc_mult[0] ;
        o3[rr].phase_increment = inputConverterF  * osc_mult[0] ;
       
        //lfo[rr].phase_increment = inputConverterF * (osc_mult[0] / 8.0);
      }
      else {
        FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1] * FMX_HiOffset ;
        o4[rr].phase_increment = inputConverter[rr] * osc_mult[1] * FMX_HiOffset+ detune[0] ;
       
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0] ;
        o3[rr].phase_increment = inputConverter[rr] * osc_mult[0]  + detune[0];
       
        //lfo[rr].phase_increment = inputConverter[rr] * (osc_mult[0] / 4.0);
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
       
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0];
        o3[rr].phase_increment = inputConverter[rr] * osc_mult[0] + detune[0];
      
         o2[rr].phase_increment =
          o4[rr].phase_increment =
            
              inputConverterA * osc_mult[1];
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio; 
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;               
       
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0];
        o2[rr].phase_increment = o1[rr].phase_increment  *  osc_mult[1];

         o3[rr].phase_increment = inputConverter[rr] * osc_mult[0]  + detune[0];
        o4[rr].phase_increment = o2[rr].phase_increment  *  osc_mult[1] + detune[0];
       
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
        o2[rr].phase_increment =  inputConverterA * osc_mult[1]*FMX_HiOffset;
        o4[rr].phase_increment =  inputConverterA * osc_mult[1]*FMX_HiOffset;
        
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0]*FMX_HiOffset;
        o3[rr].phase_increment = inputConverter[rr] * osc_mult[0]*FMX_HiOffset + detune[0];
       
       
      }
      else {
        FMMult = (float)((((averageratio >> 5) / 7.0)) + 1.0) * aInModRatio;
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1];
        o4[rr].phase_increment = o2[rr].phase_increment  + detune[0];
       
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0]*FMX_HiOffset;
        o3[rr].phase_increment = o1[rr].phase_increment  * FMX_HiOffset + detune[0];
       
       
      }

      break;

  }
}



void ASSIGNINCREMENTS_D() { //--------------------------------------------------------delay


  CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

  if (averageaInRAv > 4095) {
    ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
    aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
  }
  else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen


  switch (oscMode) {
    case 0:

      UPDATECONTROLS_FM();

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex[rr] = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 2.0))));


      if (FMFixedOn) {
        avgcubing = (float)(analogControls[3] / 500.0); //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001); 
        //Serial.println(FMMult);
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o1[rr].phase_increment = inputConverterF * osc_mult[0] ;
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1]  ;
   

      }
      else {
        FMMult = ((int)((analogControls[3] >> 9) + 1)); 
        osc_mult[0] = FMMult;
        osc_mult[1] = 4.0;
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0] ;
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1] ;
 
      }
      break;

    case 2://fm mode with x button pressed allows pitch bending on hi position and FM is LFO in fixed (no auto get freq).

      UPDATECONTROLS_FMALT();

      FMIndexContCubing = FMIndexCont / 256.0;
      FMIndex[rr] = (uint32_t((float)(((FMIndexContCubing * FMIndexContCubing * FMIndexContCubing) + (averageaInIAvCubing * averageaInIAvCubing * averageaInIAvCubing)) * (inputVOct / 2.0))));

FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);
    
      if (FMFixedOn) {
        float avgcubing = analogControls[3] / 500.0; //change to adjust "LFO" in fm fixed
        FMMult = ((((float)(avgcubing * avgcubing * avgcubing))) + 0.001); //FM+fixed mult control
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        
        o1[rr].phase_increment = inputConverterF * osc_mult[0] ;
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1] * FMX_HiOffset ;
 

      }
      else {
        FMMult = ((int)((analogControls[3] >> 9) + 1)); 
        osc_mult[0] = FMMult;
        osc_mult[1] = 4;
        
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0] ;
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1] * FMX_HiOffset ;
 

      }
      break;
    case 1://cz

      UPDATECONTROLS_CZ();

      if (FMFixedOn) {
        FMMult = (float)((((analogControls[3] >> 3) / 1.1)) + 1.0); //CZ + fixed + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0];
        o2[rr].phase_increment = inputConverterF * osc_mult[1];
     
      }
      else {
        FMMult = (float)((((analogControls[3] >> 5))) + 1.0); //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0];
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1];
   

      }
      break;


    case 3://ALT CZ

      UPDATECONTROLS_CZALT();
FMX_HiOffset = (float)(1.0 + ((float)(mixHi) * FMX_HiOffsetCont)/2048.0);

      if (FMFixedOn) {
        FMMult = (float)((((analogControls[3] >> 3) / 1.1)) + 1.0); 
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        
        o2[rr].phase_increment = inputConverterF * osc_mult[1] ; //modulation not detuned
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0] *FMX_HiOffset;    
       
       
      }
      else {
        FMMult = (float)((((analogControls[3] >> 5))) + 1.0); //CZ + free + free
        osc_mult[0] = 4;
        osc_mult[1] = FMMult;
        
        o2[rr].phase_increment = inputConverter[rr] * osc_mult[1];
        o1[rr].phase_increment = inputConverter[rr] * osc_mult[0] * FMX_HiOffset;
       
       
       
      }
      break;
  }
}


void ASSIGNINCREMENTS_TWANG() { //-------------------------------------------------------sort of karplus strong effect.

  UPDATECONTROLS_TWANG();
  if (averageaInRAv > 4095) {
    ModRatioCubing = (averageaInRAv - 4095.0) / 256.0;
    aInModRatio = ((ModRatioCubing * ModRatioCubing * ModRatioCubing) / 2048.0) + 1.0;
  }
  else aInModRatio = (averageaInRAv / 4096.0); //down direction dont go past zero, or divide by zero could happen

 
 CZMix = constrain((FMIndexCont + (2047 - (averageaInIAv / 2.0))), 0, 2047);

  
  if (FMFixedOn) {
    osc_mult[0] = 62.5;
    osc_mult[1] = 4.0;
    o1[rr].phase_increment = inputConverter[rr] * osc_mult[1]  ;
    
    delayTime0[rr] = constrain((0xFFFFFFFF/o1[rr].phase_increment),1,2047);
 
  }
  else {
    FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
    osc_mult[0] = FMMult;
    osc_mult[1] = 4.0;
    o1[rr].phase_increment = inputConverter[rr] * osc_mult[1]  ;
    o2[rr].phase_increment = (inputConverter[rr] * osc_mult[0]) ;
    delayTime0[rr] = constrain((0xFFFFFFFF/o2[rr].phase_increment),1,2047);
   
  }
}
