//
//  main.c
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "visitor.h"
#include "io.h"

#define MAX_LIMIT 20

int main(int argc, char* argv[])
{
    if (argc >= 2){
        for(int i = 1; i < argc; i++){
            int len = strlen(argv[i]);
            char* last_four = &argv[i][len-6];
                                lexer_T* lexer = init_lexer(
                    get_file_contents(argv[i])
                );
                parser_T* parser = init_parser(lexer);
                ast_T* root = parser_parse(parser, parser->scope);
                visitor_T* visitor = init_visitor();
                visitor_visit(visitor, root);
        }
    }
    else {
        printf("Welcome to the Krim Language v. 0.3!\n");
        printf("Usage:\n kk <filename>\n");
    }
    return 0;
}
