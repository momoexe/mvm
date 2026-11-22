#include <stdio.h>
#include <stdlib.h>

#include "mvm.h"

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
