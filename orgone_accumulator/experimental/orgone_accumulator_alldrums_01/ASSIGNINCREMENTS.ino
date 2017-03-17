
void ASSIGNINCREMENTS_DRUM() { //--------------------------------------------------------drum effect

  UPDATECONTROLS_DRUM();
 
  CZMix = envVal>>1;

  
  if (FMFixedOn) {
    osc_mult[0] = 250.0;
    osc_mult[1] = 4.0;
    o1[drumNum].phase_increment = inputConverter * osc_mult[1]  ;
    o2[drumNum].phase_increment = inputConverterF * osc_mult[0] * chord[0];
    o3[drumNum].phase_increment = inputConverterF * osc_mult[0] * chord[1];
    o4[drumNum].phase_increment = inputConverterF * osc_mult[0] * chord[2];
    o5[drumNum].phase_increment = inputConverterF * osc_mult[0] * chord[3];
  }
  else {
    FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
    osc_mult[0] = FMMult;
    osc_mult[1] = 4.0;
    o1[drumNum].phase_increment = inputConverter * osc_mult[1]  ;
    o2[drumNum].phase_increment = (inputConverter * osc_mult[1]) * chord[0];
    o3[drumNum].phase_increment = (inputConverter * osc_mult[1]) * chord[1];
    o4[drumNum].phase_increment = (inputConverter * osc_mult[1]) * chord[2];
    o5[drumNum].phase_increment = (inputConverter * osc_mult[1]) * chord[3];
  }
}



void ASSIGNINCREMENTS_DRUM_FM() { //--------------------------------------------------------drum effect

  UPDATECONTROLS_DRUM();
 
  CZMix = envVal>>1;

  
  if (FMFixedOn) {
    osc_mult[0] = 62.5;
    osc_mult[1] = 4.0;
    o1[drumNum].phase_increment = inputConverter * osc_mult[1]  ;
    o2[drumNum].phase_increment = inputConverterF * osc_mult[0] * chord[0];
 
  }
  else {
    FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
    osc_mult[0] = 1;
    osc_mult[1] = 4.0;
    o1[drumNum].phase_increment = inputConverter * osc_mult[1]  ;
    o2[drumNum].phase_increment = (inputConverter * osc_mult[0]) * chord[0];
   
  }
}

void ASSIGNINCREMENTS_DRUM_DEL() { //--------------------------------------------------------drum effect

  UPDATECONTROLS_DRUM();
 
  CZMix = envVal>>1;

  
  if (FMFixedOn) {
    osc_mult[0] = 62.5;
    osc_mult[1] = 4.0;
    o1[drumNum].phase_increment = inputConverter * osc_mult[1]  ;
    o2[drumNum].phase_increment = inputConverterF * osc_mult[0] * chord[0];
    delayTime0[drumNum] = constrain((0xFFFFFFFF/o1[drumNum].phase_increment),1,2047);
 
  }
  else {
    FMMult = ((int)((averageratio >> 9) + 1)) * aInModRatio; //FM + free
    osc_mult[0] = 1;
    osc_mult[1] = 4.0;
    o1[drumNum].phase_increment = inputConverter * osc_mult[1]  ;
    o2[drumNum].phase_increment = (inputConverter * osc_mult[0]) * chord[0];
   
  }
}


