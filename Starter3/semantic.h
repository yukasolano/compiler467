#ifndef _SEMANTIC_H
#define _SEMANTIC_H

#include "ast.h"
#include "symbol.h"
#include "common.h"

void fill_types(node *ast);

int semantic_check( node *ast);

#endif
