#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen.h"




/*Return 0 in case of success
		-1 otherwise
*/
int genCode(node *ast){
	fprintf(outputFile, "!!ARBfp1.0\n\n");
	readTree(ast, NULL);
	fprintf(outputFile, "END\n");
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
		case GL_TEXTCOORD: 				return "fragment.texcoord";
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
int c = 0;

//look for constants in function calls and declare them
//put declarations into declarations and put the modified argument list into arg_list
/*void declare_const_vars(char arg_list[], char *declarations) {
	int i, j = 0, last_val = 0, last_space = 1, words_seen = 0, vec_start;
	float value;
	char temp[1024], ret[1024], varName[40];
	strcpy(ret, "");
	printf("before %s\n", arg_list);
	for(i = 0; arg_list[i] != '\0'; i++) {
		if(arg_list[i] == '(') {
			//start of a vector

			//allocate a new variable
			sprintf(varName, "tempVar%d", n++);
			sprintf(temp, "TEMP %s;\nMOV %s,", varName, varName);
			strcat(declarations, temp);

			strcpy(temp, "");

			//printf("found vector arglist %s\n", arg_list[i]);

			words_seen = 0; vec_start = 0;
			while(arg_list[i] != ')') {
				if(arg_list[i] == ' ') {
					words_seen++;
					if(words_seen == 1) {i++; continue;} //after the word CALL
					if(words_seen == 2) {vec_start = i; temp[0] = '{';} //after the variable type
					else temp[i - vec_start] = ',';
				}
				else if(vec_start > 0) temp[i - vec_start] = arg_list[i];
				i++;
			}
			//end the vector
			temp[i - vec_start - 1] = '}'; temp[i - vec_start] = ';'; temp[i - vec_start + 1] = '\n'; temp[i - vec_start + 2] = '\0';
			strcat(declarations, temp);
			//printf("\ndeclarations after vec:\n%s\nret:\n%s\n", declarations, ret);
			last_val = 1;

			//add the variable name to the argument list
			strcat(ret, varName);
			j += strlen(varName);
			strcpy(temp, "");
		}
		else if(((arg_list[i] >= '0' && arg_list[i] <= '9') || arg_list[i] == '.') && !last_val && last_space) {
			//part of a scalar
			strcpy(temp, "");
			last_val = 1;
			sscanf(arg_list + i, "%s", temp);
			value = atof(temp);

			//allocate a new variable and copy in the value
			sprintf(varName, "tempVar%d", n++);
			sprintf(temp, "TEMP %s;\nMOV %s,%g;\n", varName, varName, value);
			strcat(declarations, temp);

			//add the variable name to the argument list
			strcat(ret, varName);
			j += strlen(varName);
			strcpy(temp, "");
		}
		else {
			last_val = 0;
			ret[j] = arg_list[i];
			ret[j + 1] = '\0';
			j++;
			strcpy(temp, "");
		}
		if(arg_list[i] == ' ') last_space = 1;
		else last_space = 0;
	}
	strcpy(arg_list, ret);
}

//turn arg list into comma delimited list
void reformat_args(char *arg_list) {
	int i;
	char temp[1024];
	for(i = 0; arg_list[i] != '\0'; i++) {
		if(arg_list[i] == ' ') {
			if(arg_list[i + 1] == '\0') arg_list[i] = '\0'; //last argument; remove trailing space
			else arg_list[i] = ',';
		}
	}
}*/

char *readTree(node *ast, char* condition){
	//va_list args;

	if (ast == NULL) return;
	node *temp;
	char * varName = malloc(sizeof(char)*40);
	char * varNameAux = malloc(sizeof(char)*40);
	char * varNameAux2 = malloc(sizeof(char)*40);
	char * varNameAux3 = malloc(sizeof(char)*40);
	char arg_list[1024], arg_dec[1024];

	//va_start(args, ast); 

	switch(ast->kind){

		case NESTED_SCOPE_NODE:
			readTree(ast->nested_scope, condition);
			return "";

		case INTERMEDIATE_NODE:
			readTree(ast->intermediate, condition);
			return "";

		case SCOPE_NODE:
			readTree(ast->scope.declarations, NULL);
			readTree(ast->scope.statements, condition);
			return "";; 

		case DECLARATIONS_NODE:
			readTree(ast->declarations.declarations, NULL);
			readTree(ast->declarations.declaration, NULL);
			return "";

		case STATEMENT_NODE:
			readTree(ast->statement.statements, condition);
			readTree(ast->statement.statement, condition);
			return "";

		case DECLARATION_NODE:

			//Check if it is CONST
			if (ast->declaration.constant == 1) {
				fprintf(outputFile, "PARAM %s = %s;\n", ast->declaration.id, readTree(ast->declaration.expr, NULL));
	
			} else {	
				
				//There is initialization
				if(ast->declaration.expr != NULL) {

					//Check if the variable initialize with an attributte variable
					int isAttrib = 0;
					if(ast->declaration.expr->kind == VAR_NODE && ast->declaration.expr->variable->kind == IDENT_NODE){
						temp = ast->declaration.expr->variable;
						int varCode = isPredefinedVar(temp->identifier.id);
						if(varCode == GL_TEXTCOORD || varCode == GL_COLOR || varCode == GL_SECONDARY || varCode == GL_FOGFRAGCOORD){
							fprintf(outputFile, "ATTRIB %s = %s;\n", ast->declaration.id, registerMap(varCode));
							isAttrib = 1;
						}
					} 
						
					if(!isAttrib){

						fprintf(outputFile, "TEMP %s;\n", ast->declaration.id);
						//Check if it is literal
						if(ast->declaration.expr->kind == BOOL_NODE ||ast->declaration.expr->kind == FLOAT_NODE || 
							ast->declaration.expr->kind == INT_NODE || ast->declaration.expr->kind == CONSTRUCTOR_NODE){
							sprintf(varName, "%f", ast->declaration.expr->values[0]);	
						} else {
							sprintf(varName, "%s", readTree(ast->declaration.expr, NULL));
						}	
						fprintf(outputFile, "MOV %s,%s;\n", ast->declaration.id, varName);
					}
						
				} else {
					fprintf(outputFile, "TEMP %s;\n", ast->declaration.id);
				}		
			}
			return "";



		case IF_STATEMENT_NODE:
			sprintf(varName, "cond%d", c); c++;
			fprintf(outputFile, "TEMP %s;\n", varName);
			sprintf(varNameAux,readTree(ast->if_stmt.expr, NULL));		//cond_current is [0,1]				
			
			//There is a IF inside another
			if (condition != NULL){	
				fprintf(outputFile, "MUL %s,%s,%s;\n", varName, condition, varNameAux); 	//cond = cond_pre && cond_current
				readTree(ast->if_stmt.stmt1, varName);
				if (ast->if_stmt.stmt2!= NULL){
					fprintf(outputFile, "SUB %s,%s,%s;\n",varNameAux, varNameAux, "1.0");		//cond_cur = cond_cur-1 => cond_cur is [-1,0]
					fprintf(outputFile, "CMP %s,%s,%s,%s;\n", varNameAux, varNameAux, "1.0", "0.0");//cond_cur = -cond_cur => cond_cur is [1,0]
					fprintf(outputFile, "MUL %s,%s,%s;\n", varName, condition, varNameAux); 	//cond = cond_pre && -cond_cur
					readTree(ast->if_stmt.stmt2, varName);
				}

			//This is the top IF	
			} else {
				fprintf(outputFile, "MOV %s,%s;\n",varName, varNameAux);				
				readTree(ast->if_stmt.stmt1, varName);
				if (ast->if_stmt.stmt2!= NULL){
					fprintf(outputFile, "SUB %s,%s,%s;\n",varName, varName, "1.0");			//cond = cond-1 => cond is [-1,0]
					fprintf(outputFile, "CMP %s,%s,%s,%s;\n", varName, varName, "1.0", "0.0");//cond = -cond => cond is [1,0]
					readTree(ast->if_stmt.stmt2, varName);
				}
			}
			
			return "";

		case ASSIGNMENT_NODE:
			
			if (condition == NULL){
				//check if it is literal
				if(ast->assignment.expr->kind == BOOL_NODE ||ast->assignment.expr->kind == FLOAT_NODE || 
					ast->assignment.expr->kind == INT_NODE || ast->assignment.expr->kind == CONSTRUCTOR_NODE){
					sprintf(varName, "%f", ast->assignment.expr->values[0]);
				} else {
					sprintf(varName, "%s", readTree(ast->assignment.expr, NULL));
				}	
				fprintf(outputFile, "MOV %s,%s;\n", readTree(ast->assignment.var, NULL), varName);

			} else {
				sprintf(varName, readTree(ast->assignment.var, NULL));
				sprintf(varNameAux, readTree(ast->assignment.expr, NULL));
				fprintf(outputFile, "SUB %s,%s,%s;\n",condition, condition, "1.0");		//cond = cond-1 => cond is [-1,0]
				fprintf(outputFile,"CMP %s,%s,%s,%s;\n", varName, condition, varName, varNameAux);
				fprintf(outputFile, "ADD %s,%s,%s;\n",condition, condition, "1.0");		//cond = cond+1 => cond is [0,1]
			}
			return "";

		case TYPE_NODE:
			return ""; 

		case CONSTRUCTOR_NODE:
			sprintf(varName, "{%s}",readTree(ast->constructor.args, NULL));
			return varName;

		case FUNCTION_NODE:
			//sprintf(arg_list, node_print(ast->function.args));
			
			//look for compile time constants in the variable list
			//declare_const_vars(arg_list, arg_dec);
			//fprintf(outputFile, arg_dec);

			//change from space delimited arg list to comma delimited
			//reformat_args(arg_list);
			//sprintf(varName, "tempVar%d", n++);
			//fprintf(outputFile, "TEMP %s;\n", varName);
			//char *str_args = node_print(ast->function.args);
			//readTree()

			//Create a tempVar to store the result of the function
			sprintf(varName, "tempVar%d", n); n++;
			fprintf(outputFile, "TEMP %s;\n", varName);
			sprintf(varNameAux,readTree(ast->function.args, NULL));
			
		    if(ast->function.name == DP3){
		    	//fprintf(outputFile, "DP3 %s,%s;\n", varName, arg_list);
		    	fprintf(outputFile, "DP3 %s,%s;\n", varName, varNameAux);
				//return varName;

		    }else if (ast->function.name == LIT){
		    	//fprintf(outputFile, "LIT %s,%s;\n", varName, arg_list);
		    	fprintf(outputFile, "LIT %s,%s;\n", varName, varNameAux);
				//return varName;

		    } else if (ast->function.name == RSQ){
		    	//fprintf(outputFile, "RSQ %s,%s;\n", varName, arg_list);
		    	fprintf(outputFile, "RSQ %s,%s;\n", varName, varNameAux);
				//return varName;
		    	
		    } else{
		    	report_error("Function not acceptable.\n");
		    }
			return varName;

		/*TODO  /  */ 
		case BINARY_EXPRESSION_NODE:
			/*//Left op
			if(ast->binary_expr.left->constant_val == 1){
				sprintf(varNameAux, "%f", ast->binary_expr.left->values[0]);
				sprintf(varName, "tempVar%d", n); n++;
			} else {
				sprintf(varNameAux, readTree(ast->binary_expr.left));
				sprintf(varName, varNameAux);
			}
			//Right op
			if(ast->binary_expr.left->constant_val == 1){
				sprintf(varNameAux2, "%f", ast->binary_expr.right->values[0]);
			} else {
				sprintf(varNameAux2, "%s", readTree(ast->binary_expr.right));
			}
*/
			sprintf(varNameAux,"%s",readTree(ast->binary_expr.left, NULL));
			sprintf(varNameAux2,"%s",readTree(ast->binary_expr.right, NULL));
			if(strncmp(varNameAux, "tempVar", 7) == 0) {
				sprintf(varName, varNameAux);
			} else{
				sprintf(varName, "tempVar%d", n); n++;
				fprintf(outputFile, "TEMP %s;\n", varName);	
			}
			
			if (strcmp(ast->binary_expr.op, "+") == 0) {
				fprintf(outputFile, "ADD %s,%s,%s;\n",varName, varNameAux, varNameAux2);
			} else if (strcmp(ast->binary_expr.op, "-") == 0) {	
				fprintf(outputFile, "SUB %s,%s,%s;\n",varName, varNameAux, varNameAux2);
			} else if (strcmp(ast->binary_expr.op, "*") == 0) {	
				fprintf(outputFile, "MUL %s,%s,%s;\n",varName, varNameAux, varNameAux2);
			} else if (strcmp(ast->binary_expr.op, "/") == 0) {	
				//fprintf(outputFile, "MUL %s,%s,%s;\n",varName, varName, varNameAux);
				printf("OP / not implemented\n");
			} else if (strcmp(ast->binary_expr.op, "^") == 0) {	
				fprintf(outputFile, "POW %s,%s,%s;\n",varName, varNameAux, varNameAux2);

			//result.x = (tmp0.x < tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, "<") == 0) {	
				fprintf(outputFile, "SLT %s,%s,%s;\n",varName, varNameAux, varNameAux2);

			//result.x = (tmp0.x >= tmp1.x) ? 1.0 : 0.0;	
			} else if (strcmp(ast->binary_expr.op, ">=") == 0) {	
				fprintf(outputFile, "SGE %s,%s,%s;\n",varName, varNameAux, varNameAux2);

			//result.x = (tmp0.x > tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, ">") == 0) {	
				fprintf(outputFile, "SLT %s,%s,%s;\n",varName, varNameAux2, varNameAux);

			//result.x = (tmp0.x <= tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, "<=") == 0) {	
				fprintf(outputFile, "SGE %s,%s,%s;\n",varName, varNameAux2, varNameAux);

			//result.x = (tmp0.x == tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, "==") == 0) {
				sprintf(varNameAux2, "tempVar%d", n); n++;	
				fprintf(outputFile, "TEMP %s;\n", varNameAux2);
				fprintf(outputFile, "SGE %s,%s,%s;\n",varName, varNameAux, varNameAux2); 	//A >= B => X = 1
				fprintf(outputFile, "SGE %s,%s,%s;\n",varNameAux, varNameAux2, varNameAux);	//A <= B => A = 1
				fprintf(outputFile, "ADD %s,%s,%s;\n",varName, varName, varNameAux);		//A = X + A (1+1) 
				fprintf(outputFile, "SGE %s,%s,%s;\n",varName, varName, "2.0");				//X >= 2 => X = 1

			//result.x = (tmp0.x != tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, "!=") == 0) {
				sprintf(varNameAux2, "tempVar%d", n); n++;
				fprintf(outputFile, "TEMP %s;\n", varNameAux2);	
				fprintf(outputFile, "SLT %s,%s,%s;\n",varName, varNameAux, varNameAux2); 	//A < B => X = 1
				fprintf(outputFile, "SLT %s,%s,%s;\n",varNameAux, varNameAux2, varNameAux); //A > B => A = 1
				fprintf(outputFile, "ADD %s,%s,%s;\n",varName, varName, varNameAux);		//X = X + A (1+1) 
				fprintf(outputFile, "SGE %s,%s,%s;\n",varName, varName, "1.0");				//X >= 2 => X = 1

			//result.x = (tmp0.x && tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, "&&") == 0) {
				fprintf(outputFile, "MUL %s,%s,%s;\n",varName, varNameAux, varNameAux2); 

			//result.x = (tmp0.x || tmp1.x) ? 1.0 : 0.0;
			} else if (strcmp(ast->binary_expr.op, "||") == 0) {	
				fprintf(outputFile, "ADD %s,%s,%s;\n",varName, varNameAux, varNameAux2); 	//X = A + B	
				fprintf(outputFile, "SGE %s,%s,%s;\n",varName, varName, "1.0");				//X >= 1 => X = 1	

			}else {
				printf("OP %s not implemented\n", ast->binary_expr.op);
			}
			return varName;

		case UNARY_EXPRESSION_NODE:

			sprintf(varNameAux,"%s",readTree(ast->unary_expr.right, NULL));
			if(strncmp(varNameAux, "tempVar",7) == 0) {
				sprintf(varName, varNameAux);
			} else{
				sprintf(varName, "tempVar%d", n); n++;
				fprintf(outputFile, "TEMP %s;\n", varName);	
			}
			if (strcmp(ast->unary_expr.op, "!") == 0) {									//var is [0,1]
				fprintf(outputFile, "SUB %s,%s,%s;\n",varNameAux, varNameAux, "1.0"); 	//var is [-1,0]
				fprintf(outputFile, "CMP %s,%s,%s,%s;\n",varName, varNameAux, "1.0", "0.0");//var is [1,0]
			} else {	
				fprintf(outputFile, "MOV %s,-%s;\n",varName, varNameAux);
			}
			
			return varName;		
			

		case INT_NODE: ; case BOOL_NODE: ; case FLOAT_NODE:
			sprintf(varName, "tempVar%d", n); n++;
			fprintf(outputFile, "TEMP %s;\n", varName);
			fprintf(outputFile, "MOV %s,%f;\n", varName,ast->values[0]);
			return varName;

		
		case VAR_NODE:
			sprintf(varName,readTree(ast->variable, NULL));
			return varName;

		case EXPRESSION_NODE:
			sprintf(varName,readTree(ast->expression, NULL));
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
				sprintf(varName, "%s", readTree(ast->arguments.args, NULL));
			}	
			
			if(ast->arguments.expr != NULL){
				if (ast->arguments.expr->constant_val == 1){
					sprintf(varNameAux, "%f", ast->arguments.expr->values[0]);
				} else {
					sprintf(varNameAux, "%s", readTree(ast->arguments.expr, NULL));
				}
				sprintf(varName, "%s,%s", varName, varNameAux); 
			}   
			return varName;

		default: return "";
	}
}
