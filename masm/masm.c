#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main()
{
    TokenArray arr = init_token_array();

    char *buffer;
    if (!load_asm("file.masm", &buffer))
    {
        return 1;
    }
    tokenize(buffer, &arr);
    free(buffer);

    for (size_t i = 0; i < arr.size; i++)
    {
        printf("type: %s   ", token_type_as_str(arr.items[i].type));
        printf("line: %zu   ", arr.items[i].line);
        printf("char: %zu   ", arr.items[i].character);
        printf("text: %s    \n\n", arr.items[i].text);
    }

    for (size_t i = 0; i < arr.size; i++)
    {
        free(arr.items[i].text);
    }

    free(arr.items);
    return 0;
}