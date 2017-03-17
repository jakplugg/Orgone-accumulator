void UPDATECONTROLS_CZ() {

  if (fixedWave == 1) {
    lo_wavesel_index = analogControls[8] >> 9;
    if ((mixLo > 256) && (lo_wavesel_index != lo_wavesel_indexOld)) {
      declick_ready = 1;
      lo_wavesel_indexOld = lo_wavesel_index;
    }
    waveTableLoLink = CZWTselLo[lo_wavesel_index];


    Mid_wavesel_index = analogControls[5] >> 9;
    if ((mixMid > 256) && (Mid_wavesel_index != Mid_wavesel_indexOld)) {
      declick_ready = 1;
      Mid_wavesel_indexOld = Mid_wavesel_index;
    }
    waveTableMidLink = CZWTselMid[Mid_wavesel_index];

    Hi_wavesel_index = analogControls[4] >> 9;
    if ((mixHi > 256) && (Hi_wavesel_index != Hi_wavesel_indexOld)) {
      declick_ready = 1;
      Hi_wavesel_indexOld = Hi_wavesel_index;
    }
    waveTableHiLink = CZWTselHi[Hi_wavesel_index];
  }

  switch (ARC + 1) {

    case 8:
      //Serial.print(GWTlo1);
      //Serial.print("     ");

      break;

    case 10:


      //outputs the frequency on USB serial. tune lock, FM and X must be off


      break;

    case 3:

      EffectAmountCont = analogControls[2];


      break;

    case 4:

      TUNELOCK_TOGGLE();



      break;

    case 5:




      break;

    case 6: //select hi wave



      if ((analogControls[4] >> 9) == 15) WTShiftHi = 31;
      else WTShiftHi = 23;

      break;

    case 1:
      mixPos = (analogControls[6] >> 1);

      OSC_MODE_TOGGLES();


      break;

    case 7:
      FX_TOGGLES();


      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0];
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);
      FMTable = CZWTselFM[analogControls[3] >> 9];

      break;


  }
}
//--------------------------------------------------------------------CZ-ALT--------------------------------------------------
void UPDATECONTROLS_CZALT() {
  if (fixedWave == 1) {
    lo_wavesel_index = analogControls[8] >> 9;
    if ((mixLo > 256) && (lo_wavesel_index != lo_wavesel_indexOld)) {
      declick_ready = 1;
      lo_wavesel_indexOld = lo_wavesel_index;
    }
    waveTableLoLink = CZWTselLo[lo_wavesel_index];

    Mid_wavesel_index = analogControls[5] >> 9;
    if ((mixMid > 256) && (Mid_wavesel_index != Mid_wavesel_indexOld)) {
      declick_ready = 1;
      Mid_wavesel_indexOld = Mid_wavesel_index;
    }
    waveTableMidLink = CZWTselMid[Mid_wavesel_index];
  }



  switch (ARC + 1) {

    case 8:

      break;

    case 10:


      break;

    case 3:
      TUNELOCK_TOGGLE();
      EffectAmountCont = analogControls[2];

      break;

    case 4:



      if ((analogControls[5] >> 9) == 15) WTShiftMid = 31;
      else WTShiftMid = 23;


      break;

    case 5:



      break;

    case 6: //no hi wave in alt(x) mode

      FMX_HiOffsetContCub = (analogControls[4] >> 3) - 512;
      FMX_HiOffsetCont = (float)(FMX_HiOffsetContCub * FMX_HiOffsetContCub * FMX_HiOffsetContCub) / 1073741824.0;


    case 1:
      mixPos = analogControls[6] >> 1;

      OSC_MODE_TOGGLES();



      break;

    case 7:
      FX_TOGGLES();


      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0];
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);

      FMTable = CZWTselFM[analogControls[3] >> 9];
     
      if ((analogControls[3] >> 9) == 15) WTShiftFM = 31;
      else WTShiftFM = 23;


      break;


  }
}


