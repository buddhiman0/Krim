//
//  token.c
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#include "token.h"
#include <stdlib.h>


token_T* init_token(int type, char* value)
{
    token_T* token = calloc(1, sizeof(struct token_struct));
    token->type = type;
    token->value = value;

    return token;
}
