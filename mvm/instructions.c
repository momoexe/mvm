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
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a - b);
}

void mvm_mul(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    int b = mvm_pop(mvm);
    mvm_push(mvm, a * b);
}

void mvm_div(Mvm *mvm)
{
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a / b);
}

void mvm_mod(Mvm *mvm)
{
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a % b);
}

void mvm_cmpe(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    int b = mvm_pop(mvm);
    mvm_push(mvm, a == b);
}

void mvm_cmpne(Mvm *mvm)
{
    int a = mvm_pop(mvm);
    int b = mvm_pop(mvm);
    mvm_push(mvm, a != b);
}

void mvm_cmpg(Mvm *mvm)
{
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a > b);
}

void mvm_cmpge(Mvm *mvm)
{
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a >= b);
}

void mvm_cmpl(Mvm *mvm)
{
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a < b);
}
void mvm_cmple(Mvm *mvm)
{
    int b = mvm_pop(mvm);
    int a = mvm_pop(mvm);
    mvm_push(mvm, a <= b);
}

void mvm_jmp(Mvm *mvm, size_t addr)
{
    mvm->ip = addr;
}
void mvm_jz(Mvm *mvm, size_t addr)
{
    if (mvm_pop(mvm) == 0)
        mvm->ip = addr;
    else
        mvm->ip++;
}
void mvm_jnz(Mvm *mvm, size_t addr)
{
    if (mvm_pop(mvm) != 0)
        mvm->ip = addr;
    else
        mvm->ip++;
}
