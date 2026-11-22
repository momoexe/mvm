#include <stdio.h>
#include <stdlib.h>

#include "mvm.h"

int main()
{
    Mvm mvm = {0};

    Inst prog[] = {
        PUSH(42),
        PUSH(55),
        ADD(),
        PUSH(2),
        DIV(),
    };

    write_prog_to_file(prog, sizeof(prog) / sizeof(prog[0]), "test.mvm");
    load_prog_from_file(&mvm, "test.mvm");

    while (mvm.ip < mvm.program_size)
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

    free(mvm.program);
    return 0;
}