//----------------------------------------------------------------FM--------------------------------------------------------
void UPDATECONTROLS_FM() {
  if (fixedWave == 1) {
    lo_wavesel_index = analogControls[8] >> 9;
    if ((mixLo > 256) && (lo_wavesel_index != lo_wavesel_indexOld)) {
      declick_ready = 1;
      lo_wavesel_indexOld = lo_wavesel_index;
    }
    waveTableLoLink = FMWTselLo[lo_wavesel_index];

    Mid_wavesel_index = analogControls[5] >> 9;
    if ((mixMid > 256) && (Mid_wavesel_index != Mid_wavesel_indexOld)) {
      declick_ready = 1;
      Mid_wavesel_indexOld = Mid_wavesel_index;

    }
    waveTableMidLink = FMWTselMid[Mid_wavesel_index];

    Hi_wavesel_index = analogControls[4] >> 9;
    if ((mixHi > 256) && (Hi_wavesel_index != Hi_wavesel_indexOld)) {
      declick_ready = 1;
      Hi_wavesel_indexOld = Hi_wavesel_index;
    }
    waveTableHiLink = FMWTselHi[Hi_wavesel_index];
  }


  switch (ARC + 1) {
    case 8: //8 and 10 are skipped when tune lock is on, do not use.
      break;
    case 10:
      break;

    case 3:
      TUNELOCK_TOGGLE();
      EffectAmountCont = analogControls[2];

      break;

    case 4: //mid wave

      break;

    case 5:  //lo wave

      break;

    case 6: //select hi wave


      if ((analogControls[4] >> 9) == 15) WTShiftHi = 31;
      else WTShiftHi = 23;

      break;

    case 1:
      mixPos = (analogControls[6] >> 1);

      OSC_MODE_TOGGLES();

      break;

    case 7:

      FX_TOGGLES();

      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0]; //fm ratio control smoothing in FM
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);

      FMTable = FMWTselFM[analogControls[3] >> 9];
      if ((analogControls[3] >> 9) == 15) WTShiftFM = 31;
      else WTShiftFM = 23;


      break;


  }
}
//--------------------------------------------------------------------------FMALT--------------------------------------------------------------

void UPDATECONTROLS_FMALT() {

  if (fixedWave == 1) {
    lo_wavesel_index = analogControls[8] >> 9;
    if ((mixLo > 256) && (lo_wavesel_index != lo_wavesel_indexOld)) {
      declick_ready = 1;
      lo_wavesel_indexOld = lo_wavesel_index;
    }
    waveTableLoLink = FMWTselLo[lo_wavesel_index];

    Mid_wavesel_index = analogControls[5] >> 9;
    if ((mixMid > 256) && (Mid_wavesel_index != Mid_wavesel_indexOld)) {
      declick_ready = 1;
      Mid_wavesel_indexOld = Mid_wavesel_index;
    }
    waveTableMidLink = FMWTselMid[Mid_wavesel_index];
  }

  switch (ARC + 1) {

    case 8: //7 and 9 are skipped when tune lock is on, do not use.
      break;
    case 10:
      break;

    case 3:
      TUNELOCK_TOGGLE();
      EffectAmountCont = analogControls[2];

      break;

    case 4:


      if ((analogControls[5] >> 9) == 15) WTShiftMid = 31;
      else WTShiftMid = 23;
      break;

    case 5:

      break;

    case 6: //select hi pitch offset
      FMX_HiOffsetContCub = (analogControls[4] >> 3) - 512;
      FMX_HiOffsetCont = (float)(FMX_HiOffsetContCub * FMX_HiOffsetContCub * FMX_HiOffsetContCub) / 134217728.0;
      break;

    case 1:
      mixPos = (analogControls[6] >> 1);

      OSC_MODE_TOGGLES();


      break;

    case 7:

      FX_TOGGLES();

      break;

    case 2:
      totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0]; //fm ratio control smoothing in FM
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;
      break;

    case 9:
      FMIndexCont = (int)(analogControls[1] >> 2);

      FMTable = FMWTselFM[analogControls[3] >> 9];
      if ((analogControls[3] >> 9) == 15) WTShiftFM = 31;
      else WTShiftFM = 23;

      break;


  }
}

void UPDATECONTROLS_TWANG() {

lo_wavesel_index = analogControls[8] >> 9;
    waveTableLoLink = CZWTselMid[lo_wavesel_index];


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


      //((((drum_d * drum_d)>>16)+1)*drum_d)>>2;drum_d
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
totalratio = totalratio - readingsratio[controlAveragingIndex];
      readingsratio[controlAveragingIndex] = analogControls[0];
      totalratio = totalratio + readingsratio[controlAveragingIndex];
      controlAveragingIndex = controlAveragingIndex + 1;
      if (controlAveragingIndex >= numreadingsratio) controlAveragingIndex = 0;
      averageratio = totalratio / numreadingsratio;

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


