# MVM

MVM is a small stack-based virtual machine written in C.

It executes fixed-size instruction structures containing an opcode and an optional integer operand. The machine provides stack operations, arithmetic and comparison instructions, control flow, and basic runtime error handling.

## Components

### MVM

The `mvm` executable loads a compiled program from `test.mvm`, executes it instruction by instruction, and prints the VM stack after each instruction.

### MASM

The `masm` executable reads an assembly source file named `file.masm`, tokenizes it, and writes the resulting instruction sequence to `test.mvm`.

## Build

Run the following command from the repository root:

```sh
./build.sh
```

This builds:

- `bin/mvm`: the virtual machine
- `bin/masm`: the assembly lexer and compiler

## Usage

Create a `file.masm` file in the repository root:

```text
push 10
push 3
add
halt
```

Compile the source and execute the generated program:

```sh
./bin/masm
./bin/mvm
```

## Instruction Set

The current instruction set includes:

- System: `NOP`, `HALT`
- Stack: `PUSH`, `POP`, `DUP`, `SWAP`
- Arithmetic: `ADD`, `SUB`, `MUL`, `DIV`, `MOD`
- Comparison: `CMPE`, `CMPNE`, `CMPG`, `CMPGE`, `CMPL`, `CMPLE`
- Control flow: `JMP`, `JZ`, `JNZ`
