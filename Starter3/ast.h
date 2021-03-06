
#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>
#include "symbol.h"

// Dummy node just so everything compiles, create your own node/nodes
//
// The code provided below is an example ONLY. You can use/modify it,
// but do not assume that it is correct or complete.
//
// There are many ways of making AST nodes. The approach below is an example
// of a descriminated union. If you choose to use C++, then I suggest looking
// into inheritance.

// forward declare
struct node_;
struct Visitor;
typedef struct Visitor Visitor;
typedef struct node_ node;
extern node *ast;

enum {
  DP3,
  LIT,
  RSQ
};

inline char *func_name(int encoding) {
  switch(encoding) {
    case DP3: return "dp3";
    case RSQ: return "rsq";
    case LIT: return "lit";
    default: return "";
  }
}

typedef enum {
  UNKNOWN               = 0,

  SCOPE_NODE            = (1 << 0),
  
  EXPRESSION_NODE       = (1 << 2),
  UNARY_EXPRESSION_NODE = (1 << 2) | (1 << 3),
  BINARY_EXPRESSION_NODE= (1 << 2) | (1 << 4),
  INT_NODE              = (1 << 2) | (1 << 5), 
  FLOAT_NODE            = (1 << 2) | (1 << 6),
  BOOL_NODE             = (1 << 2) | (1 << 7),
  IDENT_NODE            = (1 << 2) | (1 << 8),
  VAR_NODE              = (1 << 2) | (1 << 9),
  FUNCTION_NODE         = (1 << 2) | (1 << 10),
  CONSTRUCTOR_NODE      = (1 << 2) | (1 << 11),

  STATEMENT_NODE        = (1 << 1),
  IF_STATEMENT_NODE     = (1 << 1) | (1 << 12),
  WHILE_STATEMENT_NODE  = (1 << 1) | (1 << 13),
  ASSIGNMENT_NODE       = (1 << 1) | (1 << 14),
  NESTED_SCOPE_NODE     = (1 << 1) | (1 << 15),

  DECLARATION_NODE      = (1 << 16),
  DECLARATIONS_NODE     = (1 << 17),
  TYPE_NODE             = (1 << 18),
  ARGUMENTS_NODE        = (1 << 19),

  INTERMEDIATE_NODE     = (1 << 20)
} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;
  int expr_kind;
  symbol_table *current_table;
  int constant_val;
  float values[4];


  union {

    node *nested_scope;

	 node *intermediate;

    struct {
      node *declarations;
      node *statements;
    } scope;

    struct {
      node *declarations;
      node *declaration;
    } declarations;

    struct {
      node *statements;
      node *statement;
    } statement;

    struct {
      node *type;
      char *id;
      node *expr;
		  int constant;
    } declaration;

    struct {
      node *expr;
      node *stmt1;
      node *stmt2;
    } if_stmt;

    struct {
      node *var;
      node *expr;  
    } assignment;


    struct{
      char* name;
      int size;
    }type;
    

    struct {
      node *type;
      node *args; 
      int qtd_args; 
    } constructor;

    struct {
      int name;
      node *args; 
      int qtd_args; 
    } function;
  
    struct {
      char *op;
      node *right;
    } unary_expr;

    struct {
      char *op;
      node *left;
      node *right;
    } binary_expr;

    int int_val;
    float float_val;
    int bool_val;
    node *expression;
    node *variable;
   


    struct {
      char *id;
      int index;  
    } identifier;

    struct {
      node *args;
      node *expr;
      int qtd_args;
    } arguments;

   
   
   


    // etc.
  };
};




char *node_print(node *ast);
node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);

#endif /* AST_H_ */
