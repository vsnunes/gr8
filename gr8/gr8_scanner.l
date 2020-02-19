%option c++ prefix="gr8_scanner_" outfile="gr8_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include <cdk/ast/lvalue_node.h>
#include "gr8_parser.tab.h"

std::vector<int> stack;
int el;
int last;
long hept;
/* Initial identation starts the stack with the number of spaces
 * If its start with no identation we assume -1 to always compare with 0 identation. */
int initial_identation = -1;

// don't change this
#define yyerror LexerError
%}

H_DIGIT	 [0-6]{1,3}
SPACES	 [ \t]+
CONTINUE "..."[\n]

%x X_STRING X_COMMENT X_IGNORE X_IDENT X_STRING_CONTAINER X_CONTINUE X_INST

%%

"!!".*$                 ; /* ignore comments */
^" "+$                  ;
^"\t"+                  el = 8 * yyleng; yy_push_state(X_IDENT); 
^" "*                   initial_identation = yyleng; yy_push_state(X_INST);
^[^" "\t\n]             yyless(0); yy_push_state(X_INST);

[\n][^" "\t\n]            yyless(yyleng - 1); el = -1; yy_push_state(X_IDENT);
[\n][\t]+               el = 8 * yyleng; yy_push_state(X_IDENT);
[\n][" "]+              yyless(0); el = yyleng; yy_push_state(X_IDENT);
[\n][" "\t]+$ ;

<X_IDENT>[\t]+           {
	                      int spaces;
	                      if (el % 8 == 0)
	                         spaces = 8 * yyleng;
	                      else spaces = 8 - (el % 8) + 8 * (yyleng - 1);

	                      for (int i = 0; i < spaces; i++)
		                  unput(' ');
}
<X_IDENT>" "+          el += yyleng;
<X_IDENT>.              {
                         if (stack.size() == 0)
                            last = initial_identation;
                         else last = stack.back();
                         if (el > last) {
                            stack.push_back(el);
                            yy_pop_state();
                            yyless(0);
                            yy_push_state(X_INST);
                            return *"{";
                         }

                         if (el < last) {
                            stack.pop_back();
                            yyless(0);
                            return *"}";
                         } 

                         if (el == last) {
                            yyless(0);
                            yy_pop_state();
                            yy_push_state(X_INST);
                         }
                        }

<X_INST>"public"                return tPUBLIC;
<X_INST>"define"                return tDEFINE;
<X_INST>"procedure"             return tPROCEDURE;
<X_INST>"function"              return tFUNCTION;
<X_INST>"on"                    return tON;
<X_INST>"as"                    return tAS;
<X_INST>"small"                 return tSMALL;
<X_INST>"huge"                  return tHUGE;
<X_INST>"news"                  return tNEWS;
<X_INST>"use"                   return tUSE;
<X_INST>"fake"                  return tFAKE;
<X_INST>"cell"                  return tCELL;
<X_INST>"at"                    return tAT;
<X_INST>"objects"               return tOBJECTS;
<X_INST>"initially"             return tINITIALLY;
<X_INST>"do"                    return tDO;
<X_INST>"uses"                  return tUSES;
<X_INST>"for"                   return tFOR;
<X_INST>"return"                return tRETURN;
<X_INST>"plus"                  return *"+";
<X_INST>"minus"                 return *"-";
<X_INST>"times"                 return *"*";
<X_INST>"over"                  return *"/";
<X_INST>"modulus"               return *"%";
<X_INST>"below"                 return *"<";
<X_INST>"above"                 return *">";
<X_INST>"equals"                return tEQUALS;
<X_INST>"not"                   return *"!";
<X_INST>"and"                   return *"&";
<X_INST>"or"                    return *"|";
<X_INST>"null"                  return tNULL;
<X_INST>"tweet"                 return tTWEET;
<X_INST>"post"                  return tPOST;
<X_INST>"again"                 return tAGAIN;
<X_INST>"stop"                  return tSTOP;
<X_INST>"assign"                return tASSIGN;
<X_INST>"then"                  return tTHEN;
<X_INST>"elsif"                 return tELSIF;
<X_INST>"sweeping"              return tSWEEPING;
<X_INST>"to"                    return tTO;
<X_INST>"from"                  return tFROM;
<X_INST>"by"                    return tBY;
<X_INST>"input"                 return tINPUT; 
<X_INST>"if"                    return tIF; 
<X_INST>"else"                  return tELSE; 


