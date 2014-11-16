#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"
#include "symbol.h"

#define DEBUG_PRINT_TREE 0

node *ast = NULL;
//symbol_table *top_scope = create_table(NULL);
//symbol_table *current_scope = top_scope;

node *ast_allocate(node_kind kind, ...) {
  va_list args;

  // make the node
  node *ast = (node *) malloc(sizeof(node));
  memset(ast, 0, sizeof *ast);
  ast->kind = kind;
  ast->expr_kind = NONE;

  va_start(args, kind); 

  switch(kind) {
  
  // ...

  case NESTED_SCOPE_NODE:
    ast->nested_scope = va_arg(args, node *);
    break;

  case INTERMEDIATE_NODE:
    ast->intermediate = va_arg(args, node *);
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
	 ast->declaration.constant = va_arg(args, int);
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
    ast->type.name = va_arg(args, char*);
    ast->type.size = va_arg(args, int);
    break; 

  case CONSTRUCTOR_NODE: 
    ast->constructor.type = va_arg(args, node *);
    ast->constructor.args = va_arg(args, node *);
    break;

  case FUNCTION_NODE: 
    ast->function.name = va_arg(args, int);
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
    ast->expr_kind = INT;
    break;

  case BOOL_NODE:
    ast->bool_val = va_arg(args, int);
	 ast->expr_kind = BOOLEAN;
    break;

  case FLOAT_NODE:
    ast->float_val = va_arg(args, double);
	 ast->expr_kind = FLOAT;
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

  default: break;
  }

  return ast;
}

char * strTest(int a){
  char * str = malloc(sizeof(char)*20);
  strcpy(str, "testando");
  return str;
}


void ast_free(node *ast) {

  if(ast == NULL) return;

  //need to free all children first; different actions depending on ast->kind
  switch(ast->kind) {

  case NESTED_SCOPE_NODE:
    ast_free(ast->nested_scope);
    break;

  case INTERMEDIATE_NODE:
	 ast_free(ast->intermediate);
	 break;

  case SCOPE_NODE:
    ast_free(ast->scope.declarations);
    ast_free(ast->scope.statements);    
    break; 

  case DECLARATIONS_NODE: 
    ast_free(ast->declarations.declarations);
    ast_free(ast->declarations.declaration); 
    break;

  case STATEMENT_NODE:
    ast_free(ast->statement.statements);
    ast_free(ast->statement.statement); 
    break;

  case DECLARATION_NODE: 
    ast_free(ast->declaration.type);
    ast_free(ast->declaration.expr);
	 //if(ast->declaration.id != NULL) free(ast->declaration.id);
    break;

  case IF_STATEMENT_NODE:
    ast_free(ast->if_stmt.expr);
    ast_free(ast->if_stmt.stmt1); 
    ast_free(ast->if_stmt.stmt2);
    break;

  case ASSIGNMENT_NODE:
    ast_free(ast->assignment.var);
    ast_free(ast->assignment.expr); 
    break;

  case TYPE_NODE:
    break; 

  case CONSTRUCTOR_NODE: 
    ast_free(ast->constructor.type);
    ast_free(ast->constructor.args);
    break;

  case FUNCTION_NODE: 
    ast_free(ast->function.args);
    break;

  case BINARY_EXPRESSION_NODE:
    ast_free(ast->binary_expr.left);
    ast_free(ast->binary_expr.right);
    break;

  case UNARY_EXPRESSION_NODE:
    ast_free(ast->unary_expr.right);
    break; 

  case INT_NODE:
    break;

  case BOOL_NODE:
    break;

  case FLOAT_NODE:
    break;

  case VAR_NODE:
    ast_free(ast->variable);
    break;

  case EXPRESSION_NODE:
    ast_free(ast->expression);
    break; 

  case IDENT_NODE:
  break;

  
  case ARGUMENTS_NODE:  
    ast_free(ast->arguments.args);
    ast_free(ast->arguments.expr);      
    break;


  // ...

  default: return;
  }

  //finally, free the node we were passed
  free(ast);
  ast = NULL;
}

void ast_print(node * ast) {

  printf("%s\n", node_print(ast));


}

