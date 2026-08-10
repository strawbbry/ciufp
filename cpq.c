uint8_t n = 2;
uint8_t x = 3;
uint8_t val = 1;

// clear n bits @ pos x 
uint32_t pin &= ~(((2 ** n) - 1) << x);
// set val @ pos x 
uint32_t pin |= val << x;

// infinite loop
for (;;) (void) 0;

// delay loop 
static inline void spin(volatile uint32_t count) {
    while (count--) (void) 0;  // nop 
}