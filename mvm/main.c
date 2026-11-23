#include <stdio.h>
#include <stdlib.h>

#include "mvm.h"

int main()
{
    Mvm mvm = {0};

    if (!load_prog_from_file(&mvm, "test.mvm"))
        return 1;

    while (mvm.ip < mvm.program_size && !mvm.isHalted)
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