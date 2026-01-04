// gates/binary.h
#ifndef BINARY_H
#define BINARY_H

#include "../types.h"

bit gate_not(bit a);
bit gate_and(bit a, bit b);
bit gate_nand(bit a, bit b);
bit gate_or(bit a, bit b);
bit gate_nor(bit a, bit b);
bit gate_xor(bit a, bit b);
bit gate_xnor(bit a, bit b);

#endif
