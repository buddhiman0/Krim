//
//  main.c
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#include <stdio.h>
#include "lexer.h"


int main(int argc, char* argv[])
{
    // Initilize the lexer
    lexer_T* lexer = init_lexer(
            "include `stdio.h` \n"
            "var name = \"Krim Programming Language\" \n"
            "print(name) \n"
        );
    
    // Create a token variable
    token_T* token = (void*)0;

    // Create a while loop
    while ((token = lexer_get_next_token(lexer)) != (void*)0)
    {
        // Print the token type and value
        printf("TOKEN(%d, %s)\n", token->type, token->value);
    }
    
    
    return 0;
}
