//
//  tokens.h
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#ifndef TOKENS_H
#define TOKENS_H


typedef struct tokens_struct
{
    enum
    {
        token_identifier, // Identifier for 'vars, var names, declarations' etc.
        token_equals, // e.g x = a
        token_char, // 'c'
        token_include, // 'include'
        token_left_parenthesis, // '{'
        token_right_parenthesis, // '}'
        token_grave_accent //  '`' for include statments
    } type; // the name of our enim

    char* value; // The value
} token_T;

token_T* init_token(int type, char* value); // So we can create a token

#endif
