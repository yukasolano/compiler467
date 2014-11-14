#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "symbol.h"

symbol_table *create_table(symbol_table *higher_level) {
	symbol_table *new_table = (symbol_table *)malloc(sizeof(symbol_table));
	memset(new_table, 0, sizeof(*new_table));
	new_table->next_level = higher_level;
	return new_table;
}

//search the current scope for a variable with the correct name
symbol *search_table(symbol_table *table, char *name) {
	int i;
	for(i = 0; i < table->entries; i++) {
		if(strcmp(table->symbol_list[i].name, name) == 0) return &(table->symbol_list[i]);
	}
	return NULL;
}

//search for a variable with the correct name in this scope and all scopes higher than this
symbol *search_all_levels(symbol_table *table, char *name) {
	if(table == NULL) return NULL;
	symbol_table *curr = table;
	symbol *symb = NULL;
	while((symb = search_table(curr, name)) == NULL) {
		if(curr->next_level != NULL) curr = curr->next_level;
		else return NULL;
	}
	return symb;
}

int add_to_table(symbol_table *table, int type, float values[4], char *name, int constant) {
	if(table->entries == SYMBOL_TABLE_SIZE) {
		printf("Symbol table is full.\n");
		return -1;
	}
	if(search_table(table, name) != NULL) {
		printf("A variable named %s is already declared in this scope.\n", name);
		return -1;
	}
	symbol *new_entry = &(table->symbol_list[table->entries]);
	new_entry->type = type;
	new_entry->constant = constant;
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
	return 0;
}

void delete_table(symbol_table *table) {
	if(table != NULL) free(table);
	table = NULL;
}
