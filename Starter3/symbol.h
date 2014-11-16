#ifndef _SYMBOL_H
#define _SYMBOL_H

#include "common.h"

#define SYMBOL_TABLE_SIZE 256

struct node_;
typedef struct node_ node;

enum {
	NONE,
	INT,
	IVEC2,
	IVEC3,
	IVEC4,
	FLOAT,
	VEC2,
	VEC3,
	VEC4,
	BOOLEAN,
	BVEC2,
	BVEC3,
	BVEC4
};

inline char *var_type(int encoding) {
	switch(encoding) {
		case NONE: return "NONE";
		case INT: return "INT";
		case IVEC2: return "IVEC2";
		case IVEC3: return "IVEC3";
		case IVEC4: return "IVEC4";
		case VEC2: return "VEC2";
		case VEC3: return "VEC3";
		case VEC4: return "VEC4";
		case BVEC2: return "BVEC2";
		case BVEC3: return "BVEC3";
		case BVEC4: return "BVEC4";
		default: return "NO TYPE";
	}
}


typedef struct symbol_ {
	char name[256];
	int type;
	int constant;
	//store as float regardless of actual type
	float value[4];
} symbol;

typedef struct symbol_table_ {
	symbol symbol_list[SYMBOL_TABLE_SIZE];
	int entries;
	//the scope above the current one
	symbol_table_ *next_level;
} symbol_table;

symbol_table *create_table(symbol_table *higher_level);
void print_table(symbol_table *table);
symbol *search_table(symbol_table *table, char *name);
void print_all_levels(symbol_table *table);
symbol *search_all_levels(symbol_table *table, char *name);
symbol_table *build_all_tables(node *ast, symbol_table *current_table);
void delete_table(symbol_table *table);

#endif

