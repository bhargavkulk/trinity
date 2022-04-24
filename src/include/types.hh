#ifndef TYPES_HH
#define TYPES_HH

#include "common.hh"

enum class DataType { INT, STR, BLK };

struct ExprType {
    DataType type;
    union {
        int64_t int_val;
        char *str_val;
    } as;
};

#endif /* TYPES_HH */