#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "ast.h"
#include "symbol.h"
#include "common.h"


enum {
	NOPREDEFINED,
	ENV1,
	ENV2,
	ENV3,
	GL_LIGHT_HALF,
	GL_LIGHT_AMBIENT,
	GL_MATERIAL_SHININESS,
 	GL_TEXTCOORD,
 	GL_COLOR,
 	GL_SECONDARY,
 	GL_FOGFRAGCOORD, 
 	GL_FRAGCOLOR,
 	GL_FRAGDEPTH, 
 	GL_FRAGCOORD
};
void readTree(node *ast);
int genCode ( node *ast);

#endif