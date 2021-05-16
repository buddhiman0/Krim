//
//  visitor.h
//  Krim
//
//  Created by Krim Developers on 2021-05-16.
//


#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"

typedef struct visitor_struct
{
} visitor_T;

visitor_T* init_visitor();

ast_T* visitor_visit(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_variable_definition(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_function_definition(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_variable(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_function_call(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node);
#endif
