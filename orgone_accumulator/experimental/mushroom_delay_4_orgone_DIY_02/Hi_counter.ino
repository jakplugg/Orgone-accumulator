void FASTRUN Hi_counter(void) {
  Nold0 = Ntest0;
  Nold1 = Ntest1;
  Hi_count0 = Hi_count0 + Hi_count0_rate;
  Hi_count1 = Hi_count1 + Hi_count1_rate;
  Ntest0 = Hi_count0 >> 31;
  Ntest1 = Hi_count1 >> 31;
  if (Ntest0 != Nold0) {

    delayCounter0 = delayCounter0 + 16;
    delayCounterShift0 = delayCounter0 >> 4 ;
    delayTimeShift0 = uint16_t(delayCounter0 - ((delayCounts) << 4)) >> 4;

    if (diffuseMode == 1) {
      diffuseTimeShift[0] = uint16_t((delayCounter0) - diffuseCountShift[0]) >> 4;
      diffuseTimeShift[1] = uint16_t((delayCounter0) - diffuseCountShift[1]) >> 4;
      diffuseTimeShift[2] = uint16_t((delayCounter0) - diffuseCountShift[2]) >> 4;
      diffuseTimeShift[3] = uint16_t((delayCounter0) - diffuseCountShift[3]) >> 4;
    }

    if (gateOn) {
      delayTable0[delayCounterShift0] = delayOut0;
      delayOut0 = delayTable0[delayTimeShift0];
      finalOut0 = delayOut0;
    }
    else {
      audioIn0 = (adc->analogRead(Audio_input_pin)) - 2047;
      delayTable0[delayCounterShift0] = (audioIn0) + ((delayOut0 * delayFeedback) >> 12);


      if (diffuseMode == 1) {
        delayOut0 = (delayTable0[diffuseTimeShift[0]] + delayTable0[diffuseTimeShift[1]] +
                     delayTable0[diffuseTimeShift[2]] + delayTable0[diffuseTimeShift[3]]) >> 2 ;
      }
      else {
        delayOut0 = delayTable0[delayTimeShift0];
      }

      finalOut0 = ((delayOut0 * (delayMix0)) >> 12) + ((audioIn0 * (4096 - delayMix0)) >> 12);
    }

    finalOut0 = (finalOut0 * (4096 - delayMix1)) >> 12;
    finalOut = finalOut0 + finalOut1;
    analogWrite (A14, (finalOut << 3) + 32768);

  }

  if (Ntest1 != Nold1) {
    delayCounter1 = delayCounter1 + 16;
    delayCounterShift1 = delayCounter1 >> 4 ;
    delayTimeShift1 = uint16_t(delayCounter1 - ((delayCounts) << 4)) >> 4;

    if (gateOn) {
      delayTable1[delayCounterShift1] = delayOut1;
      delayOut1 = delayTable1[delayTimeShift1];
      finalOut1 = delayOut1;
    }
    else {
      //audioIn1 = (adc->analogRead(Audio_input_pin)) - 2047;
      delayTable1[delayCounterShift1] = (audioIn0) + ((delayOut1 * delayFeedback) >> 12);

      delayOut1 = delayTable1[delayTimeShift1];

      finalOut1 = ((delayOut1 * (delayMix0)) >> 12) + ((audioIn0 * (4096 - delayMix0)) >> 12);
    }

    finalOut1 = (finalOut1 * delayMix1) >> 12;
  }


}
