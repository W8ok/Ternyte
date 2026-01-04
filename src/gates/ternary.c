// gates/ternary.c
#include <stdint.h>

#include "../types.h"

static int trit_index(trit t) { return t + 1; } // To not have any "magic" numbers in the trit table array indexing

// Gate lookup table... just easier for nonboolean logic
static const trit neg_table[3] = {
  TRIT_PLUS, TRIT_ZERO, TRIT_MINUS
};

static const trit min_table[3][3] = {
    {TRIT_MINUS, TRIT_MINUS, TRIT_MINUS},
    {TRIT_MINUS, TRIT_ZERO,  TRIT_ZERO},
    {TRIT_MINUS, TRIT_ZERO,  TRIT_PLUS}
};

static const trit max_table[3][3] = {
    {TRIT_MINUS, TRIT_ZERO,  TRIT_PLUS},
    {TRIT_ZERO,  TRIT_ZERO,  TRIT_PLUS},
    {TRIT_PLUS,  TRIT_PLUS,  TRIT_PLUS}
};

static const trit consensus_table[3][3] = {
    {TRIT_MINUS, TRIT_ZERO, TRIT_ZERO},
    {TRIT_ZERO,  TRIT_ZERO, TRIT_ZERO},
    {TRIT_ZERO,  TRIT_ZERO, TRIT_PLUS}
};

// Gate definitions
trit gate_neg(trit a)                 { return neg_table[trit_index(a)]; }
trit gate_min(trit a, trit b)         { return min_table[trit_index(a)][trit_index(b)]; }
trit gate_max(trit a, trit b)         { return max_table[trit_index(a)][trit_index(b)]; }
trit gate_consensus(trit a, trit b)   { return consensus_table[trit_index(a)][trit_index(b)]; }
