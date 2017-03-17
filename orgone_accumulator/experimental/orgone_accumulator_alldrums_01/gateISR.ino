void gateISR() {
  if (digitalReadFast(gateIn)) {

    if (roundrobinOn) {
      drumNum = !drumNum;
    }

    gateState = 1;
    declickRampOut = 4095;
    declickHold = FinalOut;

    o1[drumNum].phase =
      o2[drumNum].phase =
        o3[drumNum].phase =
          o4[drumNum].phase =
            o5[drumNum].phase =
              o6[drumNum].phase =
                o7[drumNum].phase =
                  o8[drumNum].phase =
                    o9[drumNum].phase =                    
                        o10[drumNum].phase =
                          o11[drumNum].phase =
                            o12[drumNum].phase = 0;

    
    drum[drumNum].envStep[0] =
      drum[drumNum].envStep[1] =
        drum[drumNum].envStep[2] =
          drum[drumNum].st =
            drum[drumNum].st2 = 0;

    loopReset = 1;
  }

  else {
    gateState = 0;
  }
}

