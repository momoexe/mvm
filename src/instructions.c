#include "mvm.h"

void mvm_push(Mvm *mvm, int val)
{
    mvm->stack[mvm->sp++] = val;
}

int mvm_pop(Mvm *mvm)
{
    int ret = mvm->stack[mvm->sp - 1];
    mvm->sp--;
    return ret;
}

void mvm_dup(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    mvm_push(mvm, a);
    mvm_push(mvm, a);
}

void mvm_swap(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    int b = mvm_pop(mvm);
    mvm_push(mvm, a);
    mvm_push(mvm, b);
}

void mvm_add(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    int b = mvm_pop(mvm);
    mvm_push(mvm, a + b);
}

void mvm_sub(Mvm *mvm)
{
    int rhs = mvm_pop(mvm);
    int lhs = mvm_pop(mvm);
    mvm_push(mvm, lhs - rhs);
}

void mvm_mul(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    int b = mvm_pop(mvm);
    mvm_push(mvm, a * b);
}

void mvm_div(Mvm *mvm)
{
    int rhs = mvm_pop(mvm);
    int lhs = mvm_pop(mvm);
    mvm_push(mvm, lhs / rhs);
}