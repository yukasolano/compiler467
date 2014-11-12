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

  case NESTED_SCOPE_NODE:
    ast->nested_scope = va_arg(args, node *);
    
    //DEBUG: after delete this print!!!
    ast_print(ast);
    break;

  case SCOPE_NODE:
    ast->scope.declarations = va_arg(args, node *);
    ast->scope.statements = va_arg(args, node *);    
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
    ast->type = va_arg(args, char*);
    break; 



  case CONSTRUCTOR_NODE: 
    ast->constructor.type = va_arg(args, node *);
    ast->constructor.args = va_arg(args, node *);
    break;

  case FUNCTION_NODE: 
    ast->function.args = va_arg(args, node *);
    break;      

  case BINARY_EXPRESSION_NODE:
    ast->binary_expr.op = va_arg(args, char*);
    ast->binary_expr.left = va_arg(args, node *);
    ast->binary_expr.right = va_arg(args, node *);
    break;

  case UNARY_EXPRESSION_NODE:
    ast->unary_expr.op = va_arg(args, char*);
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

  if(ast == NULL) return;

  switch (ast->kind){

    case NESTED_SCOPE_NODE:
      printf("NESTED_SCOPE_NODE\n");
      ast_print(ast->nested_scope);
      break;

    case SCOPE_NODE: 
      printf("SCOPE_NODE\n");
      ast_print(ast->scope.declarations);
      ast_print(ast->scope.statements);
      break;

    case DECLARATIONS_NODE:
      printf("DECLARATIONS_NODE\n");
      ast_print(ast->declarations.declarations);
      ast_print(ast->declarations.declaration); 
      break;

    case STATEMENT_NODE:
      printf("STATEMENT_NODE\n");     
      ast_print(ast->statement.statements);
      ast_print(ast->statement.statement); 
      break;   

    case DECLARATION_NODE: 
      printf("DECLARATION_NODE\n");
      ast_print(ast->declaration.type);
      printf("ID: %s\n", ast->declaration.id);
      ast_print(ast->declaration.expr); 
    break;

    case IF_STATEMENT_NODE:
      printf("IF_STATEMENT_NODE\n");
      ast_print(ast->if_stmt.expr);
      ast_print(ast->if_stmt.stmt1); 
      ast_print(ast->if_stmt.stmt2);
      break;

    case ASSIGNMENT_NODE:
      printf("ASSIGMENT_NODE\n");
      ast_print(ast->assignment.var);
      ast_print(ast->assignment.expr); 
    break;

    case TYPE_NODE:
      printf("TYPE_NODE: %s\n", ast->type);
      break; 

    case CONSTRUCTOR_NODE:
      printf("CONSTRUCTOR_NODE\n"); 
      ast_print(ast->constructor.type);
      ast_print(ast->constructor.args);
      break;

    case FUNCTION_NODE: 
      printf("FUNCTION_NODE\n");
      ast_print(ast->function.args);
      break;      

    case BINARY_EXPRESSION_NODE:
      printf("BINARY_EXPRESSION_NODE: %s\n", ast->binary_expr.op);
      ast_print(ast->binary_expr.left);
      ast_print(ast->binary_expr.right);
      break;

    case UNARY_EXPRESSION_NODE:
      printf("UNARY_EXPRESSION_NODE: %s\n", ast->unary_expr.op);
      ast_print(ast->unary_expr.right);
      break;

    case INT_NODE:
      printf("INT_NODE: %d\n", ast->int_val);
      break;

    case BOOL_NODE:
      printf("BOOL_NODE: %d\n", ast->bool_val);
      break;

    case FLOAT_NODE:
      printf("FLOAT_NODE: %f\n", ast->float_val);
      break;

    case VAR_NODE:
      printf("VAR_NODE\n");
      ast_print(ast->variable);
      break;

    case EXPRESSION_NODE:
      printf("EXPRESSION_NODE\n");
      ast_print(ast->expression);
      break; 

    case IDENT_NODE:
      if(ast->identifier.index){
        printf("ID: %s[%d]\n", ast->identifier.id, ast->identifier.index);
      } else {
        printf("ID: %s\n", ast->identifier.id);
      }   
    break;

    
    case ARGUMENTS_NODE: 
      printf("ARGUMENTS_NODE\n"); 
      ast_print(ast->arguments.args);
      ast_print(ast->arguments.expr);      
      break;

     default: break; 
  }

}


  
 /* void visit ( Visitor ∗ visitor , Node ∗ root ) {
    if (NULL == root ) return;
    switch ( root->kind ) {
      case STATEMENT: visitor->visit_statement (root); break;
      case EXPRESSION : visitor->visit_expression (root); break;
    }
  };

  void my_visit_expression ( Visitor * visitor, Node * expr);
  void my_visit_statement ( Visitor ∗ visitor , Node ∗ statement ) {
  //...
  visit ( visitor , statement->next);
}*/
