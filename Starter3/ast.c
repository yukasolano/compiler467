#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"

#define DEBUG_PRINT_TREE 0

node *ast = NULL;

node *ast_allocate(node_kind kind, ...) {
  va_list args;

  // make the node
  node *ast = (node *) malloc(sizeof(node));
  memset(ast, 0, sizeof *ast);
  ast->kind = kind;

  va_start(args, kind); 

  switch(kind) {
  
  // ...

  case SCOPE_NODE:
    ast->scope.declarations = va_arg(args, node *);
    ast->scope.statements = va_arg(args, node *);
    break; 

  case NESTED_SCOPE_NODE:
    break;  

  case DECLARATIONS_NODE: 
    ast->declarations.declarations = va_arg(args, node *);
    ast->declarations.declaration = va_arg(args, node *); 
    break;

  case STATEMENT_NODE:
    ast->statement.statements = va_arg(args, node *);
    ast->statement.statement = va_arg(args, node *); 
    break;

  case DECLARATION_NODE: 
    ast->declaration.type = va_arg(args, node *);
    ast->declaration.id = va_arg(args, char*); 
    ast->declaration.expr = va_arg(args, node *);
    break;

  case IF_STATEMENT_NODE:
    ast->if_stmt.expr = va_arg(args, node *);
    ast->if_stmt.stmt1 = va_arg(args, node *); 
    ast->if_stmt.stmt2 = va_arg(args, node *);
    break;

  case ASSIGNMENT_NODE:
    ast->assignment.var = va_arg(args, node *);
    ast->assignment.expr = va_arg(args, node *); 
    break;

  case TYPE_NODE:
    ast->type = va_arg(args, int);
    break; 



  case CONSTRUCTOR_NODE: 
    ast->constructor.type = va_arg(args, node *);
    ast->constructor.args = va_arg(args, node *);
    break;

  case FUNCTION_NODE: 
    ast->function.args = va_arg(args, node *);
    break;      

  case BINARY_EXPRESSION_NODE:
    ast->binary_expr.op = va_arg(args, int);
    ast->binary_expr.left = va_arg(args, node *);
    ast->binary_expr.right = va_arg(args, node *);
    break;

  case UNARY_EXPRESSION_NODE:
    ast->unary_expr.op = va_arg(args, int);
    ast->unary_expr.right = va_arg(args, node *);
    break;

  case INT_NODE:
    ast->int_val = va_arg(args, int);
    break;
  case BOOL_NODE:
    ast->bool_val = va_arg(args, int);
    break;
  case FLOAT_NODE:
    ast->float_val = va_arg(args, float);
    break;

  case VAR_NODE:
    ast->variable = va_arg(args, node *);
    break;

  case EXPRESSION_NODE:
    ast->expression = va_arg(args, node *);
    break; 

  case IDENT_NODE:
    ast->identifier.id = va_arg(args, char*);
    ast->identifier.index = va_arg(args, int); 
  break;

  
  case ARGUMENTS_NODE:  
    ast->arguments.args = va_arg(args, node *);
    ast->arguments.expr = va_arg(args, node *);      
    break;


  // ...

  default: break;
  }

  va_end(args);

  return ast;
}

void ast_free(node *ast) {

}

void ast_print(node * ast) {

}
