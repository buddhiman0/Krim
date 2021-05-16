//
//  ast.h
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#ifndef AST_H
#define AST_H
#include <stdlib.h>

typedef struct ast_struct
{
    enum {
        ast_variable_definition,
        ast_function_definition,
        ast_variable,
        ast_function_call,
        ast_string,
        ast_compound,
        ast_noop
    } type;

    struct scope_struct* scope;

    /* ast_variable_definition */
    char* variable_definition_variable_name;
    struct ast_struct* variable_definition_value;

    /* ast_function_definition */
    struct ast_struct* function_definition_body;
    char* function_definition_name;
    struct ast_struct** function_definition_args;
    size_t function_definition_args_size;

    /* ast_variable */
    char* variable_name;

    /* ast_function_call */
    char* function_call_name;
    struct ast_struct** function_call_arguments;
    size_t function_call_arguments_size;

    /* ast_string */
    char* string_value;

    /* ast_compound */
    struct ast_struct** compound_value;
    size_t compound_size;
} ast_T;

ast_T* init_ast(int type);
#endif
