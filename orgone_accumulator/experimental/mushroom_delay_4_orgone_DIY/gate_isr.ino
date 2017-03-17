void gateISR() {
  if (digitalReadFast(gateIn)) {

    gateOn = 1; 
  }

  else {
    gateOn = 0;
  }
}
