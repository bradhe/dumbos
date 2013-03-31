#pragma once

typedef unsigned int COUNTER;
typedef unsigned char BYTE;

/* Boolean types */
typedef int BOOL;

#define UNUSED(expr) do { (void)(expr); } while (0)

#define TRUE            (BOOL)1
#define FALSE           (BOOL)0
#define NULL            0

#define AS_BOOL(x)      x ? TRUE : FALSE
#define NOT_NULL(x)     x != NULL
