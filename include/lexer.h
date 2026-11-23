#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    TOKEN_INST_NOP,
    TOKEN_INST_HALT,

    TOKEN_INST_PUSH,
    TOKEN_INST_POP,
    TOKEN_INST_DUP,
    TOKEN_INST_SWAP,

    TOKEN_INST_ADD,
    TOKEN_INST_SUB,
    TOKEN_INST_MUL,
    TOKEN_INST_DIV,
    TOKEN_INST_MOD,

    TOKEN_INST_CMPE,
    TOKEN_INST_CMPNE,
    TOKEN_INST_CMPG,
    TOKEN_INST_CMPGE,
    TOKEN_INST_CMPL,
    TOKEN_INST_CMPLE,

    TOKEN_INST_JMP,
    TOKEN_INST_JZ,
    TOKEN_INST_JNZ,
    TOKEN_CONST_NUMBER,
    TOKEN_TYPE_UNKNOWN,
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