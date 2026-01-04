// gates/ternary.h
#ifndef TERNARY_H
#define TERNARY_H

#include "../types.h"

trit gate_neg(trit a);
trit gate_min(trit a, trit b);
trit gate_max(trit a, trit b);
trit gate_consensus(trit a, trit b);

#endif 
