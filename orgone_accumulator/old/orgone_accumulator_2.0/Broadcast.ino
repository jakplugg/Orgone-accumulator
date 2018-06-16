// Broadcast version 1.0



int BROADCAST = 1;

#define POT_FREQ         analogControls[0]
#define POT_INDEX        analogControls[1]
#define POT_EFFECT       analogControls[2]
#define POT_MOD          analogControls[3]
#define POT_WAVE_HI      analogControls[4]
#define POT_WAVE_MID     analogControls[5]
#define POT_POS          analogControls[6]
#define POT_TUNE_FINE    analogControls[7]
#define POT_WAVE_LO      analogControls[8]  
#define POT_TUNE         analogControls[9]

enum {
    PT_WAVEFORM1 = 0,
    PT_WAVEFORM2,
    PT_WAVEFORM3,
    PT_MOD,
    PT_TUNE,
    PT_TUNE_FINE,
    PT_POSITION,
    PT_EFFECT,
    PT_INDEX,
    PT_FREQ,
    BROADCAST_PT, // count
    
    SW_DETUNE1 = 0,
    SW_DETUNE2,
    SW_DETUNE3,
    SW_FIX,
    SW_TUNELOCK,
    BROADCAST_SW, // count
    
    CV_VOCT_IN = 0,
    CV_POSITION_IN,
    CV_DETUNE_IN,
    CV_INDEX_IN,
    CV_FREQ_IN,
    BROADCAST_CV, // count
    
    BROADCAST_UNUSED = 4, // count
    
    STX = 2,
    ETX = 3,
    PACKET_BROADCAST = 0x58
};

#pragma pack(1)

typedef struct {
    uint8_t  stx;
    uint8_t  typeCode;
    uint16_t pt[BROADCAST_PT];
    uint16_t cv[BROADCAST_CV];
    uint8_t  sw[BROADCAST_SW];
    uint32_t unused[BROADCAST_UNUSED];
    uint8_t  effect;
    uint8_t  oscMode;    
    uint8_t  etx;
} BroadcastPacket;

#define BROADCASTPACKET_SIZE  sizeof(BroadcastPacket)

BroadcastPacket bPacket;

void sendBroadcastPacket()
{
  bPacket.stx = STX;
  bPacket.typeCode = PACKET_BROADCAST;

  bPacket.pt[PT_WAVEFORM1]    = POT_WAVE_LO;
  bPacket.pt[PT_WAVEFORM2]    = POT_WAVE_MID;
  bPacket.pt[PT_WAVEFORM3]    = POT_WAVE_HI;
  bPacket.pt[PT_MOD]          = POT_MOD;
  bPacket.pt[PT_TUNE]         = POT_TUNE;
  bPacket.pt[PT_TUNE_FINE]    = POT_TUNE_FINE;
  bPacket.pt[PT_POSITION]     = POT_POS;
  bPacket.pt[PT_EFFECT]       = POT_EFFECT;
  bPacket.pt[PT_INDEX]        = POT_INDEX;
  bPacket.pt[PT_FREQ]         = POT_FREQ;

  bPacket.sw[SW_DETUNE1]      = EffectEnOn_A;
  bPacket.sw[SW_DETUNE2]      = EffectEnOn_B;
  bPacket.sw[SW_DETUNE3]      = EffectEnOn_C;
  bPacket.sw[SW_FIX]          = FMFixedOn;
  bPacket.sw[SW_TUNELOCK]     = tuneLockOn;

  bPacket.cv[CV_VOCT_IN]      = inCV;
  bPacket.cv[CV_POSITION_IN]  = aInPos;
  bPacket.cv[CV_DETUNE_IN]    = aInEffectReading;
  bPacket.cv[CV_INDEX_IN]     = aInModIndex;
  bPacket.cv[CV_FREQ_IN]      = AInRawFilter;

  bPacket.unused[0] = pcounter;
  bPacket.unused[1] = (uint32_t)inputConverter;
  bPacket.unused[2] = ISRrate;
  bPacket.unused[3] = ADT1;

  bPacket.effect = FX;
  bPacket.oscMode = oscMode;  
  bPacket.etx = ETX;
  
  uint8_t *ptr = (uint8_t *)&bPacket;
  for (uint16_t i = 0; i < BROADCASTPACKET_SIZE; ++i)
    Serial.write(ptr[i]);
}

// ----------------------

boolean requestForData = false;

void monitorSerialReception()
{
  for (;;) {
    if (Serial.available() <= 0) return;
    Serial.read();
    requestForData = true;
  }
}
  


