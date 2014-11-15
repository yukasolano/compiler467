#ifndef _SYMBOL_H
#define _SYMBOL_H

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

