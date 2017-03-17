void FASTRUN ISR_OSC(void) {

  Ophase2[0] = Ophase2[0] + (2097152 << Ooctave[0]);
  Owave2[0] = waveLink[Ophase2[0]>> 23];

  
    Ooutput = (Owave2[0] >> 4);
    analogWrite(A14, (Ooutput) + 2047);
 
}





