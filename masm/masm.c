#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "mvm.h"

int main()
{

    TokenArray arr = init_token_array();

    char *buffer;
    if (!load_asm("file.masm", &buffer))
    {
        return 1;
    }
    tokenize(buffer, &arr);

    Inst *program = malloc(arr.size * sizeof(Inst));
    if (!program)
    {
        fprintf(stderr, "Unable to alloc mem\n");
        return 1;
    }

    size_t i = 0;
    size_t program_idx = 0;
    while (i < arr.size)
    {
        int val;
        switch (arr.items[i].type)
        {
        case TOKEN_INST_NOP:
            program[program_idx] = (Inst)NOP();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_HALT:
            program[program_idx] = (Inst)HALT();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_POP:
            program[program_idx] = (Inst)POP();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_DUP:
            program[program_idx] = (Inst)DUP();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_SWAP:
            program[program_idx] = (Inst)SWAP();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_ADD:
            program[program_idx] = (Inst)ADD();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_SUB:
            program[program_idx] = (Inst)SUB();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_MUL:
            program[program_idx] = (Inst)MUL();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_DIV:
            program[program_idx] = (Inst)DIV();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_MOD:
            program[program_idx] = (Inst)MOD();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_CMPE:
            program[program_idx] = (Inst)CMPE();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_CMPNE:
            program[program_idx] = (Inst)CMPNE();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_CMPG:
            program[program_idx] = (Inst)CMPG();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_CMPGE:
            program[program_idx] = (Inst)CMPGE();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_CMPL:
            program[program_idx] = (Inst)CMPL();
            program_idx++;
            i++;
            break;
        case TOKEN_INST_CMPLE:
            program[program_idx] = (Inst)CMPLE();
            program_idx++;
            i++;
            break;

        case TOKEN_INST_PUSH:
            if (i < arr.size - 1 && arr.items[i + 1].type == TOKEN_CONST_NUMBER)
            {
                val = atoi(arr.items[i + 1].text);
                program[program_idx] = (Inst)PUSH(val);
                program_idx++;
                i += 2;
                break;
            }
            else
            {
                fprintf(stderr, "Error: no operand at ln %zu col %zu\n", arr.items[i].line, arr.items[i].character + strlen(arr.items[i].text) + 1);
                return 1;
            }
        case TOKEN_INST_JMP:
            if (i < arr.size - 1 && arr.items[i + 1].type == TOKEN_CONST_NUMBER)
            {
                val = atoi(arr.items[i + 1].text);
                program[program_idx] = (Inst)JMP(val);
                program_idx++;
                i += 2;
                break;
            }
            else
            {
                fprintf(stderr, "Error: no operand at ln %zu col %zu\n", arr.items[i].line, arr.items[i].character + strlen(arr.items[i].text) + 1);
                return 1;
            }
        case TOKEN_INST_JZ:
            if (i < arr.size - 1 && arr.items[i + 1].type == TOKEN_CONST_NUMBER)
            {
                val = atoi(arr.items[i + 1].text);
                program[program_idx] = (Inst)JZ(val);
                program_idx++;
                i += 2;
                break;
            }
            else
            {
                fprintf(stderr, "Error: no operand at ln %zu col %zu\n", arr.items[i].line, arr.items[i].character + strlen(arr.items[i].text) + 1);
                return 1;
            }
        case TOKEN_INST_JNZ:
            if (i < arr.size - 1 && arr.items[i + 1].type == TOKEN_CONST_NUMBER)
            {
                val = atoi(arr.items[i + 1].text);
                program[program_idx] = (Inst)JNZ(val);
                program_idx++;
                i += 2;
                break;
            }
            else
            {
                fprintf(stderr, "Error: no operand at ln %zu col %zu\n", arr.items[i].line, arr.items[i].character + strlen(arr.items[i].text) + 1);
                return 1;
            }
        case TOKEN_TYPE_UNKNOWN:
        case TOKEN_CONST_NUMBER:
            fprintf(stderr, "ERROR Ln %zu, Col %zu\n", arr.items[i].line, arr.items[i].character);
            return 1;
        }
    }
    if (!write_prog_to_file(program, program_idx, "test.mvm"))
    {
        fprintf(stderr, "ERROR: Unable to write to file\n");
        return 1;
    }

    // free
    free(buffer);
    for (size_t i = 0; i < arr.size; i++)
    {
        free(arr.items[i].text);
    }
    free(arr.items);
    free(program);

    return 0;
}

void debug_dump_arr(TokenArray arr)
{
    for (size_t i = 0; i < arr.size; i++)
    {
        printf("type: %s   ", token_type_as_str(arr.items[i].type));
        printf("line: %zu   ", arr.items[i].line);
        printf("char: %zu   ", arr.items[i].character);
        printf("text: %s    \n\n", arr.items[i].text);
    }
}