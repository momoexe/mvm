#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

bool load_asm(const char *filename, char **buffer)
{
    *buffer = NULL;

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

    long len = ftell(fp);
    if (len < 0)
    {
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to ftell file\n");
        return false;
    }
    rewind(fp);

    if (len == 0)
    {
        fclose(fp);
        *buffer = malloc(1);
        if (!*buffer)
        {
            fprintf(stderr, "ERROR: Unable to alloc mem\n");
            return false;
        }
        (*buffer)[0] = '\0';
        return true;
    }

    char *prog = malloc(len + 1);
    if (!prog)
    {
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to alloc mem\n");
        return false;
    }

    if (fread(prog, 1, len, fp) != (size_t)len)
    {
        free(prog);
        fclose(fp);
        fprintf(stderr, "ERROR: Unable to read file\n");
        return false;
    }

    prog[len] = '\0';
    fclose(fp);
    *buffer = prog;

    return true;
}

TokenArray init_token_array()
{
    TokenArray arr = {0};
    arr.capacity = 10;
    arr.items = malloc(arr.capacity * sizeof(Token));
    if (!arr.items)
    {
        fprintf(stderr, "ERROR: Unable to alloc mem\n");
        arr.capacity = 0;
    }

    return arr;
}

void tokenize(char *buffer, TokenArray *arr)
{
    if (!buffer || !arr)
        return;

    size_t l = 1;
    size_t c = 0;
    size_t i = 0;
    size_t len = strlen(buffer);

    while (i < len)
    {
        char ch = buffer[i];
        if (ch == '\n')
        {
            l++;
            c = 0;
            i++;
            continue;
        }
        else if (isalpha(ch))
        {
            size_t tok_c = c;
            char *text = read_word(buffer, &i);
            if (!text)
                return;
            c += strlen(text);

            TokenType type = get_token_type(text);
            Token tok = init_token(type, text, l, tok_c);
            push_token(tok, arr);
            continue;
        }
        else if (isdigit(ch))
        {
            size_t tok_c = c;
            char *text = read_number(buffer, &i);
            if (!text)
                return;
            c += strlen(text);

            TokenType type = get_token_type(text);
            Token tok = init_token(type, text, l, tok_c);
            push_token(tok, arr);
            continue;
        }
        c++;
        i++;
    }
}

char *read_word(char *buffer, size_t *idx)
{
    size_t start = *idx;
    while (isalpha(buffer[*idx]))
    {
        (*idx)++;
    }

    size_t len = *idx - start;
    char *word = malloc(len + 1);
    if (!word)
    {
        fprintf(stderr, "ERROR: Unable to alloc mem\n");
        return NULL;
    }
    word[len] = '\0';
    memcpy(word, &buffer[start], len);
    return word;
}

char *read_number(char *buffer, size_t *idx)
{
    size_t start = *idx;
    while (isdigit(buffer[*idx]))
    {
        (*idx)++;
    }

    size_t len = *idx - start;
    char *num = malloc(len + 1);
    if (!num)
    {
        fprintf(stderr, "ERROR: Unable to alloc mem\n");
        return NULL;
    }
    num[len] = '\0';
    memcpy(num, &buffer[start], len);
    return num;
}

void push_token(Token token, TokenArray *arr)
{
    if (arr->size >= arr->capacity)
    {
        arr->capacity = arr->capacity * 2;
        Token *tmp = realloc(arr->items, arr->capacity * sizeof(Token));
        if (!tmp)
        {
            fprintf(stderr, "ERROR: Unable to alloc mem\n");
            arr->capacity = 0;
            return;
        }
        arr->items = tmp;
    }

    arr->items[arr->size++] = token;
}

Token init_token(TokenType type, char *text, size_t line, size_t character)
{
    return (Token){type, text, line, character};
}

TokenType get_token_type(char *text)
{
    if (strcmp(text, "nop") == 0)
    {
        return INST_NOP;
    }
    else if (strcmp(text, "halt") == 0)
    {
        return INST_HALT;
    }
    else if (strcmp(text, "push") == 0)
    {
        return INST_PUSH;
    }
    else if (strcmp(text, "pop") == 0)
    {
        return INST_POP;
    }
    else if (strcmp(text, "dup") == 0)
    {
        return INST_DUP;
    }
    else if (strcmp(text, "swap") == 0)
    {
        return INST_SWAP;
    }
    else if (strcmp(text, "add") == 0)
    {
        return INST_ADD;
    }
    else if (strcmp(text, "sub") == 0)
    {
        return INST_SUB;
    }
    else if (strcmp(text, "mul") == 0)
    {
        return INST_MUL;
    }
    else if (strcmp(text, "div") == 0)
    {
        return INST_DIV;
    }
    else if (strcmp(text, "mod") == 0)
    {
        return INST_MOD;
    }
    else if (strcmp(text, "cmpe") == 0)
    {
        return INST_CMPE;
    }
    else if (strcmp(text, "cmpne") == 0)
    {
        return INST_CMPNE;
    }
    else if (strcmp(text, "cmpg") == 0)
    {
        return INST_CMPG;
    }
    else if (strcmp(text, "cmpge") == 0)
    {
        return INST_CMPGE;
    }
    else if (strcmp(text, "cmpl") == 0)
    {
        return INST_CMPL;
    }
    else if (strcmp(text, "cmple") == 0)
    {
        return INST_CMPLE;
    }
    else if (strcmp(text, "jmp") == 0)
    {
        return INST_JMP;
    }
    else if (strcmp(text, "jz") == 0)
    {
        return INST_JZ;
    }
    else if (strcmp(text, "jnz") == 0)
    {
        return INST_JNZ;
    }
    else if (isdigit(text[0]))
    {
        bool isNumber = true;

        for (size_t i = 0; i < strlen(text) && isNumber; i++)
        {
            if (!isdigit(text[i]))
                isNumber = false;
        }
        if (isNumber)
        {
            return CONST_NUMBER;
        }
        return TYPE_UNKNOWN;
    }
    else
    {
        return TYPE_UNKNOWN;
    }
}

const char *token_type_as_str(TokenType type)
{
    switch (type)
    {
    case INST_NOP:
        return "INST_NOP";
    case INST_HALT:
        return "INST_HALT";

    case INST_PUSH:
        return "INST_PUSH";
    case INST_POP:
        return "INST_POP";
    case INST_DUP:
        return "INST_DUP";
    case INST_SWAP:
        return "INST_SWAP";

    case INST_ADD:
        return "INST_ADD";
    case INST_SUB:
        return "INST_SUB";
    case INST_MUL:
        return "INST_MUL";
    case INST_DIV:
        return "INST_DIV";
    case INST_MOD:
        return "INST_MOD";

    case INST_CMPE:
        return "INST_CMPE";
    case INST_CMPNE:
        return "INST_CMPNE";
    case INST_CMPG:
        return "INST_CMPG";
    case INST_CMPGE:
        return "INST_CMPGE";
    case INST_CMPL:
        return "INST_CMPL";
    case INST_CMPLE:
        return "INST_CMPLE";

    case INST_JMP:
        return "INST_JMP";
    case INST_JZ:
        return "INST_JZ";
    case INST_JNZ:
        return "INST_JNZ";
    case CONST_NUMBER:
        return "CONST_NUMBER";
    case TYPE_UNKNOWN:
        return "TYPE_UNKNOWN";
    }
    return "";
}