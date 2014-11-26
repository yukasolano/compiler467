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
	 if(ast->declaration.expr != NULL && ast->declaration.expr->expr_kind != ast->declaration.type->expr_kind) {
		//invalid declaration
		char msg[512];
		sprintf(msg, "Declaration type mismatch: variable %s declared as type %s but assigned value of type %s\n", ast->declaration.id, 				var_type(ast->declaration.type->expr_kind), var_type(ast->declaration.expr->expr_kind));
		report_error(msg);
	 }
	 if (ast->declaration.constant == 1){
	 	//CONST Should initialize only with literals (including constructors) or uniform variables
	 	if (ast->declaration.expr->kind != BOOL_NODE && ast->declaration.expr->kind != INT_NODE && ast->declaration.expr->kind != FLOAT_NODE &&
	 	 ast->declaration.expr->kind != VAR_NODE && ast->declaration.expr->kind != CONSTRUCTOR_NODE ){
	 		report_error("const qualified variables must be initialized with a literal value or an uniform variable.\n");
	 	}
 		if(ast->declaration.expr->kind == VAR_NODE && ast->declaration.expr->variable->kind == IDENT_NODE){
 			//Check if it is an uniform variable
 			char id[32];
 			strncpy(id, ast->declaration.expr->variable->identifier.id, 32);
 			if(strcmp(id, "gl_Light_Half") != 0 && strcmp(id, "gl_Light_Ambient") != 0 && strcmp(id, "gl_Material_Shininess") != 0 
 				&& strcmp(id, "env1") != 0 && strcmp(id, "env2") != 0 && strcmp(id, "env3") != 0){		
	 		report_error("const qualified variables must be initialized with a literal value or an uniform variable.\n");
 			}		 			
 		}	 	
	 }
	 else if(ast->declaration.expr != NULL && ast->declaration.expr->kind == VAR_NODE && ast->declaration.expr->variable->kind == IDENT_NODE){
	 	//result variable: cannot be read. Write-only.
		char id[32];
		strncpy(id, ast->declaration.expr->variable->identifier.id, 32);
		if(strcmp(id, "gl_FragColor") == 0 || strcmp(id,"gl_FragDepth") == 0 || strcmp(id, "gl_FragCoord") == 0){		
			char msg[512];
			sprintf(msg, "Variable %s is a result variable. It cannot be read. Write-only.\n", id);
	 		report_error(msg); 			
		}	
	 }
	 ast->expr_kind = ast->declaration.type->expr_kind;
    break;

  case IF_STATEMENT_NODE:
    fill_types(ast->if_stmt.expr);
    fill_types(ast->if_stmt.stmt1); 
    fill_types(ast->if_stmt.stmt2);
    if (ast->if_stmt.expr->expr_kind != BOOLEAN) report_error("The expression that determins which branch of an if statement should be taken must have the type bool\n");

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

	//attribute variable: cannot be assigned. Read-only.
	char id[32];
	strncpy(id, ast->assignment.var->identifier.id, 32);
	if(strcmp(id, "gl_TexCoord") == 0 || strcmp(id, "gl_Color") == 0 || strcmp(id, "gl_Secondary") == 0 
		|| strcmp(id, "gl_FogFragCoord") == 0){		
 		sprintf(msg, "Variable %s is a attribute variable. It cannot be assigned. Read-only.\n", id);
 		report_error(msg);
	}		 				
	if(ast->assignment.expr->kind == VAR_NODE && ast->assignment.expr->variable->kind == IDENT_NODE){
		//result variable: cannot be read. Write-only.
		char id[32];
		strncpy(id, ast->assignment.expr->variable->identifier.id, 32);
		if(strcmp(id, "gl_FragColor") == 0 || strcmp(id,"gl_FragDepth") == 0 || strcmp(id, "gl_FragCoord") == 0){		
			sprintf(msg, "Variable %s is a result variable. It cannot be read. Write-only.\n", id);
	 		report_error(msg); 			
		}		 			
 	 }	 
	 ast->expr_kind = ast->assignment.var->expr_kind;
    break;

  case TYPE_NODE:
	 if(strcmp(ast->type.name, "int") == 0 || strcmp(ast->type.name, "ivec") == 0) ast->expr_kind = INT;
	 else if(strcmp(ast->type.name, "bool") == 0 || strcmp(ast->type.name, "bvec") == 0) ast->expr_kind = BOOLEAN;
	 else if(strcmp(ast->type.name, "float") == 0 || strcmp(ast->type.name, "vec") == 0) ast->expr_kind = FLOAT;
	 if(ast->expr_kind != NULL) ast->expr_kind += ast->type.size;
    break; 

  case CONSTRUCTOR_NODE: 
    fill_types(ast->constructor.type);
    fill_types(ast->constructor.args);

    //Get the quantity of arguments
    /*if (ast->constructor.args != NULL){
    	ast->constructor.qtd_args = ast->constructor.args->arguments.qtd_args;
    }else {
    	ast->constructor.qtd_args = 0; 
    }*/
    
	if(ast->constructor.args->expr_kind != base_type(ast->constructor.type->expr_kind)) report_error("Constructor type mismatch.\n");	 
	ast->expr_kind = ast->constructor.type->expr_kind;

	//Check if order of vector match with the type of the constructor
	if(ast->constructor.qtd_args%4 != ast->expr_kind%4 ) {
		int qtd_args = ast->expr_kind%4;
		if(ast->expr_kind%4 == 0) qtd_args = 4;
		char msg[512];
		sprintf(msg, "%s constructor should have %d arguments, but it has %d.\n", var_type(ast->expr_kind), qtd_args ,ast->constructor.qtd_args);
		report_error(msg);
	}
	/*printf("DEBUG CONSTRUCTOR_NODE ");
	for (int i = 0; i < ast->constructor.qtd_args; i++){
		ast->values[i] = ast->constructor.args->values[i];
		printf("%f ",ast->values[i]);
	}
	printf("\n");*/
    break;

  case FUNCTION_NODE: 
    fill_types(ast->function.args);

    //Get the quantity of arguments
    if (ast->function.args != NULL){
    	ast->function.qtd_args = ast->function.args->arguments.qtd_args;
    }else {
    	ast->function.qtd_args = 0; 
    }

    if(ast->function.name == DP3){
    	if(ast->function.qtd_args != 2) report_error("DP3 function should have 2 arguments.\n");
    	else if (ast->function.args->expr_kind == VEC4 || ast->function.args->expr_kind == VEC3) ast->expr_kind = FLOAT;
    	else if (ast->function.args->expr_kind == IVEC4 || ast->function.args->expr_kind == IVEC3) ast->expr_kind = INT;
    	else report_error("DP3 function should have 2 arguments of type VEC4, VEC3, IVEC4 or IVEC3.\n");

    }else if (ast->function.name == LIT){
    	if(ast->function.qtd_args != 1 || ast->function.args->expr_kind != VEC4)
    	 report_error("LIT function should have only one argument of type VEC4.\n");
    	//LIT function is type VEC4
    	ast->expr_kind = VEC4;

    } else if (ast->function.name == RSQ){
    	if(ast->function.qtd_args != 1) report_error("RSQ function should have only one argument.\n");
    	else if (ast->function.args->expr_kind == FLOAT) ast->expr_kind = FLOAT;
    	else if (ast->function.args->expr_kind == INT) ast->expr_kind = INT;
    	else report_error("RSQ function should have an argument of type FLOAT or INT.\n");
    } else{
    	report_error("Function not acceptable.\n");
    }
    break;

  case BINARY_EXPRESSION_NODE:
    fill_types(ast->binary_expr.left);
    fill_types(ast->binary_expr.right);
	 left_type = ast->binary_expr.left->expr_kind;
	 right_type = ast->binary_expr.right->expr_kind;
	 ast->expr_kind = left_type;
	 if(strcmp(ast->binary_expr.op, "&&") == 0 || strcmp(ast->binary_expr.op, "||") == 0) {
		 if(base_type(left_type) != BOOLEAN || base_type(right_type) != BOOLEAN) {
		 	ast->expr_kind = NONE;
		 	report_error("All operands to logical operators must have boolean types.\n");
		 } 
		 else if(left_type != right_type){
		 	ast->expr_kind = NONE;
		 	report_error("Operands to logical operators must have the same type.\n");
		 } 	
	 }
	 else if(strcmp(ast->binary_expr.op, "+") == 0 || strcmp(ast->binary_expr.op, "-") == 0) {
		 if(left_type != right_type){
		 	ast->expr_kind = NONE;
		 	report_error("+/- operations require both operands to have the same type.\n");
		 } 
		 else if(base_type(left_type) == BOOLEAN || base_type(right_type) == BOOLEAN){
		 	ast->expr_kind = NONE;
		 	report_error("Operands to +/- must be arithmetic.\n");
		 } 
	 }
	 else if(strcmp(ast->binary_expr.op, "*") == 0) {
		 if(left_type == FLOAT) {
			if(right_type == FLOAT) ast->expr_kind = FLOAT;
			else if(right_type == VEC2 || right_type == VEC3 || right_type == VEC4) ast->expr_kind = right_type;
			else {
				ast->expr_kind = NONE;
				report_error("Invalid operands to * operator.\n");
			}
		 }
		 else if(left_type == INT) {
			if(right_type == INT) ast->expr_kind = INT;
			else if(right_type == IVEC2 || right_type == IVEC3 || right_type == IVEC4) ast->expr_kind = right_type;
			else {
				ast->expr_kind = NONE;
				report_error("Invalid operands to * operator.\n");
			}
		 }
		 else if(base_type(left_type) == FLOAT) {
			//left type is a float vector or it would have triggered the first if statement
			if(right_type == FLOAT) ast->expr_kind = left_type;
			else if(right_type == left_type) ast->expr_kind = right_type;
			else {
				ast->expr_kind = NONE;
				report_error("Invalid operands to * operator.\n");
			}
		 }
		 else if(base_type(left_type) == INT) {
			//left type is an int vector or it would have triggered the first if statement
			if(right_type == INT) ast->expr_kind = left_type;
			else if(right_type == left_type) ast->expr_kind = right_type;
			else {
				ast->expr_kind = NONE;
				report_error("Invalid operands to * operator.\n");
			}
		 }
		 else {
		 	ast->expr_kind = NONE;
		 	report_error("Invalid operands to * operator.\n");
		 }
	 }
	 else if(strcmp(ast->binary_expr.op, "/") == 0 || strcmp(ast->binary_expr.op, "^") == 0) {
		 if((left_type != FLOAT && left_type != INT) || (right_type != FLOAT && right_type != INT) || right_type != left_type){
		 	ast->expr_kind = NONE;
		 	report_error("Operands to ^ or / must both be arithmetic scalars of the same type.\n");
		 }	 
	 }
	 else if(strcmp(ast->binary_expr.op, "<") == 0 || strcmp(ast->binary_expr.op, "<=") == 0 ||
				strcmp(ast->binary_expr.op, ">") == 0 || strcmp(ast->binary_expr.op, ">=") == 0) {
	 		if((left_type != FLOAT && left_type != INT) || (right_type != FLOAT && right_type != INT) || right_type != left_type){
	 			ast->expr_kind = NONE;
	 			report_error("Operands to inequality comparisons must both be arithmetic and scalars of the same type.\n");
	 		} 
			else ast->expr_kind = BOOLEAN;
	 }
	 else if(strcmp(ast->binary_expr.op, "==") == 0 || strcmp(ast->binary_expr.op, "!=") == 0) {
		 if(right_type != left_type) {
		 	ast->expr_kind = NONE;
		 	report_error("Operands to equality comparisons must have the same type.\n");
		 }
		 else if (base_type(left_type) == BOOLEAN || base_type(right_type) == BOOLEAN){
		 	ast->expr_kind = NONE;
		 	report_error("Operands to equality comparisons must be arithmetic.\n");
		 } 
		 else ast->expr_kind = BOOLEAN;
	 }
    break;

  case UNARY_EXPRESSION_NODE:
    fill_types(ast->unary_expr.right);
	 right_type = ast->unary_expr.right->expr_kind;
	 ast->expr_kind = right_type;
	 if(strcmp(ast->unary_expr.op, "!") == 0) {
	 	if(base_type(right_type) != BOOLEAN){
	 		ast->expr_kind = NONE;
	 		report_error("Operand of ! must be boolean.\n");
	 	} 
	 }
	 else if(strcmp(ast->unary_expr.op, "-") == 0) {
		 if(base_type(right_type) == BOOLEAN){
		 	ast->expr_kind = NONE;
		 	report_error("Operand of unary minus must be arithmetic.\n");
		 } 
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
	 
	 //If it has an index
	 else if (ast->identifier.index != -1){
	 	//Check if it is in the range
	 	int size = symb->type%4;
	 	if(size == 0) size = 4;
	 	if (ast->identifier.index < 0 || ast->identifier.index >= size){
	 		char msg[512];
	 		sprintf(msg,"Index of %s is out of range.\n", ast->identifier.id);
	 		report_error(msg);
	 	} 

	 	ast->expr_kind = base_type(symb->type);
		 
	 } else {
	 	ast->expr_kind = symb->type;
	 }
  break;

  
  case ARGUMENTS_NODE: 
    fill_types(ast->arguments.args);
    fill_types(ast->arguments.expr);
	if(ast->arguments.expr != NULL && ast->arguments.expr->expr_kind != ast->arguments.args->expr_kind) report_error("Arguments type mismatch.\n");
	ast->expr_kind = ast->arguments.args->expr_kind;

	 /*//The father node get the values and qtd_args of the child node
	 if(ast->arguments.args!= NULL){
	 	ast->arguments.qtd_args = ast->arguments.args->arguments.qtd_args + 1;
	 	if (ast->arguments.expr != NULL){
	 		for(int i = 0; i < ast->arguments.qtd_args; i++){
	 			ast->values[i] = ast->arguments.args->values[i];
	 		}
	 		ast->values[ast->arguments.qtd_args] = ast->arguments.expr->values[0];
	 	} else {
	 		for(int i = 0; i < ast->arguments.qtd_args; i++){
	 			ast->values[i] = ast->arguments.args->values[i];
	 		}
	 	}	 	
	 } */
    break;


  default: return;
  }

}

int semantic_check( node *ast) {
  return 0; // failed checks
}
