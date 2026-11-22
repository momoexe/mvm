#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mvm.h"

#define NOP() \
    {.type = INST_NOP}

#define PUSH(value) \
    {.type = INST_PUSH, .operand = value}

#define POP() \
    {.type = INST_POP}

#define DUP() \
    {.type = INST_DUP}

#define SWAP() \
    {.type = INST_SWAP}

#define ADD() \
    {.type = INST_ADD}

#define SUB() \
    {.type = INST_SUB}

#define MUL() \
    {.type = INST_MUL}

#define DIV() \
    {.type = INST_DIV}

int main()
{
    Mvm mvm = {0};

    Inst prog[] = {
        PUSH(42),
        PUSH(55),
        ADD(),
    };

    write_prog_to_file(prog, sizeof(prog) / sizeof(prog[0]), "test.mvm");
    size_t program_size = load_prog_from_file(&mvm, "test.mvm");

    while (mvm.ip < program_size)
    {
        Inst inst = mvm.program[mvm.ip];
        Err err = mvm_execute_inst(&mvm, inst);
        mvm_dump_stack(&mvm);

        if (err != ERR_OK)
        {
            fprintf(stderr, "ERROR: %s\n", err_as_str(err));
            exit(1);
        }
    }

    return 0;
}

char *err_as_str(Err err)
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
    default:
        assert(0 && "UNREACH");
    }
}

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
        if (mvm->stack[mvm->sp - 2] == 0)
            return ERR_MATH_ERROR;
        mvm_div(mvm);
        mvm->ip++;
        break;

    default:
        return ERR_ILLEGAL_INST;
    }

    return ERR_OK;
}

void load_prog_from_mem(Mvm *mvm, Inst prog[], size_t program_size)
{
    for (size_t i = 0; i < program_size; i++)
    {
        mvm->program[i] = prog[i];
    }
}

void write_prog_to_file(Inst *program, size_t program_size, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Unable to open file\n");
        exit(1);
    }

    fwrite(program, sizeof(program[0]), program_size, fp);
    fclose(fp);
}

size_t load_prog_from_file(Mvm *mvm, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Unable to read file\n");
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    rewind(fp);

    fread(mvm->program, sizeof(Inst), len / sizeof(Inst), fp);
    fclose(fp);

    return len / sizeof(Inst);
}

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
    mvm_push(mvm, mvm_pop(mvm) + mvm_pop(mvm));
}

void mvm_sub(Mvm *mvm)
{
    mvm_push(mvm, mvm_pop(mvm) - mvm_pop(mvm));
}

void mvm_mul(Mvm *mvm)
{
    mvm_push(mvm, mvm_pop(mvm) * mvm_pop(mvm));
}

void mvm_div(Mvm *mvm)
{
    mvm_push(mvm, mvm_pop(mvm) / mvm_pop(mvm));
}