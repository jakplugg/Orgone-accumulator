
void UPDATECONTROLS_DRUM() {


  switch (ARC + 1) {

    case 8:

      break;

    case 10:




      break;

    case 3:

      EffectAmountCont = analogControls[2];

      break;

    case 4:

      TUNELOCK_TOGGLE();

Serial.print(delayTime0[0]);
Serial.print("          ");
Serial.println(delayTime0[1]);
      //((((drum[drumNum].d * drum[drumNum].d)>>16)+1)*drum[drumNum].d)>>2;drum[drumNum].d
      //drum decay

      break;

    case 5:

      //waveTableMidLink = drumWT[analogControls[8] >> 9];

      break;

    case 6: //select hi wave



      break;

    case 1:
      mixPos = (analogControls[6] >> 1); //this is drum wave mix

      OSC_MODE_TOGGLES();


      break;

    case 7:
      FX_TOGGLES();


      break;

    case 2:


      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);

      //waveTableHiLink = drumWT2[analogControls[4] >> 9]; //drum uses mid wave from fm
      //drum uses mid wave from fm
      //      if ((analogControls[3] >> 9) == 15) WTShiftMid = 31;
      //      else WTShiftMid = 23;

      break;


  }
}