<X_INST>\"       yy_push_state(X_STRING_CONTAINER); yy_push_state(X_STRING); yylval.s = new std::string("");


<X_INST>[A-Za-z][A-Za-z0-9-]*   yylval.s = new std::string(yytext); return tIDENTIFIER;

<X_INST>0[0-6]+                                 yylval.i = strtol(yytext, nullptr, 7); return tINTEGER;
<X_INST>[0-9]+                                  yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;
<X_INST>[0-9]*\.[0-9]+([Ee][-+]?[0-9]+)?        yylval.d = std::stod(yytext); return tDOUBLE;
<X_INST>[0-9]+\.[0-9]*([Ee][-+]?[0-9]+)?        yylval.d = std::stod(yytext); return tDOUBLE;
<X_INST>[0-9]+([Ee][-+]?[0-9]+)                 yylval.d = std::stod(yytext); return tDOUBLE;  

<X_INST>"<<"                          yy_pop_state(); yy_push_state(X_COMMENT);
<X_INST>"!!".*$                       yy_pop_state(); /* ignore comments */

<X_INST>[().,?!&|]                              return *yytext;
<X_INST>{SPACES}             ; /* ignore whitespace */      
<X_INST>{CONTINUE}                    yy_push_state(X_CONTINUE);

<X_INST>\n       yyless(0); yy_pop_state(); return *";";
<X_INST><<EOF>>  yy_pop_state(); return *";";



\"                            yy_push_state(X_STRING_CONTAINER); yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\"                  yy_pop_state();
<X_STRING>"~0"			      yy_push_state(X_IGNORE);
<X_STRING>"~t"			      yytext[1] = '\t'; *yylval.s += yytext + 1;
<X_STRING>"~n"			      yytext[1] = '\n'; *yylval.s += yytext + 1;
<X_STRING>"~r"			      yytext[1] = '\r'; *yylval.s += yytext + 1;
<X_STRING>"~~"			      *yylval.s += yytext + 1;
<X_STRING>"~\""			      *yylval.s += yytext + 1;
<X_STRING>"~"{H_DIGIT}	      hept = strtol(yytext + 1, nullptr, 7); if (hept > 255) yyerror("hept out of limits"); *yylval.s += ((char)hept); 
<X_STRING>"~".			      yyerror("invalid tilde in string");
<X_STRING>{CONTINUE}          yy_push_state(X_CONTINUE);
<X_STRING>.                   *yylval.s += yytext;
<X_STRING>\n                  yyerror("newline in string");

{CONTINUE}                    yy_push_state(X_CONTINUE);

<X_CONTINUE>[" "\t|\n]+         ;
<X_CONTINUE>.                 yyless(0); yy_pop_state();

<X_STRING_CONTAINER>\"        yy_push_state(X_STRING);
<X_STRING_CONTAINER>"<<"      yy_push_state(X_COMMENT);
<X_STRING_CONTAINER>{SPACES}  ;
<X_STRING_CONTAINER>.|\n      yyless(0); yy_pop_state(); return tSTRING;
<X_STRING_CONTAINER><<EOF>>   yy_pop_state(); return tSTRING;


<X_IGNORE>\"			      yy_pop_state(); yy_pop_state();
<X_IGNORE>{CONTINUE}          ;
<X_IGNORE>.				      ;
<X_IGNORE>\n			      yyerror("newline in string");

"<<"					      yy_push_state(X_COMMENT);
<X_COMMENT>"<<"			      yy_push_state(X_COMMENT);
<X_COMMENT>">>"			      yy_pop_state();	
<X_COMMENT>.|\n			      ;


0[0-6]+                                 yylval.i = strtol(yytext, nullptr, 7); return tINTEGER;
[0-9]+                                  yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;
[0-9]*\.[0-9]+([Ee][-+]?[0-9]+)?        yylval.d = std::stod(yytext); return tDOUBLE;
[0-9]+\.[0-9]*([Ee][-+]?[0-9]+)?        yylval.d = std::stod(yytext); return tDOUBLE;
[0-9]+([Ee][-+]?[0-9]+)                 yylval.d = std::stod(yytext); return tDOUBLE;

[().,?!&|]                              return *yytext;

{SPACES}             ; /* ignore whitespace */


<<EOF>>               if (stack.size() > 0) {stack.pop_back(); return *"}";} else return *yytext;
.                     yyerror("Unknown character");

%%
