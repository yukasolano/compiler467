#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "semantic.h"


void fill_types(node *ast) {

  if(ast == NULL) return;
  ast->expr_kind = NONE;
  symbol *symb = NULL;
  node *temp;
  char var_name[256];
  int left_type, right_type;

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
		//invalid declaration
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

	 char msg[512];

	 //Find the name of the variable being assigned a value
	 temp = ast->assignment.var;
	 strcpy(var_name, temp->identifier.id);

	 //Find the variable in the symbol table
	 symb = search_all_levels(ast->current_table, var_name);
	 if(symb == NULL) {
		 //variable is not defined in this scope
		 sprintf(msg, "Variable %s is not defined in this scope.\n", var_name);
		 report_error(msg);
	 }
	 else if(ast->assignment.var->expr_kind != ast->assignment.expr->expr_kind) {
		//variable type does not match the expression type
		sprintf(msg, "Declaration type mismatch: variable %s declared as type %s but assigned value of type %s\n", 
 				var_name, var_type(ast->assignment.var->expr_kind), var_type(ast->assignment.expr->expr_kind));
		report_error(msg);
	 }
	 else if(symb->constant) {
		 //variable was declared as constant
		 sprintf(msg, "Variable %s was declared as constant. Value cannot be reassigned.\n", var_name);
		 report_error(msg);
	 }
	 ast->expr_kind = ast->assignment.var->expr_kind;
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
	 left_type = ast->binary_expr.left->expr_kind;
	 right_type = ast->binary_expr.right->expr_kind;
	 ast->expr_kind = left_type;
	 if(strcmp(ast->binary_expr.op, "&&") == 0 || strcmp(ast->binary_expr.op, "||") == 0) {
		 if(base_type(left_type) != BOOLEAN || base_type(right_type) != BOOLEAN) report_error("All operands to logical operators must have 				boolean types.\n");
	 }
	 else if(strcmp(ast->binary_expr.op, "+") == 0 || strcmp(ast->binary_expr.op, "-") == 0) {
		 if(left_type != right_type) report_error("+/- operations require both operands to have the same type.\n");
		 else if(base_type(left_type) == BOOLEAN || base_type(right_type) == BOOLEAN) report_error("Operands to +/- must be arithmetic.\n");
	 }
	 else if(strcmp(ast->binary_expr.op, "*") == 0) {
		 if(left_type == FLOAT) {
			if(right_type == FLOAT) ast->expr_kind = FLOAT;
			else if(right_type == VEC2 || right_type == VEC3 || right_type == VEC4) ast->expr_kind = right_type;
			else report_error("Invalid operands to * operator.\n");
		 }
		 else if(left_type == INT) {
			if(right_type == INT) ast->expr_kind = INT;
			else if(right_type == IVEC2 || right_type == IVEC3 || right_type == IVEC4) ast->expr_kind = right_type;
			else report_error("Invalid operands to * operator.\n");
		 }
		 else if(base_type(left_type) == FLOAT) {
			//left type is a float vector or it would have triggered the first if statement
			if(right_type == FLOAT) ast->expr_kind = left_type;
			else if(right_type == left_type) ast->expr_kind = right_type;
			else report_error("Invalid operands to * operator.\n");
		 }
		 else if(base_type(left_type) == FLOAT) {
			//left type is an int vector or it would have triggered the first if statement
			if(right_type == INT) ast->expr_kind = left_type;
			else if(right_type == left_type) ast->expr_kind = right_type;
			else report_error("Invalid operands to * operator.\n");
		 }
		 else report_error("Invalid operands to * operator.\n");
		 printf("Expression type: %s\n", var_type(ast->expr_kind));
	 }
	 else if(strcmp(ast->binary_expr.op, "/") == 0 || strcmp(ast->binary_expr.op, "^") == 0) {
		 if((left_type != FLOAT && left_type != INT) || (right_type != FLOAT && right_type != INT) || right_type != left_type)
			 report_error("Operands to ^ or / must both be scalars of the same type.\n");
	 }
	 else if(strcmp(ast->binary_expr.op, "<") == 0 || strcmp(ast->binary_expr.op, "<=") == 0 ||
				strcmp(ast->binary_expr.op, ">") == 0 || strcmp(ast->binary_expr.op, ">=") == 0) {
	 		if((left_type != FLOAT && left_type != INT) || (right_type != FLOAT && right_type != INT) || right_type != left_type)
			 report_error("Operands to inequality comparisons must both be scalars of the same type.\n");
			else ast->expr_kind = BOOLEAN;
	 }
	 else if(strcmp(ast->binary_expr.op, "==") == 0 || strcmp(ast->binary_expr.op, "!=") == 0) {
		 if(right_type != left_type) report_error("Operands to equality comparisons must have the same type.\n");
		 else if (base_type(left_type) == BOOLEAN || base_type(right_type) == BOOLEAN) report_error("Operands to equality comparisons must be arithmetic.\n");
		 else ast->expr_kind = BOOLEAN;
	 }
    break;

  case UNARY_EXPRESSION_NODE:
    fill_types(ast->unary_expr.right);
	 right_type = ast->unary_expr.right->expr_kind;
	 ast->expr_kind = right_type;
	 if(strcmp(ast->unary_expr.op, "!") == 0) {
	 	if(base_type(right_type) != BOOLEAN) report_error("Operand of ! must be boolean.\n");
	 }
	 else if(strcmp(ast->unary_expr.op, "-") == 0) {
		 if(base_type(right_type) == BOOLEAN) report_error("Operand of unary minus must be arithmetic.\n");
	 }
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
		 /*//check if it's a vector, in which case we need to get the base type
		 if(ast->expr_kind == BVEC2 || ast->expr_kind == BVEC3 || ast->expr_kind == BVEC4) ast->expr_kind = BOOLEAN;
		 if(ast->expr_kind == IVEC2 || ast->expr_kind == IVEC3 || ast->expr_kind == IVEC4) ast->expr_kind = INT;
		 if(ast->expr_kind == VEC2 || ast->expr_kind == VEC3 || ast->expr_kind == VEC4) ast->expr_kind = FLOAT;*/
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
