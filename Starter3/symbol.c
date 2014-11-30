#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "symbol.h"
#include "ast.h"

symbol_table *create_table(symbol_table *higher_level) {
	symbol_table *new_table = (symbol_table *)malloc(sizeof(symbol_table));
	memset(new_table, 0, sizeof(*new_table));
	new_table->next_level = higher_level;
	return new_table;
}

//debug function
void print_table(symbol_table *table) {
	int i;
	for(i = 0; i < table->entries; i++) {
		symbol symb = table->symbol_list[i];
		printf("Name: %s, Type: %d, const: %d\n", symb.name, symb.type, symb.constant);
		printf("Value 0: %f, Value 1: %f, Value 2: %f, Value 3: %f\n", symb.value[0], symb.value[1], symb.value[2], symb.value[3]);
	}
	return NULL;
}

//search the current scope for a variable with the correct name
symbol *search_table(symbol_table *table, char *name) {
	int i;
	for(i = 0; i < table->entries; i++) {
		if(strcmp(table->symbol_list[i].name, name) == 0) return &(table->symbol_list[i]);
	}
	return NULL;
}

//debug function
void print_all_levels(symbol_table *table) {
	if(table == NULL) return;
	symbol_table *curr = table;
	print_table(curr);
	printf("Finished level!\n\n");
	if(curr->next_level != NULL) print_all_levels(curr->next_level);
}

//search for a variable with the correct name in this scope and all scopes higher than this
symbol *search_all_levels(symbol_table *table, char *name) {
	if(table == NULL) return NULL;
	symbol_table *curr = table;
	symbol *symb = NULL;
	while((symb = search_table(curr, name)) == NULL) {
		/*if(strcmp(name, "gl_FragColor") == 0 || strcmp(name, "gl_FragDepth") == 0 || strcmp(name, "gl_FragCoord") == 0) {
			//these are result registers and we are in a scope other than the top level scope
			report_error("Cannot write a result register in this scope.\n");
			return NULL;
		}*/
		if(curr->next_level != NULL) curr = curr->next_level;
		else return NULL;
	}
	return symb;
}

//add an entry to the table
int add_to_table(symbol_table *table, int type, float values[4], char *name, int constant) {
	if(table->entries == SYMBOL_TABLE_SIZE) {
		printf("Symbol table is full.\n");
		return -1;
	}
	if(search_table(table, name) != NULL) {
		char msg[512];
		sprintf(msg, "A variable named %s is already declared in this scope.\n", name);
		report_error(msg);
		return -1;
	}
	symbol *new_entry = &(table->symbol_list[table->entries]);
	new_entry->type = type;
	new_entry->constant = constant;
	strcpy(new_entry->name, name);
	(table->entries)++;

	//initialize all the values that matter
	switch (type) {
		case IVEC4: case VEC4: case BVEC4:
			new_entry->value[3] = values[3];
		case IVEC3: case VEC3: case BVEC3:
			new_entry->value[2] = values[2];
		case IVEC2: case VEC2: case BVEC2:
			new_entry->value[1] = values[1];
		default:
			new_entry->value[0] = values[0];
	}
	//printf("Added Name: %s, Type: %d, const: %d\n", new_entry->name, new_entry->type, new_entry->constant);
	//printf("Value 0: %f, Value 1: %f, Value 2: %f, Value 3: %f\n", values[0], values[1], values[2], values[3]);
	return 0;
}

