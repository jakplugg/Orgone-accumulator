void gateISR() {
  if (digitalReadFast(gateIn)) {
    gateState = 1;
    firstNote = HIGH;
    //rr = 0;
    inCVck[rr] = inCV;
    for (int te = 0; te < NumVoices; te = te + 1) {
      inputConverter[te] =  0.0;
      FMIndex[te] = 0.0;
      o1[te].phase_increment = 0;
      o2[te].phase_increment = 0;
      o3[te].phase_increment = 0;
      o4[te].phase_increment = 0;
      o1[te].phase = 0;
      o2[te].phase = 0;
      o3[te].phase = 0;
      o4[te].phase = 0;
      twang[te].envStep[0] =
        twang[te].envStep[1] =
          twang[te].envStep[2] =
            twang[te].st =
              twang[te].st2 = 0;

    }

    // nextNote();
  }
  else {
    gateState = 0;
  }
}

void nextNote() {//no round robin. the voice allocation stops when there is no more
  // if (gateState == 1){
  rr ++;
  if (rr > (NumVoices - 1)) rr = 0;
  inputConverter[rr] =  0.0;
  FMIndex[rr] = 0.0;
  o1[rr].phase_increment = 0;
  o2[rr].phase_increment = 0;
  o3[rr].phase_increment = 0;
  o4[rr].phase_increment = 0;
  o1[rr].phase = 0;
  o2[rr].phase = 0;
  o3[rr].phase = 0;
  o4[rr].phase = 0;
  // }

  //inCVck[rr] = inCV;

  twang[rr].envStep[0] =
    twang[rr].envStep[1] =
      twang[rr].envStep[2] =
        twang[rr].st =
          twang[rr].st2 = 0;

  loopReset = 1;

}

