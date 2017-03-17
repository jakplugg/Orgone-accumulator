static inline float fastpow2(float p) __attribute__((always_inline, unused));
static inline float
fastpow2 (float p)

{
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
