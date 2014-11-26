#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"


/*Return 0 in case of success
		-1 otherwise
*/
int genCode(node *ast){
	fprintf(outputFile, "#COMPILER467\n\n");
	readTree(ast);
	return 0;
}


int isPredefinedVar(char *id){
	
	//Uniform
	if (strcmp(id, "env1") == 0) 					return ENV1;
	if (strcmp(id, "env2") == 0) 					return ENV2;
	if (strcmp(id, "env3") == 0) 					return ENV3;
 	if (strcmp(id, "gl_Light_Half") == 0) 			return GL_LIGHT_HALF;
 	if (strcmp(id, "gl_Light_Ambient") == 0) 		return GL_LIGHT_AMBIENT;
 	if (strcmp(id, "gl_Material_Shininess") == 0) 	return GL_MATERIAL_SHININESS; 
 		
 	//Atribute
 	if (strcmp(id, "gl_TexCoord") == 0) 			return GL_TEXTCOORD;
 	if (strcmp(id, "gl_Color") == 0) 				return GL_COLOR;
 	if (strcmp(id, "gl_Secondary") == 0) 			return GL_SECONDARY;
 	if (strcmp(id, "gl_FogFragCoord") == 0)			return GL_FOGFRAGCOORD;
 		
 	//Result	
 	if (strcmp(id, "gl_FragColor") == 0) 			return GL_FRAGCOLOR;
 	if (strcmp(id, "gl_FragDepth") == 0) 			return GL_FRAGDEPTH;
 	if (strcmp(id, "gl_FragCoord") == 0)			return GL_FRAGCOORD;
 		
 	return NOPREDEFINED;
}

char *registerMap(int varCode){
	switch(varCode){
		case ENV1: 						return "program.env[1]";
		case ENV2:						return "program.env[2]";
		case ENV3: 						return "program.env[3]";
		case GL_LIGHT_HALF: 			return "state.light[0].half";
		case GL_LIGHT_AMBIENT: 			return "state.lightmodel.ambient";
		case GL_MATERIAL_SHININESS: 	return "state.material.shininess";
		case GL_TEXTCOORD: 				return "fragment.textcoord";
		case GL_COLOR: 					return "fragment.color";
		case GL_SECONDARY: 				return "fragment.color.secondary";
		case GL_FOGFRAGCOORD:			return "fragment.fogcoord";
		case GL_FRAGCOLOR: 				return "result.color";
		case GL_FRAGDEPTH: 				return "result.depth";
		case GL_FRAGCOORD: 				return "fragment.position";	
		//case NOPREDEFINED 			return "";
		default: return;
	}
}

char indexMap (int index){
	switch(index){
		case 0: return 'x';
		case 1: return 'y';
		case 2: return 'z';
		case 3: return 'w';
		default: return;
	}
}

