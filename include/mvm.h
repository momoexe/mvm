#ifndef MVM_H
#define MVM_H

#include <stddef.h>
#include <stdbool.h>

#define STACK_CAPACITY 1024

// Macros for constructing instructions
#define NOP() \
    {.type = INST_NOP}

#define HALT() \
    {.type = INST_HALT}

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

#define MOD() \
    {.type = INST_MOD}

#define CMPE() \
    {.type = INST_CMPE}

#define CMPNE() \
    {.type = INST_CMPNE}

#define CMPL() \
    {.type = INST_CMPL}

#define CMPLE() \
    {.type = INST_CMPLE}

#define CMPG() \
    {.type = INST_CMPG}

#define CMPGE() \
    {.type = INST_CMPGE}

#define JMP(addr) \
    {.type = INST_JMP, .operand = addr}

#define JZ(addr) \
    {.type = INST_JZ, .operand = addr}

#define JNZ(addr) \
    {.type = INST_JNZ, .operand = addr}

// Runtime error types
typedef enum
{
    ERR_STACK_OVERFLOW,
    ERR_STACK_UNDERFLOW,
    ERR_ILLEGAL_INST,
    ERR_MATH_ERROR,
    ERR_ILLEGAL_ACCESS,
    ERR_OK,

} Err;

// VM instruction types
typedef enum
{
    // SYS
    INST_NOP,
    INST_HALT,

    // STACK
    INST_PUSH,
    INST_POP,
    INST_DUP,
    INST_SWAP,

    // MATH
    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_DIV,
    INST_MOD,

    // LOGIC
    INST_CMPE,
    INST_CMPNE,
    INST_CMPG,
    INST_CMPGE,
    INST_CMPL,
    INST_CMPLE,

    // FLOW
    INST_JMP,
    INST_JZ,
    INST_JNZ,

} InstType;

// A VM instruction and its optional integer operand
typedef struct
{
    InstType type;
    int operand;
} Inst;

// Virtual Machine struct
typedef struct
{
    int stack[STACK_CAPACITY];
    size_t sp; // stack pointer

    Inst *program; // array that contains the program ( array of instructions )
    size_t program_size;
    size_t ip; // Index of the next instruction to execute

    bool isHalted; // stop the machine
} Mvm;

// Functions that execute VM instructions
void mvm_push(Mvm *mvm, int val);
int mvm_pop(Mvm *mvm);
void mvm_dup(Mvm *mvm);
void mvm_swap(Mvm *mvm);

void mvm_add(Mvm *mvm);
void mvm_sub(Mvm *mvm);
void mvm_mul(Mvm *mvm);
void mvm_div(Mvm *mvm);
void mvm_mod(Mvm *mvm);

void mvm_cmpe(Mvm *mvm);
void mvm_cmpne(Mvm *mvm);
void mvm_cmpg(Mvm *mvm);
void mvm_cmpge(Mvm *mvm);
void mvm_cmpl(Mvm *mvm);
void mvm_cmple(Mvm *mvm);

void mvm_jmp(Mvm *mvm, size_t addr);
void mvm_jz(Mvm *mvm, size_t addr);
void mvm_jnz(Mvm *mvm, size_t addr);

// Writes the program as a binary instruction array to a file
bool write_prog_to_file(Inst *program, size_t program_size, const char *filename);

// Copies an instruction array into the VM
bool load_prog_from_mem(Mvm *mvm, Inst prog[], size_t program_size);

// Loads binary instructions from a file into the VM
bool load_prog_from_file(Mvm *mvm, const char *filename);

// Decodes and executes an instruction
Err mvm_execute_inst(Mvm *mvm, Inst inst);

// Utils
void mvm_dump_stack(Mvm *mvm);
const char *err_as_str(Err err);

#endif