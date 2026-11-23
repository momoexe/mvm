#include "mvm.h"

const char *err_as_str(Err err)
{
    switch (err)
    {
    case ERR_STACK_OVERFLOW:
        return "ERR_STACK_OVERFLOW";
    case ERR_STACK_UNDERFLOW:
        return "ERR_STACK_UNDERFLOW";
    case ERR_ILLEGAL_INST:
        return "ERR_ILLEGAL_INST";
    case ERR_MATH_ERROR:
        return "ERR_MATH_ERROR";
    case ERR_OK:
        return "ERR_OK";
    case ERR_ILLEGAL_ACCESS:
        return "ERR_ILLEGAL_ACCESS";
    default:
        return "ERR_UNKNOWN";
    }
}