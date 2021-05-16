//
//  visitor.c
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#include "visitor.h"
#include "scope.h"
#include <stdio.h>
#include <string.h>


static ast_T* builtin_function_print(visitor_T* visitor, ast_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        ast_T* visited_ast = visitor_visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case ast_string: printf("%s\n", visited_ast->string_value); break;
            default: printf("%p\n", visited_ast); break;
        }
    }

    return init_ast(ast_noop);
}

static ast_T* builtin_function_exit(visitor_T* visitor, ast_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        ast_T* visited_ast = visitor_visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case ast_noop: printf("You exited\n"); exit(0); break;
            default: printf("%p\n", visited_ast); break;
        }
    }

    return init_ast(ast_noop);
}

static ast_T* builtin_function_clear(visitor_T* visitor, ast_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        ast_T* visited_ast = visitor_visit(visitor, args[i]);
        switch (visited_ast->type)
        {
                
            case ast_noop: system("clear"); break;
            default: printf("%p\n", visited_ast); break;
        }
    }

    return init_ast(ast_noop);
}

visitor_T* init_visitor()
{
    visitor_T* visitor = calloc(1, sizeof(struct visitor_struct));

    return visitor;
}

ast_T* visitor_visit(visitor_T* visitor, ast_T* node)
{
    switch (node->type)
    {
        case ast_variable_definition: return visitor_visit_variable_definition(visitor, node); break;
        case ast_function_definition: return visitor_visit_function_definition(visitor, node); break;
        case ast_variable: return visitor_visit_variable(visitor, node); break;
        case ast_function_call: return visitor_visit_function_call(visitor, node); break;
        case ast_string: return visitor_visit_string(visitor, node); break;
        case ast_compound: return visitor_visit_compound(visitor, node); break;
        case ast_noop: return node; break;
    }

    printf("Uncaught statement of type `%d`\n", node->type);
    exit(1);

    return init_ast(ast_noop);
}

ast_T* visitor_visit_variable_definition(visitor_T* visitor, ast_T* node)
{
    scope_add_variable_definition(
        node->scope,
        node        
    ); 

    return node;
}

ast_T* visitor_visit_function_definition(visitor_T* visitor, ast_T* node)
{
    scope_add_function_definition(
        node->scope,
        node        
    );

    return node;
}

ast_T* visitor_visit_variable(visitor_T* visitor, ast_T* node)
{
    ast_T* vdef = scope_get_variable_definition(
        node->scope,
        node->variable_name
    );
    
    if (vdef != (void*) 0)
        return visitor_visit(visitor, vdef->variable_definition_value);

    printf("Undefined variable `%s`\n", node->variable_name);
    exit(1);
}

ast_T* visitor_visit_function_call(visitor_T* visitor, ast_T* node)
{
    if (strcmp(node->function_call_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    if (strcmp(node->function_call_name, "exit") == 0)
    {
        return builtin_function_exit(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    if (strcmp(node->function_call_name, "clear") == 0)
    {
        return builtin_function_clear(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    ast_T* fdef = scope_get_function_definition(
        node->scope,
        node->function_call_name
    );

    if (fdef == (void*)0)
    {
        printf("Undefined method `%s`\n", node->function_call_name);
        exit(1);
    }

    for (int i = 0; i < (int) node->function_call_arguments_size; i++)
    {
        // grab the variable from the function definition arguments
        ast_T* ast_var = (ast_T*) fdef->function_definition_args[i];

        // grab the value from the function call arguments
        ast_T* ast_value = (ast_T*) node->function_call_arguments[i];

        // create a new variable definition with the value of the argument
        // in the function call.
        ast_T* ast_vardef = init_ast(ast_variable_definition);
        ast_vardef->variable_definition_value = ast_value;

        // copy the name from the function definition argument into the new
        // variable definition
        ast_vardef->variable_definition_variable_name = (char*) calloc(strlen(ast_var->variable_name) + 1, sizeof(char));
        strcpy(ast_vardef->variable_definition_variable_name, ast_var->variable_name);

        // push our variable definition into the function body scope.
        scope_add_variable_definition(fdef->function_definition_body->scope, ast_vardef);
    }
    
    return visitor_visit(visitor, fdef->function_definition_body);
}

ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node)
{
    return node;
}

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node)
{
    for (int i = 0; i < node->compound_size; i++)
    {
        visitor_visit(visitor, node->compound_value[i]);
    }

    return init_ast(ast_noop);
}
