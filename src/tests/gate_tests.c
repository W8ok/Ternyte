// tests/gate_tests.c
#include <stdio.h>

#include "../types.h"
#include "../gates/logic_binary.h"
#include "../gates/logic_ternary.h"

void binary_gate_testing(){
  
  // Terrible testing code dont question it

  printf("\nNOT:\n");
  for(int i = 0; i<=1; i++){
    bit result = gate_not(i);
    printf("NOT %d = %d\n", i, result);
  }
  
  printf("\nAND:\n");
  for(int i = 0; i<=1; i++){
    for(int j = 0; j<=1; j++){
      bit result = gate_and(i, j);
      printf("%d AND %d = %d\n", i, j, result);
    }
  }
  printf("\nNAND:\n");
  for(int i = 0; i<=1; i++){
    for(int j = 0; j<=1; j++){
      bit result = gate_nand(i, j);
      printf("%d NAND %d = %d\n", i, j, result);
    }
  }

  printf("\nOR:\n");
  for(int i = 0; i<=1; i++){
    for(int j = 0; j<=1; j++){
      bit result = gate_or(i, j);
      printf("%d OR %d = %d\n", i, j, result);
    }
  }

  printf("\nNOR:\n");
  for(int i = 0; i<=1; i++){
    for(int j = 0; j<=1; j++){
      bit result = gate_nor(i, j);
      printf("%d NOR %d = %d\n", i, j, result);
    }
  }

  printf("\nXOR:\n");
  for(int i = 0; i<=1; i++){
    for(int j = 0; j<=1; j++){
      bit result = gate_xor(i, j);
      printf("%d XOR %d = %d\n", i, j, result);
    }
  }

  printf("\nXNOR:\n");
  for(int i = 0; i<=1; i++){
    for(int j = 0; j<=1; j++){
      bit result = gate_xnor(i, j);
      printf("%d XNOR %d = %d\n", i, j, result);
    }
  }
}

void ternary_gate_testing(){
  
  // Again shush about my totally awesome coding

  printf("\nNEG:\n");
  for(int i = -1; i<=1; i++){
    trit result = gate_neg(i);
    printf("NEG %d = %d\n", i, result);
  }

  printf("\nMAX:\n");
  for(int i = -1; i<=1; i++){
    for(int j = -1; j<=1; j++){
      trit result = gate_max(i, j);
      printf("%d MAX %d = %d\n", i, j, result);
    }
  }
  printf("\nMIN:\n");
  for(int i = -1; i<=1; i++){
    for(int j = -1; j<=1; j++){
      trit result = gate_min(i, j);
      printf("%d MIN %d = %d\n", i, j, result);
    }
  }

  printf("\nCONSENSUS:\n");
  for(int i = -1; i<=1; i++){
    for(int j = -1; j<=1; j++){
      trit result = gate_consensus(i, j);
      printf("%d CONSENSUS %d = %d\n", i, j, result);
    }
  }
}

