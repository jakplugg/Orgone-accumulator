//  unsigned saturate to 12 bits  
static inline uint32_t usat12(uint32_t a) __attribute__((always_inline, unused));
static inline uint32_t usat12(uint32_t a)
{
  if (a > 4095) a = 4095;
  return a;
}

static inline float fastpow2 (float p) {
  float offset = (p < 0) ? 1.0f : 0.0f;
  float clipp = (p < -126) ? -126.0f : p;
  int w = clipp;
  float z = clipp - w + offset;
  union {
    uint32_t i;
    float f;
  } v = { cast_uint32_t ( (1 << 23) *
                          (clipp + 121.2740575f + 27.7280233f / (4.84252568f - z) - 1.49012907f
                           * z) )
        };

  return v.f;
}

static inline float fasterpow2 (float p)
{
  union {
    uint32_t i;
    float f;
  } v = { (1 << 23) * (p + 126.94269504f) };
  return v.f;
}

void FASTRUN READSLOW(void) {
  switch (ARC){
    case 0:
     dtuner = (float)((((int)((adc->analogRead(Coarse_tune_pin,ADC_0)<<1)/227)) * 72.0) + ftune);
    break;
    case 1:
     delayCounts = (32<<((adc->analogRead(Delay_counts_pin,ADC_0))>>9))-1;
    break;
    case 2:
     delayFeedback = adc->analogRead(Delay_feedback_pin);
    break;
    case 3:
    delayMix = adc->analogRead(Delay_mix_pin);
    break;
    case 4:
    ftune = ((int)(adc->analogRead(Fine_tune_pin)<<1) / 28);
    break;
    case 5:
    diffuseMix = adc->analogRead(Diffuse_mix_pin);
    diffuseMode = digitalReadFast(diffuse_button);
  }
}

