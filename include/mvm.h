#ifndef MVM_H
#define MVM_H

#include <stddef.h>

#define STACK_CAPACITY 1024
#define PROGRAM_CAPACITY 1024

typedef enum
{
    ERR_STACK_OVERFLOW,
    ERR_STACK_UNDERFLOW,
    ERR_ILLEGAL_INST,
    ERR_MATH_ERROR,
    ERR_OK,

} Err;

typedef enum
{
    // STACK
    INST_NOP,
    INST_PUSH,
    INST_POP,
    INST_DUP,
    INST_SWAP,

    // MATH
    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_DIV,

} InstType;

typedef struct
{
    InstType type;
    int operand;
} Inst;

typedef struct
{
    int stack[STACK_CAPACITY];
    size_t sp;

    Inst program[PROGRAM_CAPACITY];
    size_t ip;

} Mvm;

// OP FUNC

void mvm_push(Mvm *mvm, int val);
int mvm_pop(Mvm *mvm);
void mvm_dup(Mvm *mvm);
void mvm_swap(Mvm *mvm);
void mvm_add(Mvm *mvm);
void mvm_sub(Mvm *mvm);
void mvm_mul(Mvm *mvm);
void mvm_div(Mvm *mvm);

void load_prog_from_mem(Mvm *mvm, Inst prog[], size_t program_size);

Err mvm_execute_inst(Mvm *mvm, Inst inst);
void mvm_dump_stack(Mvm *mvm);

char *err_as_str(Err err);

#endif