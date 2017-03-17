void CONTROL_SHED(void) {
  CARC ++;
  if (CARC > 9) {
    CARC = 0;
  }
  CONTROL_IN[CARC] = analogRead(CONTROL_PIN[CARC]);
}

void CV_SHED(void) {
  VARC ++;
  if (VARC > 4) {
    VARC = 1;
  }
  CV_IN[VARC] = analogRead(CV_PIN[VARC]);
}

void VOCTAVG(void) {
  VOtotalL = VOtotalL - VOreadingsL[VOreadIndexL];
  VOtotalS = VOtotalS - VOreadingsS[VOreadIndexS];
  
  VOreadingsS[VOreadIndexS] = VOreadingsL[VOreadIndexL] = analogRead(CV_PIN[0]);
  
  VOtotalL = VOtotalL + VOreadingsL[VOreadIndexL];
   VOtotalS = VOtotalS + VOreadingsS[VOreadIndexS];
  
  VOaverageL = uint32_t(VOtotalL / VOnumReadingsLong);
   VOaverageS = uint32_t(VOtotalS / VOnumReadingsShort);

  if (abs(VOaverageL - VOreadingsL[VOreadIndexL]) > VOthresh){
  CV_IN[0] = VOreadingsS[VOreadIndexS];
  testout = 1;
  }
  else {
  if (VOaverageL = VOaverageS);
  testout = 0;
  }
  
  VOreadIndexL = VOreadIndexL + 1;
  if (VOreadIndexL >= VOnumReadingsLong) {
    VOreadIndexL = 0;
  }  

    VOreadIndexS = VOreadIndexS + 1;
  if (VOreadIndexS >= VOnumReadingsShort) {
    VOreadIndexS = 0;
  } 
}
