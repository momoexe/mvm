#include <stdio.h>
#include <stdlib.h>

#include "mvm.h"

bool load_prog_from_mem(Mvm *mvm, Inst prog[], size_t program_size)
{
    mvm->program = malloc(program_size * sizeof(Inst));
    if (!mvm->program)
        return false;
    mvm->program_size = program_size;
    for (size_t i = 0; i < program_size; i++)
    {
        mvm->program[i] = prog[i];
    }
    return true;
}

bool write_prog_to_file(Inst *program, size_t program_size, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Unable to open file\n");
        return false;
    }

    size_t written = fwrite(program, sizeof(Inst), program_size, fp);
    fclose(fp);

    if (written < program_size)
    {
        fprintf(stderr, "ERROR: Unable to write to file\n");
        return false;
    }

    return true;
}

bool load_prog_from_file(Mvm *mvm, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Unable to open file\n");
        return false;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to seek file\n");
        return false;
    }

    long len = ftell(fp); // Number of bytes in the file
    if (len < 0)
    {
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to ftell file\n");
        return false;
    }
    rewind(fp);

    if ((size_t)len % sizeof(Inst) != 0)
    {
        fclose(fp);
        fprintf(stderr, "ERROR: Invalid file size\n");
        return false;
    }

    size_t count = (size_t)len / sizeof(Inst); // Number of instructions in the file
    if (count == 0)
    {
        fclose(fp);
        mvm->program_size = 0;
        mvm->program = NULL;
        return true;
    }

    Inst *new_prog = malloc(count * sizeof(Inst));
    if (!new_prog)
    {
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to allocate mem\n");
        return false;
    }

    if (fread(new_prog, sizeof(Inst), count, fp) < count)
    {
        free(new_prog);
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to read file\n");
        return false;
    }

    fclose(fp);

    mvm->program_size = count;
    mvm->program = new_prog;

    return true;
}
