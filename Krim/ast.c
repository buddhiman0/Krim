//
//  ast.c
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#include "ast.h"


ast_T* init_ast(int type)
{
    ast_T* ast = calloc(1, sizeof(struct ast_struct));
    ast->type = type;

    ast->scope = (void*) 0;

    /* ast_variable_definition */
    ast->variable_definition_variable_name = (void*) 0;
    ast->variable_definition_value = (void*) 0;

    /* ast_function_definition */
    ast->function_definition_body = (void*) 0;
    ast->function_definition_name = (void*) 0;
    ast->function_definition_args = (void*) 0;
    ast->function_definition_args_size = 0;

    /* ast_variable */
    ast->variable_name = (void*) 0;

    /* ast_function_call */
    ast->function_call_name = (void*) 0;
    ast->function_call_arguments = (void*) 0;
    ast->function_call_arguments_size = 0;

    /* ast_string */
    ast->string_value = (void*) 0;

    /* ast_compound */
    ast->compound_value = (void*) 0;
    ast->compound_size = 0;

    return ast;
}