symbol_table *build_all_tables(node *ast, symbol_table *current_table) {

  if(ast == NULL) return;
  float values[4] = {0, 0, 0, 0};
  symbol_table *table = NULL;
  node *temp_node;
  int i;

  switch(ast->kind) {

  case NESTED_SCOPE_NODE:
	 //no tables exist yet
    table = build_all_tables(ast->nested_scope, NULL);
    break;

  case INTERMEDIATE_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
 
    build_all_tables(ast->intermediate, ast->current_table);
    break;

  case SCOPE_NODE:
	 //we are entering a new scope so we need a new table
	 //if this is the first scope, it will be passed NULL by the nested scope node
	 table = ast->current_table = create_table(current_table);

	 //now traverse down the tree
    build_all_tables(ast->scope.declarations, ast->current_table);
    build_all_tables(ast->scope.statements, ast->current_table);
    break; 

  case DECLARATIONS_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
 
    build_all_tables(ast->declarations.declarations, ast->current_table);
    build_all_tables(ast->declarations.declaration, ast->current_table); 
    break;

  case STATEMENT_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->statement.statements, ast->current_table);
    build_all_tables(ast->statement.statement, ast->current_table); 
    break;

  case DECLARATION_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->declaration.type, ast->current_table);
    build_all_tables(ast->declaration.expr, ast->current_table);
	 int decl_type;
	 /*if (strcmp(ast->declaration.type->type.name, "int") == 0) decl_type = INT;
	 else if (strcmp(ast->declaration.type->type.name, "ivec") == 0) decl_type = IVEC2;
	 else if (strcmp(ast->declaration.type->type.name, "bool") == 0) decl_type = BOOLEAN;
	 else if (strcmp(ast->declaration.type->type.name, "bvec") == 0) decl_type = BVEC2;
	 else if (strcmp(ast->declaration.type->type.name, "float") == 0) decl_type = FLOAT;
	 else if (strcmp(ast->declaration.type->type.name, "vec") == 0) decl_type = VEC2;*/
	 if (strcmp(ast->declaration.type->type.name, "int") == 0) decl_type = INT;
	 else if (strcmp(ast->declaration.type->type.name, "ivec") == 0 && ast->declaration.type->type.size == 1) decl_type = IVEC2;
	 else if (strcmp(ast->declaration.type->type.name, "ivec") == 0 && ast->declaration.type->type.size == 2) decl_type = IVEC3;
	 else if (strcmp(ast->declaration.type->type.name, "ivec") == 0 && ast->declaration.type->type.size == 3) decl_type = IVEC4;
	 else if (strcmp(ast->declaration.type->type.name, "bool") == 0) decl_type = BOOLEAN;
	 else if (strcmp(ast->declaration.type->type.name, "bvec") == 0 && ast->declaration.type->type.size == 1) decl_type = BVEC2;
	 else if (strcmp(ast->declaration.type->type.name, "bvec") == 0 && ast->declaration.type->type.size == 2) decl_type = BVEC3;
	 else if (strcmp(ast->declaration.type->type.name, "bvec") == 0 && ast->declaration.type->type.size == 3) decl_type = BVEC4;
	 else if (strcmp(ast->declaration.type->type.name, "float") == 0) decl_type = FLOAT;
	 else if (strcmp(ast->declaration.type->type.name, "vec") == 0 && ast->declaration.type->type.size == 1) decl_type = VEC2;
	 else if (strcmp(ast->declaration.type->type.name, "vec") == 0 && ast->declaration.type->type.size == 2) decl_type = VEC3;
	 else if (strcmp(ast->declaration.type->type.name, "vec") == 0 && ast->declaration.type->type.size == 3) decl_type = VEC4;

	 //check if type should be a vector type
	 //if(ast->declaration.type->type.size > 0) {
	//	decl_type += ast->declaration.type->type.size - 1;
		/*if(ast->declaration.expr->kind == CONSTRUCTOR_NODE) {
			temp_node = ast->declaration.expr->constructor.args; //pointing to top level arguments node
		 	for(i = 0; i < ast->declaration.type->type.size + 1; i++) {
				printf("Here: %d %d %f\n", i, temp_node->values[0], temp_node->values[0]);
				if(temp_node->arguments.expr != NULL) {
					ast->values[i] = temp_node->arguments.expr->values[0];
					printf("Arguments: %f %f %f %f\n", ast->values[0], ast->values[1], ast->values[2], ast->values[3]);
					if(temp_node->arguments.args != NULL) {
						temp_node = temp_node->arguments.args;
					}
				}
				//else break;
			}
		}*/
	 //}
	 add_to_table(current_table, decl_type, ast->values, ast->declaration.id, ast->declaration.constant);
    break;

  case IF_STATEMENT_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->if_stmt.expr, ast->current_table);
    build_all_tables(ast->if_stmt.stmt1, ast->current_table); 
    build_all_tables(ast->if_stmt.stmt2, ast->current_table);
    break;

  case ASSIGNMENT_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->assignment.var, ast->current_table);
    build_all_tables(ast->assignment.expr, ast->current_table); 
    break;

  case TYPE_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    break; 

  case CONSTRUCTOR_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->constructor.type, ast->current_table);
    build_all_tables(ast->constructor.args, ast->current_table);
    break;

  case FUNCTION_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->function.args, ast->current_table);
    break;

  case BINARY_EXPRESSION_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->binary_expr.left, ast->current_table);
    build_all_tables(ast->binary_expr.right, ast->current_table);
    break;

  case UNARY_EXPRESSION_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->unary_expr.right, ast->current_table);
    break;

  case INT_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    ast->expr_kind = INT;
    break;

  case BOOL_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
	 ast->expr_kind = BOOLEAN;
    break;

  case FLOAT_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
	 ast->expr_kind = FLOAT;
    break;

  case VAR_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->variable, ast->current_table);
    break;

  case EXPRESSION_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
    build_all_tables(ast->expression, ast->current_table);
    break; 

  case IDENT_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;
  break;

  case ARGUMENTS_NODE:
	 //we are not entering a new scope, so use the passed value of current_table
	 ast->current_table = current_table;  
    build_all_tables(ast->arguments.args, ast->current_table);
    build_all_tables(ast->arguments.expr, ast->current_table);      
    break;

  default: break;
  }
  return table;
}

//add the predefined variables
void add_global_symbols (symbol_table *table) {
	float values[4] = {0, 0, 0, 0};
	add_to_table(table, VEC4, values, "gl_FragColor", 0);
	add_to_table(table, BOOLEAN, values, "gl_FragDepth", 0);
	add_to_table(table, VEC4, values, "gl_FragCoord", 0);

	add_to_table(table, VEC4, values, "gl_TexCoord", 0);
	add_to_table(table, VEC4, values, "gl_Color", 0);
	add_to_table(table, VEC4, values, "gl_Secondary", 0);
	add_to_table(table, VEC4, values, "gl_FogFragCoord", 0);

	add_to_table(table, VEC4, values, "gl_Light_Half", 1);
	add_to_table(table, VEC4, values, "gl_Light_Ambient", 1);
	add_to_table(table, VEC4, values, "gl_Material_Shininess", 1);

	add_to_table(table, VEC4, values, "env1", 1);
	add_to_table(table, VEC4, values, "env2", 1);
	add_to_table(table, VEC4, values, "env3", 1);
}

void delete_table(symbol_table *table) {
	if(table != NULL) free(table);
	table = NULL;
}
