#ifndef LEXER_H
#define LEXER_H

#include "tokens.h" // include the tokens.h file


// We will create a struct to store the current state of the lexer
typedef struct LEXER_STRUCT {
    char c; // Current character the lexer is in
    unsigned int i; // Index
    char* contents; // The contents of the file
    
} lexer_T; // The name of our struct

lexer_T* init_lexer(char* contents); // Initilize our lexer

void lexer_advance(lexer_T* lexer); // Move the current char to the next one, if it is the last char, it will not be called

void lexer_skip_whitespace(lexer_T* lexer); // Skip the whitespace in the compiler

token_T* lexer_get_next_token(lexer_T* lexer); // Get to the next token in the contents

token_T* lexer_collect_string(lexer_T* lexer); // Get the contents inside of a string in the code

token_T* lexer_collect_include_string(lexer_T* lexer); // Get the files inside the include statment


token_T* lexer_collect_id(lexer_T* lexer); // Collect the identifier of the token

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token); // Go to the next char with a token

char* lexer_get_current_char_as_string(lexer_T* lexer); // turn the 'char c' variable into a string

#endif /* LEXER_H */
