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

"!"         {
                yTRACE(NOT);
                return NOT;
            }

"+"         {
                yTRACE(ADD);
                return ADD;
            }

"-"         {
                yTRACE(SUB);
                return SUB;
            }

"*"         {
                yTRACE(MULT);
                return MULT;
            }

"/"         {
                yTRACE(DIV);
                return DIV;
            }

"^"         {
                yTRACE(EXP);
                return EXP;
            }

"="         {
                yTRACE(ASSIGN);
                return ASSIGN;
            }
"&&"        {
                yTRACE(AND);
                return AND;
            }

"||"        {
                yTRACE(OR);
                return OR;
            }
            
"<"         {
                yTRACE(CMP_LT);
                return CMP_LT;
            }

">"         {
                yTRACE(CMP_GT);
                return CMP_GT;
            }

"<="        {
                yTRACE(CMP_LE);
                return CMP_LE;
            }
            
">="        {
                yTRACE(CMP_GE);
                return CMP_GE;
            } 

"=="        {
                yTRACE(CMP_EQ);
                return CMP_EQ;
            }

"!="        {
                yTRACE(CMP_NE);
                return CMP_NE;
            }

","         {
                yTRACE(COMMA);
                return COMMA;
            }
            
";"         {
                yTRACE(SEMICOLON);
                return SEMICOLON;
            }  

"("         {
                yTRACE(LEFT_PAR);
                return LEFT_PAR;
            }

")"         {
                yTRACE(RIGHT_PAR);
                return RIGHT_PAR;
            }

"{"         {
                yTRACE(LEFT_BRACE);
                return LEFT_BRACE;
            }

"}"         {
                yTRACE(RIGHT_BRACE);
                return RIGHT_BRACE;
            }

"["         {
                yTRACE(LEFT_SQUARE);
                return LEFT_SQUARE;
            }

"]"         {
                yTRACE(RIGHT_SQUARE);
                return RIGHT_SQUARE;
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

"lit"       {
                yTRACE(LIT);
                return LIT;
            }
"dp3"       {
                yTRACE(DP3);
                return DP3;
            }
"rsq"       {
                yTRACE(RSQ);
                return RSQ;
            }
"gl_FragColor"  {
                yTRACE(gl_FragColor);
                return gl_FragColor;
            } 
"gl_FragDepth"  {
                yTRACE(gl_FragDepth);
                return gl_FragDepth;
            }         
"gl_FragCoord"  {
                yTRACE(gl_FragCoord);
                return gl_FragCoord;
            }
"gl_TexCoord"   {
                yTRACE(gl_TexCoord);
                return gl_TexCoord;
            }
"gl_Color"      {
                yTRACE(gl_Color);
                return gl_Color;
            }
"gl_Secondary"  {
                yTRACE(gl_Secondary);
                return gl_Secondary;
            } 
"gl_FogFragCoord"   {
                yTRACE(gl_FogFragCoord);
                return gl_FogFragCoord;
            } 
"gl_Light_Half" {
                yTRACE(gl_Light_Half);
                return gl_Light_Half;
            }
"gl_Light_Ambient"  {
                yTRACE(gl_Light_Ambient);
                return gl_Light_Ambient;
            }
"gl_Material_Shininess" {
                yTRACE(gl_Material_Shininess);
                return gl_Material_Shininess;
            }
"env1"      {
                yTRACE(env1);
                return env1;
            }
"env2"      {
                yTRACE(env2);
                return env2;
            }
"env3"      {
                yTRACE(env3);
                return env3;
            }          
        
0|[1-9][0-9]*/[^a-zA-Z0-9] {
                yylval.intValue = atoi(yytext);
                yTRACE(INT_V);
                return INT_V;
            }

(0|[1-9][0-9]*)"."[0-9]+/[^a-zA-Z0-9] {
                yylval.floatValue = atof(yytext);
                yTRACE(FLOAT_V);
                return FLOAT_V;
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