//
//  token.h
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//



#ifndef TOKEN_H
#define TOKEN_H
typedef struct token_struct
{
    enum
    {
        token_identifier,
        token_equals,
        token_string,
        token_semicolon,
        token_left_paren,
        token_right_paren,
        token_right_brace,
        token_left_brace,
        token_comma,
        token_end_of_file
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif
