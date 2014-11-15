#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semantic.h"

void fill_types(node *ast) {

  if(ast == NULL) return;
  //ast->expr_kind = NONE;

  //need to free all children first; different actions depending on ast->kind
  switch(ast->kind) {

  case NESTED_SCOPE_NODE:
    fill_types(ast->nested_scope);
    break;

  case INTERMEDIATE_NODE:
	 fill_types(ast->intermediate);
	 break;

  case SCOPE_NODE:
    fill_types(ast->scope.declarations);
    fill_types(ast->scope.statements);    
    break; 

  case DECLARATIONS_NODE: 
    fill_types(ast->declarations.declarations);
    fill_types(ast->declarations.declaration); 
    break;

  case STATEMENT_NODE:
    fill_types(ast->statement.statements);
    fill_types(ast->statement.statement); 
    break;

  case DECLARATION_NODE: 
    fill_types(ast->declaration.type);
    fill_types(ast->declaration.expr);
	 if(ast->declaration.expr->expr_kind != ast->declaration.type->expr_kind) return -1;
	 ast->expr_kind = ast->declaration.expr->expr_kind;
	 //if(ast->declaration.id != NULL) free(ast->declaration.id);
    break;

  case IF_STATEMENT_NODE:
    fill_types(ast->if_stmt.expr);
    fill_types(ast->if_stmt.stmt1); 
    fill_types(ast->if_stmt.stmt2);
    break;

  case ASSIGNMENT_NODE:
    fill_types(ast->assignment.var);
    fill_types(ast->assignment.expr); 
    break;

  case TYPE_NODE:
	 if(strcmp(ast->type.name, "int")) ast->expr_kind = INT;
	 else if(strcmp(ast->type.name, "bool")) ast->expr_kind = BOOLEAN;
	 else if(strcmp(ast->type.name, "float")) ast->expr_kind = FLOAT;
	 ast->expr_kind += ast->type.size;
    break; 

  case CONSTRUCTOR_NODE: 
    fill_types(ast->constructor.type);
    fill_types(ast->constructor.args);
    break;

  case FUNCTION_NODE: 
    fill_types(ast->function.args);
    break;

  case BINARY_EXPRESSION_NODE:
    fill_types(ast->binary_expr.left);
    fill_types(ast->binary_expr.right);
	 //if(ast->binary_expr.op != NULL) free(ast->binary_expr.op);
    break;

  case UNARY_EXPRESSION_NODE:
    fill_types(ast->unary_expr.right);
	 //if(ast->unary_expr.op != NULL) free(ast->unary_expr.op);
    break; 

  case INT_NODE:
	 ast->expr_kind = INT;
    break;

  case BOOL_NODE:
	 ast->expr_kind = BOOLEAN;
    break;

  case FLOAT_NODE:
	 ast->expr_kind = FLOAT;
    break;

  case VAR_NODE:
    fill_types(ast->variable);
    break;

  case EXPRESSION_NODE:
    fill_types(ast->expression);
    break; 

  case IDENT_NODE:
    //if(ast->identifier.id != NULL) free(ast->identifier.id);
  break;

  
  case ARGUMENTS_NODE:  
    ast_free(ast->arguments.args);
    ast_free(ast->arguments.expr);      
    break;


  // ...

  default: return;
  }

}

int semantic_check( node *ast) {
  return 0; // failed checks
}
