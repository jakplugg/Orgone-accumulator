void gateISR() {
  if (digitalReadFast(gateIn)) {

    gateState = 1;
    declickRampOut = 4095;
    declickValue = FinalOut;

    o1.phase =
      o2.phase =
        o3.phase =
          o4.phase =
            o5.phase =
              o6.phase =
                o7.phase =
                  o8.phase =
                    o9.phase =
                      lfo.phase =
                        o10.phase =
                          o11.phase =
                            o12.phase = 0;

    if (pulsarOn) {
      oSQ.phase = 0;
    }

    drum_envStep[0] =
      drum_envStep[1] =
        drum_envStep[2] =
          drum_st =
            drum_st2 = 0;

    loopReset = 1;
  }

  else {
    gateState = 0;
  }
}

