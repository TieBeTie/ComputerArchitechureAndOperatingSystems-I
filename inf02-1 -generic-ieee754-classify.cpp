/*
Реализуйте функцию с прототипом:

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

extern float_class_t
classify(double *value_ptr);
      
которая классифицирует специальные значения вещественного числа, на которое указывает value_ptr, в соответствии со стандартом IEEE 754.

При решении допускается использовать только побитовые операции, включая сдвиги.
*/
#include <stdio.h>
#include <stdint.h>

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

typedef union {
    double real_value;
    uint64_t uint_value;
} real_or_uint;

extern float_class_t
classify(double *value_ptr) {
    real_or_uint num;
    num.real_value = *value_ptr;
    uint64_t bits = num.uint_value;
    uint64_t plus_inf = (~(0ull) << 53) >> 1;
    uint64_t sign = !(bits >> 63);

    if (bits == 0llu) {
        return PlusZero;
    }
    if (bits == (1llu << 63)) {
        return MinusZero;
    }
    if (bits == plus_inf) {
        return PlusInf;
    }
    if (bits == (~(0llu) << 52)) {
        return MinusInf;
    }
    if ((bits & plus_inf) == plus_inf) {
        if (!(((bits << 1) >> 52) & 1)) {
            return SignalingNaN;
        } else {
            return QuietNaN;
        }
    }
    if (bits & plus_inf) {
        if (sign) {
            return PlusRegular;
        } else {
            return MinusRegular;
        }
    } else {
        if (sign) {
            return PlusDenormal;
        } else {
            return MinusDenormal;
        }
    }
}