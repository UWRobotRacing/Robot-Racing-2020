#define DEBUG_BUILD

#ifdef DEBUG_BUILD
#  define DEBUG(x) Serial.print(x)
#else
#  define DEBUG(x) do {} while (0)
#endif
