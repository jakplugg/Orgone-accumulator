void FASTRUN Delay_increment(void) {

  delayCounter = delayCounter + 16;
  delayCounterShift = delayCounter >> 4 ;
  delayTimeShift = uint16_t(delayCounter - ((delayCounts) << 4)) >> 4;

  diffuseTimeShift[0] = uint16_t((delayCounter) - diffuseCountShift[0]) >> 4;
  diffuseTimeShift[1] = uint16_t((delayCounter) - diffuseCountShift[1]) >> 4;
  diffuseTimeShift[2] = uint16_t((delayCounter) - diffuseCountShift[2]) >> 4;
  diffuseTimeShift[3] = uint16_t((delayCounter) - diffuseCountShift[3]) >> 4;


  if (gateOn) {
    delayTable[delayCounterShift] = delayOut;
    delayOut = delayTable[delayTimeShift];
    finalOut = delayOut;
  }
  else {
    audioIn = (adc->analogRead(Audio_input_pin)) - 2047;
    delayTable[delayCounterShift] = (audioIn) + ((delayOut * delayFeedback) >> 12);

    if (diffuseMode == 1) {
      delayOut = (delayTable[diffuseTimeShift[0]] + delayTable[diffuseTimeShift[1]] +
                  delayTable[diffuseTimeShift[2]] + delayTable[diffuseTimeShift[3]]) >> 2 ;
    }
    else {
      delayOut = delayTable[delayTimeShift];
    }


    finalOut = ((delayOut * (delayMix)) >> 12) + ((audioIn * (4096 - delayMix)) >> 12);
  }


  analogWrite (A14, (finalOut << 4) + 32768);
}

