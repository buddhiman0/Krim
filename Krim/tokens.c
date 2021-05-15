#include "tokens.h"
#include <stdlib.h>

// Initilize a token
token_T* init_token(int type, char* value)
{
    // create a token variable
    token_T* token = calloc(1, sizeof(struct tokens_struct));
    
    // Add a few params
    token->type = type;
    token->value = value;

    
    return token;
}
