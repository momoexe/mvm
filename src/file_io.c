#include <stdio.h>
#include <stdlib.h>

#include "mvm.h"

void load_prog_from_mem(Mvm *mvm, Inst prog[], size_t program_size)
{
    mvm->program = malloc(program_size * sizeof(Inst));
    mvm->program_size = program_size;
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

    fwrite(program, sizeof(Inst), program_size, fp);
    fclose(fp);
}

void load_prog_from_file(Mvm *mvm, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Unable to read file\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    rewind(fp);

    mvm->program_size = (size_t)len / sizeof(Inst);
    mvm->program = malloc(mvm->program_size * sizeof(Inst));
    if (!mvm->program)
    {
        fclose(fp);
        mvm->program_size = 0;
        fprintf(stderr, "ERROR: Unable to allocate mem\n");
        return;
    }

    fread(mvm->program, sizeof(Inst), mvm->program_size, fp);
    fclose(fp);
}
