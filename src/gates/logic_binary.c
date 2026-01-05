// gates/logic_binary.c
#include <stdint.h>
#include <stdbool.h> 

#include "../types.h"

// Gate definitions
bit gate_not(bit a)         { return !a; }
bit gate_and(bit a, bit b)  { return a && b; }
bit gate_nand(bit a, bit b) { return !(a && b); }
bit gate_or(bit a, bit b)   { return a || b; }
bit gate_nor(bit a, bit b)  { return !(a || b); }
bit gate_xor(bit a, bit b)  { return a != b; }
bit gate_xnor(bit a, bit b) { return a == b; }
