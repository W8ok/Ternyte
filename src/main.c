// main.c
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h> 

#include "types.h"
#include "gates/binary.h"
#include "gates/ternary.h"

#include "tests/gate_tests.c"

int main(){
  binary_gate_testing();
  ternary_gate_testing();
  return 0;
}
