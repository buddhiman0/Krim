//
//  parser.c
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#include "parser.h"
#include "scope.h"
#include <stdio.h>
#include <string.h>


parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser = calloc(1, sizeof(struct parser_struct));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;

    parser->scope = init_scope();

    return parser;
}

void parser_eat(parser_T* parser, int token_type)
{
    if (parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else
    {
        printf(
            "Unexpected token `%s`, with type %d",
            parser->current_token->value,
            parser->current_token->type
        );
        exit(1);
    }
}

ast_T* parser_parse(parser_T* parser, scope_T* scope)
{
    return parser_parse_statements(parser, scope);
}

ast_T* parser_parse_statement(parser_T* parser, scope_T* scope)
{
    switch (parser->current_token->type)
    {
        case token_identifier: return parser_parse_id(parser, scope);
    }

    return init_ast(ast_noop);
}

ast_T* parser_parse_statements(parser_T* parser, scope_T* scope)
{
    ast_T* compound = init_ast(ast_compound);
    compound->scope = scope;
    compound->compound_value = calloc(1, sizeof(struct ast_struct*));

    ast_T* ast_statement = parser_parse_statement(parser, scope);
    ast_statement->scope = scope;
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;

    while (parser->current_token->type == token_semicolon)
    {
        parser_eat(parser, token_semicolon);

        ast_T* ast_statement = parser_parse_statement(parser, scope);

        if (ast_statement)
        {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size * sizeof(struct ast_struct*)
            );
            compound->compound_value[compound->compound_size-1] = ast_statement;
        }
    }

    return compound;
}

ast_T* parser_parse_expr(parser_T* parser, scope_T* scope)
{
    switch (parser->current_token->type)
    {
        case token_string: return parser_parse_string(parser, scope);
        case token_identifier: return parser_parse_id(parser, scope);
    }

    return init_ast(ast_noop);
}

ast_T* parser_parse_factor(parser_T* parser, scope_T* scope)
{
}

ast_T* parser_parse_term(parser_T* parser, scope_T* scope)
{
}

ast_T* parser_parse_function_call(parser_T* parser, scope_T* scope)
{
    ast_T* function_call = init_ast(ast_function_call);

    function_call->function_call_name = parser->prev_token->value;
    parser_eat(parser, token_left_paren); 

    function_call->function_call_arguments = calloc(1, sizeof(struct ast_struct*));

    ast_T* ast_expr = parser_parse_expr(parser, scope);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size += 1;

    while (parser->current_token->type == token_comma)
    {
        parser_eat(parser, token_comma);

        ast_T* ast_expr = parser_parse_expr(parser, scope);
        function_call->function_call_arguments_size += 1;
        function_call->function_call_arguments = realloc(
            function_call->function_call_arguments,
            function_call->function_call_arguments_size * sizeof(struct ast_struct*)
        );
        function_call->function_call_arguments[function_call->function_call_arguments_size-1] = ast_expr;
    }
    parser_eat(parser, token_right_paren);

    function_call->scope = scope;

    return function_call;
}

ast_T* parser_parse_variable_definition(parser_T* parser, scope_T* scope)
{
    parser_eat(parser, token_identifier); // var
    char* variable_definition_variable_name = parser->current_token->value;
    parser_eat(parser, token_identifier); // var name
    parser_eat(parser, token_equals);
    ast_T* variable_definition_value = parser_parse_expr(parser, scope);

    ast_T* variable_definition = init_ast(ast_variable_definition);
    variable_definition->variable_definition_variable_name = variable_definition_variable_name;
    variable_definition->variable_definition_value = variable_definition_value;

    variable_definition->scope = scope;

    return variable_definition;
}

ast_T* parser_parse_function_definition(parser_T* parser, scope_T* scope)
{
    ast_T* ast = init_ast(ast_function_definition);
    parser_eat(parser, token_identifier); // function

    char* function_name = parser->current_token->value;
    ast->function_definition_name = calloc(
            strlen(function_name) + 1, sizeof(char)
    );
    strcpy(ast->function_definition_name, function_name);

    parser_eat(parser, token_identifier); // function name

    parser_eat(parser, token_left_paren);

    ast->function_definition_args =
        calloc(1, sizeof(struct ast_struct*));

    ast_T* arg = parser_parse_variable(parser, scope);
    ast->function_definition_args_size += 1;
    ast->function_definition_args[ast->function_definition_args_size-1] = arg;

    while (parser->current_token->type == token_comma)
    {
        parser_eat(parser, token_comma);

        ast->function_definition_args_size += 1;

        ast->function_definition_args =
            realloc(
                    ast->function_definition_args,
                    ast->function_definition_args_size * sizeof(struct ast_struct*)
                   );

        ast_T* arg = parser_parse_variable(parser, scope);
        ast->function_definition_args[ast->function_definition_args_size-1] = arg;
    }

    parser_eat(parser, token_right_paren);
    
    parser_eat(parser, token_left_brace);
    
    ast->function_definition_body = parser_parse_statements(parser, scope);

    parser_eat(parser, token_right_brace);

    ast->scope = scope;

    return ast;
}

ast_T* parser_parse_variable(parser_T* parser, scope_T* scope)
{
    char* token_value = parser->current_token->value;
    parser_eat(parser, token_identifier); // var name or function call name

    if (parser->current_token->type == token_left_paren)
        return parser_parse_function_call(parser, scope);

    ast_T* ast_variable_var = init_ast(ast_variable);
    ast_variable_var->variable_name = token_value;

    ast_variable_var->scope = scope;

    return ast_variable_var;
}

ast_T* parser_parse_string(parser_T* parser, scope_T* scope)
{
    ast_T* ast_string_var = init_ast(ast_string);
    ast_string_var->string_value = parser->current_token->value;

    parser_eat(parser, token_string);

    ast_string_var->scope = scope;

    return ast_string_var;
}

ast_T* parser_parse_id(parser_T* parser, scope_T* scope)
{
    if (strcmp(parser->current_token->value, "var") == 0)
    {
        return parser_parse_variable_definition(parser, scope);
    }
    else
    if (strcmp(parser->current_token->value, "func") == 0)
    {
        return parser_parse_function_definition(parser, scope);
    }
    else
    {
        return parser_parse_variable(parser, scope);
    }
}
