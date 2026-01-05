// gates/logic_binary.h
#ifndef LOGIC_BINARY_H
#define LOGIC_BINARY_H

#include "../types.h"

bit gate_not(bit a);
bit gate_and(bit a, bit b);
bit gate_nand(bit a, bit b);
bit gate_or(bit a, bit b);
bit gate_nor(bit a, bit b);
bit gate_xor(bit a, bit b);
bit gate_xnor(bit a, bit b);

#endif
