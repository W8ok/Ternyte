// types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef bool bit;
typedef int8_t trit;

#define BIT_FALSE  ((bit)0)
#define BIT_TRUE   ((bit)1)

#define TRIT_MINUS ((trit)-1)
#define TRIT_ZERO  ((trit)0)
#define TRIT_PLUS  ((trit)1)

#endif
