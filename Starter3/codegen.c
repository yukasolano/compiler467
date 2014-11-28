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
 		
 	//Attribute
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

int n = 0;

//turn arg list into comma delimited list
void reformat_args(char *arg_list, char *declarations) {
	int i;
	char temp[1024];
	for(i = 0; arg_list[i] != '\0'; i++) {
		if(arg_list[i] == ' ') {
			if(arg_list[i + 1] == '\0') arg_list[i] = '\0'; //last argument; remove trailing space
			else arg_list[i] = ',';
		}
	}
}

char *readTree(node *ast){

	if (ast == NULL) return;
	node *temp;
	char * varName = malloc(sizeof(char)*40);
	char * varNameAux = malloc(sizeof(char)*40);
	char arg_list[1024], arg_dec[1024];
	switch(ast->kind){

		case NESTED_SCOPE_NODE:
			readTree(ast->nested_scope);
			return "";

		case INTERMEDIATE_NODE:
			readTree(ast->intermediate);
			return "";

		case SCOPE_NODE:
			readTree(ast->scope.declarations);
			readTree(ast->scope.statements);
			return "";; 

		case DECLARATIONS_NODE:
			readTree(ast->declarations.declarations);
			readTree(ast->declarations.declaration);
			return "";

		case STATEMENT_NODE:
			readTree(ast->statement.statements);
			readTree(ast->statement.statement);
			return "";

		case DECLARATION_NODE:

			//Check if it is CONST
			if (ast->declaration.constant == 1) {
				fprintf(outputFile, "PARAM %s = %s;\n", ast->declaration.id, readTree(ast->declaration.expr));

			} else {	
				fprintf(outputFile, "TEMP %s;\n", ast->declaration.id);
				//There is initialization
				if(ast->declaration.expr != NULL) {
					fprintf(outputFile, "MOV %s,%s;\n", ast->declaration.id, readTree(ast->declaration.expr));
				}		
			}
			return "";



		/*TODO: IF_STATEMENT*/
		case IF_STATEMENT_NODE:
			printf("IF_STATEMENT_NODE\n");
			//we are not entering a new scope, so use the passed value of current_table
			//ast->current_table = current_table;
			//build_all_tables(ast->if_stmt.expr, ast->current_table);
			//build_all_tables(ast->if_stmt.stmt1, ast->current_table); 
			//build_all_tables(ast->if_stmt.stmt2, ast->current_table);
			return "";

		case ASSIGNMENT_NODE:
			fprintf(outputFile, "MOV %s,%s;\n", readTree(ast->assignment.var), readTree(ast->assignment.expr));
			return "";

		/*TODO ??? */
		case TYPE_NODE:
			printf("TYPE_NODE\n");
			return ""; 

		case CONSTRUCTOR_NODE:
			sprintf(varName, "{%s}",readTree(ast->constructor.args));
			return varName;

		/*TODO FUNCTION_NODE*/
		case FUNCTION_NODE:
			printf("FUNCTION_NODE\n");
			sprintf(arg_list, node_print(ast->function.args));
			reformat_args(arg_list, arg_dec);
			sprintf(varName, "tempVar%d", n++);
			fprintf(outputFile, "TEMP %s;\n", varName);
			//char *str_args = node_print(ast->function.args);
			//readTree()
		    if(ast->function.name == DP3){
		    	fprintf(outputFile, "DP3 %s,%s;\n", varName, arg_list);
				return varName;
		    	/*if(ast->function.qtd_args != 2) report_error("DP3 function should have 2 arguments.\n");
		    	else if (ast->function.args->expr_kind == VEC4 || ast->function.args->expr_kind == VEC3) ast->expr_kind = FLOAT;
		    	else if (ast->function.args->expr_kind == IVEC4 || ast->function.args->expr_kind == IVEC3) ast->expr_kind = INT;
		    	else report_error("DP3 function should have 2 arguments of type VEC4, VEC3, IVEC4 or IVEC3.\n");*/

		    }else if (ast->function.name == LIT){
		    	fprintf(outputFile, "LIT %s,%s;\n", varName, arg_list);
				return varName;
		    	/*if(ast->function.qtd_args != 1 || ast->function.args->expr_kind != VEC4)
		    	 report_error("LIT function should have only one argument of type VEC4.\n");
		    	//LIT function is type VEC4
		    	ast->expr_kind = VEC4;*/

		    } else if (ast->function.name == RSQ){
		    	fprintf(outputFile, "RSQ %s,%s;\n", varName, arg_list);
				return varName;
		    	/*if(ast->function.qtd_args != 1) report_error("RSQ function should have only one argument.\n");
		    	else if (ast->function.args->expr_kind == FLOAT) ast->expr_kind = FLOAT;
		    	else if (ast->function.args->expr_kind == INT) ast->expr_kind = INT;
		    	else report_error("RSQ function should have an argument of type FLOAT or INT.\n");*/
		    } else{
		    	report_error("Function not acceptable.\n");
		    }
					/*//we are not entering a new scope, so use the passed value of current_table
					ast->current_table = current_table;
					build_all_tables(ast->function.args, ast->current_table);*/
			return "";

		/*TODO < > >= <= == != / ^ && ||*/ 
		case BINARY_EXPRESSION_NODE:
			printf("BINARY_EXPRESSION_NODE\n");
			sprintf(varName,"%s",readTree(ast->binary_expr.left));
			sprintf(varNameAux,"%s",readTree(ast->binary_expr.right));
			if (strcmp(ast->binary_expr.op, "+") == 0) {
				fprintf(outputFile, "ADD %s,%s,%s;\n",varName, varName, varNameAux);
			} else if (strcmp(ast->binary_expr.op, "-") == 0) {	
				fprintf(outputFile, "SUB %s,%s,%s;\n",varName, varName, varNameAux);
			} else if (strcmp(ast->binary_expr.op, "*") == 0) {	
				fprintf(outputFile, "MUL %s,%s,%s;\n",varName, varName, varNameAux);
			}else {
				printf("OP %s not implemented\n", ast->binary_expr.op);
			}
			return varName;

		/*TODO !*/
		case UNARY_EXPRESSION_NODE:
			printf("UNARY_EXPRESSION_NODE\n");
			sprintf(varName,"%s",readTree(ast->unary_expr.right));
			if (strcmp(ast->unary_expr.op, "!") == 0) {
				printf("OP ! not implemented!\n");
			} else {	
				fprintf(outputFile, "MOV %s,-%s\n",varName, varName);
			}
			
			return varName;		
			

		case INT_NODE: ; case BOOL_NODE: ; case FLOAT_NODE:
			sprintf(varName, "tempVar%d", n); n++;
			fprintf(outputFile, "TEMP %s;\n", varName);
			fprintf(outputFile, "MOV %s,%f;\n", varName,ast->values[0]);
			return varName;

		
		case VAR_NODE:
			sprintf(varName,"%s",readTree(ast->variable));
			return varName;

		case EXPRESSION_NODE:
			sprintf(varName,"%s",readTree(ast->expression));
			return varName;

		case IDENT_NODE:
			//Check if it is predefined variable
			if (int varCode = isPredefinedVar(ast->identifier.id))
				strcpy(varName, registerMap(varCode));
			else strcpy(varName, ast->identifier.id);

			//Check if it has index
			if (ast->identifier.index > -1){
				sprintf(varName, "%s.%c", varName, indexMap(ast->identifier.index));
			}
			return varName;


		case ARGUMENTS_NODE:
			if(ast->arguments.args->constant_val == 1){
				sprintf(varName, "%f", ast->arguments.args->values[0]);
			} else {
				sprintf(varName, "%s", readTree(ast->arguments.args));
			}	
			
			if(ast->arguments.expr != NULL){
				if (ast->arguments.expr->constant_val == 1){
					sprintf(varNameAux, "%f", ast->arguments.expr->values[0]);
				} else {
					sprintf(varNameAux, "%s", readTree(ast->arguments.expr));
				}
				sprintf(varName, "%s,%s", varName, varNameAux); 
			}   
			return varName;

		default: return "";
	}
}
