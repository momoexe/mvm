#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    INST_NOP,
    INST_HALT,

    INST_PUSH,
    INST_POP,
    INST_DUP,
    INST_SWAP,

    INST_ADD,
    INST_SUB,
    INST_MUL,
    INST_DIV,
    INST_MOD,

    INST_CMPE,
    INST_CMPNE,
    INST_CMPG,
    INST_CMPGE,
    INST_CMPL,
    INST_CMPLE,

    INST_JMP,
    INST_JZ,
    INST_JNZ,
    CONST_NUMBER,
    TYPE_UNKNOWN,
} TokenType;

const char *token_type_as_str(TokenType type);

typedef struct
{
    TokenType type;
    char *text;
    size_t line;
    size_t character;
} Token;

typedef struct
{
    Token *items;
    size_t size;
    size_t capacity;
} TokenArray;

char *read_word(char *buffer, size_t *i);
char *read_number(char *buffer, size_t *i);
bool load_asm(const char *filename, char **buffer);
TokenArray init_token_array();
void push_token(Token token, TokenArray *arr);

Token init_token(TokenType type,
                 char *text,
                 size_t line,
                 size_t character);

TokenType get_token_type(char *text);
void tokenize(char *buffer, TokenArray *arr);
#endif