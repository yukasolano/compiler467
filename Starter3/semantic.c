#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semantic.h"


void fill_types(node *ast) {

  if(ast == NULL) return;
  ast->expr_kind = NONE;
  symbol *symb = NULL;

  //need to fill all children first; different actions depending on ast->kind
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
	 if((ast->declaration.expr != NULL) && ast->declaration.expr->expr_kind != ast->declaration.type->expr_kind) {
		char msg[512];
		sprintf(msg, "Declaration type mismatch: variable %s declared as type %s but assigned value of type %s\n", ast->declaration.id, 				var_type(ast->declaration.type->expr_kind), var_type(ast->declaration.expr->expr_kind));
		report_error(msg);
	 }
	 ast->expr_kind = ast->declaration.type->expr_kind;
    break;

  case IF_STATEMENT_NODE:
    fill_types(ast->if_stmt.expr);
    fill_types(ast->if_stmt.stmt1); 
    fill_types(ast->if_stmt.stmt2);
    break;

  case ASSIGNMENT_NODE:
    fill_types(ast->assignment.var);
    fill_types(ast->assignment.expr);
	 if(ast->assignment.var->expr_kind != ast->assignment.expr->expr_kind) {
		char msg[512];
		sprintf(msg, "Declaration type mismatch: variable declared as type %s but assigned value of type %s\n", 
 				var_type(ast->assignment.var->expr_kind), var_type(ast->assignment.expr->expr_kind));
		report_error(msg);
	 }
    break;

  case TYPE_NODE:
	 if(strcmp(ast->type.name, "int") == 0) ast->expr_kind = INT;
	 else if(strcmp(ast->type.name, "bool") == 0) ast->expr_kind = BOOLEAN;
	 else if(strcmp(ast->type.name, "float") == 0) ast->expr_kind = FLOAT;
	 if(ast->expr_kind != NULL) ast->expr_kind += ast->type.size;
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
    break;

  case UNARY_EXPRESSION_NODE:
    fill_types(ast->unary_expr.right);
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
	 ast->expr_kind = ast->variable->expr_kind;
    break;

  case EXPRESSION_NODE:
    fill_types(ast->expression);
	 ast->expr_kind = ast->expression->expr_kind;
    break;

  case IDENT_NODE:
	 //search the symbol table for the variable with the correct name so we can remember its type
	 symb = search_all_levels(ast->current_table, ast->identifier.id);
	 if(symb == NULL) report_error("Variable not defined in this scope.\n");
	 else {
		 ast->expr_kind = symb->type;
		 //check if it's a vector, in which case we need to get the base type
		 if(ast->expr_kind == BVEC2 || ast->expr_kind == BVEC3 || ast->expr_kind == BVEC4) ast->expr_kind = BOOLEAN;
		 if(ast->expr_kind == IVEC2 || ast->expr_kind == IVEC3 || ast->expr_kind == IVEC4) ast->expr_kind = INT;
		 if(ast->expr_kind == VEC2 || ast->expr_kind == VEC3 || ast->expr_kind == VEC4) ast->expr_kind = FLOAT;
	 }
  break;

  
  case ARGUMENTS_NODE:  
    fill_types(ast->arguments.args);
    fill_types(ast->arguments.expr);
	 if(ast->arguments.expr->expr_kind != ast->arguments.args->expr_kind) report_error("Arguments type mismatch\n");     
    break;


  default: return;
  }

}

int semantic_check( node *ast) {
  return 0; // failed checks
}