char * node_print(node *ast){

  if(ast == NULL) return "";
  char * str = malloc(sizeof(char)*50);

  switch (ast->kind){

    case NESTED_SCOPE_NODE:
      //printf("NESTED_SCOPE_NODE\n");
      return node_print(ast->nested_scope);

	 case INTERMEDIATE_NODE:
		return node_print(ast->intermediate);

    case SCOPE_NODE: 
      //printf("SCOPE_NODE\n");
      sprintf(str, "\n(SCOPE \n%s", node_print(ast->scope.declarations));
      sprintf(str, "%s%s)", str, node_print(ast->scope.statements));
      return str;

    case DECLARATIONS_NODE:
      //printf("DECLARATIONS_NODE\n");
      sprintf(str, " (DECLARATIONS %s", node_print(ast->declarations.declarations));
      sprintf(str, "%s %s)\n" , str, node_print(ast->declarations.declaration));
      return str;

    case STATEMENT_NODE:
      //printf("STATEMENT_NODE\n");     
      sprintf(str, " (STATEMENTS %s", node_print(ast->statement.statements));
      sprintf(str, "%s %s)\n", str, node_print(ast->statement.statement)); 
      return str;   

    case DECLARATION_NODE: 
      //printf("DECLARATION_NODE\n");
      sprintf(str, "(DECLARATION %s %s" ,ast->declaration.id, node_print(ast->declaration.type));
      sprintf(str, "%s %s)", str, node_print(ast->declaration.expr));
      return str;

    case IF_STATEMENT_NODE:
      //printf("IF_STATEMENT_NODE\n");
      sprintf(str, "(IF %s", node_print(ast->if_stmt.expr));
      sprintf(str, "%s %s", str, node_print(ast->if_stmt.stmt1));
      sprintf(str, "%s %s)", str, node_print(ast->if_stmt.stmt2));  
      return str;

    case ASSIGNMENT_NODE:
      //printf("ASSIGMENT_NODE\n");
      sprintf(str, "(ASSIGN <type> %s", node_print(ast->assignment.var));
      sprintf(str, "%s %s)", str, node_print(ast->assignment.expr));
      return str; 

    case TYPE_NODE:
      //printf("TYPE_NODE: %s\n", ast->type);
      if(ast->type.size == NULL){
        sprintf(str, "%s", ast->type.name);
      }
      else {
        sprintf(str, "%s%d", ast->type.name, ast->type.size+1);
      }
      return str;

    case CONSTRUCTOR_NODE:
      //printf("CONSTRUCTOR_NODE\n"); 
      sprintf(str, "(CALL %s", node_print(ast->constructor.type));
      sprintf(str, "%s %s)",str, node_print(ast->constructor.args));
      return str;

    case FUNCTION_NODE: 
      //printf("FUNCTION_NODE\n");
      char name[3];
      if (ast->function.name == 0) strcpy(name, "dp3");
      else if (ast->function.name == 1) strcpy(name, "lit");
      else strcpy(name, "rsq");
      sprintf(str, "(CALL %s %s)", name, node_print(ast->function.args));
      return str;      

    case BINARY_EXPRESSION_NODE:
      //printf("BINARY_EXPRESSION_NODE: %s\n", ast->binary_expr.op);
      sprintf(str, "(BINARY <type> %s %s", ast->binary_expr.op, node_print(ast->binary_expr.left));
      sprintf(str, "%s %s)", str, node_print(ast->binary_expr.right));
      return  str;

    case UNARY_EXPRESSION_NODE:
      //printf("UNARY_EXPRESSION_NODE: %s\n", ast->unary_expr.op);
      sprintf(str, "(UNARY <type> %s %s)\n", ast->unary_expr.op, node_print(ast->unary_expr.right));
      return str; 

    case INT_NODE:
      //printf("INT_NODE: %d\n", ast->int_val);
      sprintf(str, "%d", ast->int_val);;
      return str;

    case BOOL_NODE:
      //printf("BOOL_NODE: %d\n", ast->bool_val);
      if(ast->bool_val == 0){
        //printf("false\n");
        return "false";
      } else {
        //printf("true\n");
        return "true";
      }

    case FLOAT_NODE:
      //printf("FLOAT_NODE: %f\n", ast->float_val);
      sprintf(str, "%f", ast->float_val);
      return str;

    case VAR_NODE:
      //printf("VAR_NODE\n");
      return node_print(ast->variable);

    case EXPRESSION_NODE:
      //printf("EXPRESSION_NODE\n");
      return node_print(ast->expression); 

    case IDENT_NODE:
      //printf("IDENT_NODE: %s\n", ast->identifier.id);
      if(ast->identifier.index){
        sprintf(str, "(INDEX <type> %s %d)", ast->identifier.id, ast->identifier.index);
      } else {
        sprintf(str, "%s", ast->identifier.id);
      };
      return str;
    
    case ARGUMENTS_NODE: 
      //printf("ARGUMENTS_NODE\n"); 
      sprintf(str, "%s", node_print(ast->arguments.args));
      sprintf(str, "%s %s", str, node_print(ast->arguments.expr)); 
      return str;     

     default: return ""; 
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