void readTree(node *ast){

	if (ast == NULL) return;
	node *temp;
	switch(ast->kind){

		case NESTED_SCOPE_NODE:
			readTree(ast->nested_scope);
			break;

		case INTERMEDIATE_NODE:
			readTree(ast->intermediate);
			break;

		case SCOPE_NODE:
			readTree(ast->scope.declarations);
			readTree(ast->scope.statements);
			break; 

		case DECLARATIONS_NODE:
			readTree(ast->declarations.declarations);
			readTree(ast->declarations.declaration);
			break;

		case STATEMENT_NODE:
			readTree(ast->statement.statements);
			readTree(ast->statement.statement);
			break;

		case DECLARATION_NODE:
			/*TODO: cases when expr is FUNC or OPERATION*/

			//Check if it is CONST
			char instr[20];
			if (ast->declaration.constant == 1) strcpy(instr, "PARAM");
			else strcpy(instr, "TEMP");

			//There is no initialization
			if(ast->declaration.expr == NULL){
				fprintf(outputFile, "%s %s;\n", instr, ast->declaration.id);

			//There is initialization
			} else {
				//Initialization with a variable
				if(ast->declaration.expr->kind == VAR_NODE){
					temp = ast->declaration.expr->variable;

					//Check if it is predefined variable
					char varName[32];
					if (int varCode = isPredefinedVar(temp->identifier.id))
						strcpy(varName, registerMap(varCode));
					else strcpy(varName, temp->identifier.id);

					//Check if it has index
					if (temp->identifier.index == -1){
						fprintf(outputFile, "%s %s = %s;\n",instr, ast->declaration.id, varName);
					} else {
						fprintf(outputFile, "%s %s = %s.%c;\n",instr, ast->declaration.id, varName, indexMap(temp->identifier.index));
					}

				//Initialization with literal or constructor
				} else {
					if (ast->declaration.type->type.size == 0){
						fprintf(outputFile, "%s %s = %f;\n", instr, ast->declaration.id, ast->values[0]);
					} else if (ast->declaration.type->type.size == 1){
						fprintf(outputFile, "%s %s = {%f,%f};\n", instr, ast->declaration.id, ast->values[0],ast->values[1]);
					} else if (ast->declaration.type->type.size == 2){
						fprintf(outputFile, "%s %s = {%f,%f,%f};\n", instr, ast->declaration.id, ast->values[0],ast->values[1], ast->values[2]);
					} else {
						fprintf(outputFile, "%s %s = {%f,%f,%f,%f};\n", instr, ast->declaration.id, ast->values[0],ast->values[1],ast->values[2],ast->values[3]);
					}
				}
			}
			break;



		/*TODO: case below*/

		case IF_STATEMENT_NODE:
			printf("IF_STATEMENT_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			//ast->current_table = current_table;
			//build_all_tables(ast->if_stmt.expr, ast->current_table);
			//build_all_tables(ast->if_stmt.stmt1, ast->current_table); 
			//build_all_tables(ast->if_stmt.stmt2, ast->current_table);
			break;

		case ASSIGNMENT_NODE:
			printf("ASSIGNMENT_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			build_all_tables(ast->assignment.var, ast->current_table);
			build_all_tables(ast->assignment.expr, ast->current_table); */
			break;

		case TYPE_NODE:
			printf("TYPE_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			//ast->current_table = current_table;
			break; 

		case CONSTRUCTOR_NODE:
			printf("CONSTRUCTOR_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			build_all_tables(ast->constructor.type, ast->current_table);
			build_all_tables(ast->constructor.args, ast->current_table);*/
			break;

		case FUNCTION_NODE:
			printf("FUNCTION_NODE\n");
			/*//we are not entering a new scope, so use the passed value of current_table
			ast->current_table = current_table;
			build_all_tables(ast->function.args, ast->current_table);
			break;*/

		case BINARY_EXPRESSION_NODE:
			printf("BINARY_EXPRESSION_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			build_all_tables(ast->binary_expr.left, ast->current_table);
			build_all_tables(ast->binary_expr.right, ast->current_table);*/
			break;

		case UNARY_EXPRESSION_NODE:
			printf("UNARY_EXPRESSION_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			build_all_tables(ast->unary_expr.right, ast->current_table);*/
			break;

		case INT_NODE:
			printf("INT_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			ast->expr_kind = INT;*/
			break;

		case BOOL_NODE:
			printf("BOOL_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			ast->expr_kind = BOOLEAN;*/
			break;

		case FLOAT_NODE:
			printf("FLOAT_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			ast->expr_kind = FLOAT;*/
			break;

		case VAR_NODE:
			printf("VAR_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			build_all_tables(ast->variable, ast->current_table);*/
			break;

		case EXPRESSION_NODE:
			printf("EXPRESSION_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;
			build_all_tables(ast->expression, ast->current_table);*/
			break; 

		case IDENT_NODE:
			printf("INT_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			//ast->current_table = current_table;
			break;

		case ARGUMENTS_NODE:
			printf("ARGUMENTS_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			/*ast->current_table = current_table;  
			build_all_tables(ast->arguments.args, ast->current_table);
			build_all_tables(ast->arguments.expr, ast->current_table);  */    
			break;

		default: break;
	}
}
