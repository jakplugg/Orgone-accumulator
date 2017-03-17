void loop() {

  CONTROL_SHED();
  
  //CV_VOCT = (analogRead(A0)); //main v/oct CV in. only use 13 bits of analog in SEPERATE AINS WITH CODE  
 
  VOCT_ADD_TUNERS = (CV_VOCT * 1.2025) + ((POT_TUNE >> 10)*4096) + ((POT_TUNE_FINE >>9 ) * 341.333333);
  //OSC_CLOCK = superPow2_table[VOCT_ADD_TUNERS & 4095]>>13;
  VOCT_ADD_TUNERS_FLOAT = float(VOCT_ADD_TUNERS & 4095)/4096.0;
  OSC_CLOCK = uint32_t(fastpow2(VOCT_ADD_TUNERS_FLOAT)*16384.0);
  Ooctave[0] = (VOCT_ADD_TUNERS >> 12);

  //averaging the voct input.
   VOCTAVG();  

  waveLink = wavePointer[POT_WAVE_LO >> 13]; //assign wavetable

Serial.print(testout);
Serial.print("   ");
Serial.print(OSC_CLOCK);
Serial.print("   ");
Serial.print(VOaverageS);
Serial.print("   ");
Serial.println(VOaverageL );
  
   CV_SHED();
   if(testout == 1){//resetting tone and attachinterrupt over and over causes glitches in the sample rate. this will let it update only when the input has changed more than a threshold amount from the average.
   tone(timerPin[0], OSC_CLOCK); //tone works better than analogwritefrequency.
   //analogWrite(timerPin[0],512);
   attachInterrupt(timerPin[0], ISR_OSC, RISING);  
   }
   OSC_CLOCK_OLD = OSC_CLOCK;
}
