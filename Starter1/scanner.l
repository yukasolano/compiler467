%{
/**********************************************************************
 *
 * **YOUR GROUP INFO SHOULD GO HERE**
 *
 *  Interface to the scanner module for CSC467 course project
 **********************************************************************/


#include "common.h"
#include "parser.tab.h"
#include "string.h"


#define YY_USER_INIT { yyin = inputFile; }
#define	yyinput      input
#define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
#define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; yyterminate(); }

int CheckInt(void);
int yyline = 1;

%}
%option noyywrap

WS          [ \t]
DIGIT       [0-9]
LETTER      [a-zA-Z]
LIMITATOR   [ \t\n]

%%
"/*"        {
              int c1      = 0;
              int c2      = yyinput();
              int curline = yyline;
              for(;;) {
                if (c2 == EOF) {
                  fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: Unmatched /*\n", curline);
                  errorOccurred = TRUE;
                  yyterminate();
                }
                if (c1 == '*' && c2 == '/')
                  break;
                c1 = c2;
                c2 = yyinput();
                if (c1 == '\n' && c2 != EOF)
                  yyline++;
              }
            }

{WS}+       {}

"if"        {
                yTRACE(IF);
                return IF;
            }
"else"      {
                yTRACE(ELSE);
                return ELSE;
            }   
"while"     {
                yTRACE(WHILE);
                return WHILE;
            }
"break"     {
                yTRACE(BREAK);
                return BREAK;
            }
"return"    {
                yTRACE(RETURN);
                return RETURN;
            }
"const"     {
                yTRACE(CONST);
                return CONST;
            }
"void"      {
                yTRACE(VOID);
                return VOID;
            }



0|[1-9][0-9]*/{LIMITATOR} {
                yylval.intValue = atoi(yytext);
                yTRACE(INT_V);
                return INT_V;
            }

(0|[1-9][0-9]*)"."[0-9]+/{LIMITATOR} {
                yylval.floatValue = atof(yytext);
                yTRACE(FLOAT_V);
                return FLOAT_V;
            }

"true"      {
                yylval.boolValue = true;
                yTRACE(TRUE_V);
                return TRUE_V;
            }

"false"     {
                yylval.boolValue = false;
                yTRACE(FALSE_V);
                return FALSE_V;
            }
        
[a-zA-Z_][a-zA-Z_0-9]* {
                if(strlen(yytext) > MAX_IDENTIFIER){
                    yERROR("Length larger than MAX_IDENTIFIER")
                }
                yylval.stringValue = (char *)malloc(strlen(yytext));
                strncpy(yylval.stringValue, yytext, strlen(yytext));

                yTRACE(ID);
                return ID;
            }


.           { yERROR("Unknown token"); }

%%