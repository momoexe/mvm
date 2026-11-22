#include <stdio.h>
#include <stdlib.h>

#include "mvm.h"

void mvm_dump_stack(Mvm *mvm)
{
    printf("STACK: \n");
    if (mvm->sp > 0)
    {
        for (size_t i = 0; i < mvm->sp; i++)
            printf("    %d\n", mvm->stack[i]);
    }
    else
        printf("    [empty]\n");
}

Err mvm_execute_inst(Mvm *mvm, Inst inst)
{
    switch (inst.type)
    {
    case INST_NOP:
        mvm->ip++;
        break;

    case INST_PUSH:
        if (mvm->sp >= STACK_CAPACITY)
            return ERR_STACK_OVERFLOW;
        mvm_push(mvm, inst.operand);
        mvm->ip++;
        break;

    case INST_POP:
        if (mvm->sp <= 0)
            return ERR_STACK_UNDERFLOW;
        mvm_pop(mvm);
        mvm->ip++;
        break;

    case INST_DUP:
        if (mvm->sp <= 0)
            return ERR_STACK_UNDERFLOW;

        if (mvm->sp >= STACK_CAPACITY)
            return ERR_STACK_OVERFLOW;

        mvm_dup(mvm);
        mvm->ip++;
        break;

    case INST_SWAP:
        if (mvm->sp < 2)
            return ERR_STACK_UNDERFLOW;
        mvm_swap(mvm);
        mvm->ip++;
        break;

    case INST_ADD:
        if (mvm->sp < 2)
            return ERR_STACK_UNDERFLOW;
        mvm_add(mvm);
        mvm->ip++;
        break;

    case INST_SUB:
        if (mvm->sp < 2)
            return ERR_STACK_UNDERFLOW;
        mvm_sub(mvm);
        mvm->ip++;
        break;
    case INST_MUL:
        if (mvm->sp < 2)
            return ERR_STACK_UNDERFLOW;
        mvm_mul(mvm);
        mvm->ip++;
        break;
    case INST_DIV:
        if (mvm->sp < 2)
            return ERR_STACK_UNDERFLOW;
        if (mvm->stack[mvm->sp - 1] == 0)
            return ERR_MATH_ERROR;
        mvm_div(mvm);
        mvm->ip++;
        break;

    default:
        return ERR_ILLEGAL_INST;
    }

    return ERR_OK;
}
