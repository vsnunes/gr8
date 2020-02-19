%{
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE               compiler->scanner()->lineno()
#define yylex()            compiler->scanner()->scan()
#define yyerror(s)         compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  double                d;  /* double value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  cdk::lvalue_node     *lvalue;
  basic_type           *type;
  gr8::block_node      *block;
};

%token <i> tINTEGER
%token <d> tDOUBLE
%token <s> tIDENTIFIER tSTRING  
%token <type> tSMALL tHUGE tNEWS tFAKE
%token tIF tTHEN tELSIF tELSE tINPUT
%token tUSE tINITIALLY tPUBLIC
%token tDEFINE tPROCEDURE tFUNCTION
%token tON tAS tDO tUSES tFOR tTO tFROM tBY
%token tBELOW tABOVE tCELL tAT tOBJECTS
%token tAGAIN tSTOP tRETURN tASSIGN 
%token tNULL tTWEET tPOST
%token tSWEEPING tEQUALS



%right tASSIGN
%nonassoc tIF tELSE
%nonassoc tCELL tAGAIN tSTOP tRETURN tTWEET tPOST tDO tINPUT tUSE tSMALL tHUGE tNEWS tFAKE tPUBLIC tDEFINE tPROCEDURE tNULL
%nonassoc tINTEGER tDOUBLE tSTRING tIDENTIFIER
%nonassoc pEXP 
%left '|'
%left '&'
%nonassoc '!'
%left tEQUALS
%left '>' '<'
%left '+' '-'
%left '*' '/' '%'
%nonassoc pLVAL
%nonassoc tUNARY tOBJECTS '?'
%nonassoc '(' ')'


%type <node> stmt var funcdec elsif
%type <sequence> decs insts vars exprs vardecs list funcdecs
%type <expression> expr lvals
%type <lvalue> lval
%type <type> type smallType hugeType newsType
%type <block> block

%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

program: list                                                      {compiler->ast(new cdk::sequence_node(LINE, $1));}
       |                                                           {compiler->ast(new cdk::sequence_node(LINE));}
       ;

list: decs                                                         { $$ = new cdk::sequence_node(LINE, $1); }
    | list decs                                                    { $$ = new cdk::sequence_node(LINE, $2, $1); }
    ;

decs: vardecs  %prec pEXP                                          { $$ = new cdk::sequence_node(LINE, $1); }
    | funcdecs %prec pEXP                                          { $$ = new cdk::sequence_node(LINE, $1); }
    ;

vardecs: var ';'                                                   { $$ = new cdk::sequence_node(LINE, $1); }
       | vardecs var ';'                                           { $$ = new cdk::sequence_node(LINE, $2, $1); } 
       ;
       
funcdecs: funcdec                                                  { $$ = new cdk::sequence_node(LINE, $1); }
        | funcdecs funcdec                                         { $$ = new cdk::sequence_node(LINE, $2, $1); } 
        ;
        
funcdec: tDEFINE tPUBLIC type tFUNCTION tIDENTIFIER tON vars tAS ';' block { $$ = new gr8::function_def_node(LINE, true, *$5, $3, $7, $10);}
   | tDEFINE type tFUNCTION tIDENTIFIER tON vars tAS ';' block             { $$ = new gr8::function_def_node(LINE, false, *$4, $2, $6, $9);}
   | tDEFINE tPUBLIC type tFUNCTION tIDENTIFIER tAS ';' block              { $$ = new gr8::function_def_node(LINE, true, *$5, $3, nullptr, $8);}
   | tDEFINE type tFUNCTION tIDENTIFIER tAS ';' block                      { $$ = new gr8::function_def_node(LINE, true, *$4, $2, nullptr, $7);}
   | tPUBLIC type tFUNCTION tIDENTIFIER tUSES vars ';'                     { $$ = new gr8::function_prototype_node(LINE, true, *$4, $2, $6);}
   | type tFUNCTION tIDENTIFIER tUSES vars ';'                             { $$ = new gr8::function_prototype_node(LINE, false, *$3, $1, $5);}
   | tPUBLIC type tFUNCTION tIDENTIFIER ';'                                { $$ = new gr8::function_prototype_node(LINE, true, *$4, $2, nullptr);}
   | type tFUNCTION tIDENTIFIER ';'                                        { $$ = new gr8::function_prototype_node(LINE, false, *$3, $1, nullptr);}
   | tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tON vars tAS ';' block         { $$ = new gr8::function_def_node(LINE, true, *$4, nullptr, $6, $9);}
   | tDEFINE tPUBLIC tPROCEDURE tIDENTIFIER tAS ';' block                  { $$ = new gr8::function_def_node(LINE, true, *$4, nullptr, nullptr, $7);}
   | tDEFINE tPROCEDURE tIDENTIFIER tON vars tAS ';' block                 { $$ = new gr8::function_def_node(LINE, false, *$3, nullptr, $5, $8);}
   | tDEFINE tPUBLIC tIDENTIFIER tAS ';' block                             { $$ = new gr8::function_def_node(LINE, true, *$3, nullptr, nullptr, $6);}
   | tDEFINE tPROCEDURE tIDENTIFIER tAS ';' block                          { $$ = new gr8::function_def_node(LINE, false, *$3, nullptr, nullptr, $6);}
   | tPUBLIC tPROCEDURE tIDENTIFIER tUSES vars ';'                         { $$ = new gr8::function_prototype_node(LINE, true, *$3, nullptr, $5);}
   | tPROCEDURE tIDENTIFIER tUSES vars ';'                                 { $$ = new gr8::function_prototype_node(LINE, false, *$2, nullptr, $4);}
   | tPUBLIC tPROCEDURE tIDENTIFIER ';'                                    { $$ = new gr8::function_prototype_node(LINE, true, *$3, nullptr, nullptr);}
   | tPROCEDURE tIDENTIFIER ';'                                            { $$ = new gr8::function_prototype_node(LINE, false, *$2, nullptr, nullptr);}
   ;

block:  '{' vardecs insts '}'                                       { $$ = new gr8::block_node(LINE, $2, $3);}
     |  '{' insts '}'                                               { $$ = new gr8::block_node(LINE, nullptr, $2);}
     |  '{' vardecs '}'                                             { $$ = new gr8::block_node(LINE, $2, nullptr);}
     ;

vars: var                                                          { $$ = new cdk::sequence_node(LINE, $1);}
    | vars ',' var                                                 { $$ = new cdk::sequence_node(LINE, $3, $1);}
    ;

var: tPUBLIC type tIDENTIFIER '(' tINITIALLY expr ')'              { $$ = new gr8::variable_dec_node(LINE, true, false, *$3, $2, $6);}
   | tPUBLIC type tIDENTIFIER                                      { $$ = new gr8::variable_dec_node(LINE, true, false, *$3, $2, nullptr);}
   | type tIDENTIFIER                                              { $$ = new gr8::variable_dec_node(LINE, false, false, *$2, $1, nullptr);}
   | type tIDENTIFIER '(' tINITIALLY expr ')'                      { $$ = new gr8::variable_dec_node(LINE, false, false, *$2, $1, $5);}
   | tUSE type tIDENTIFIER                                         { $$ = new gr8::variable_dec_node(LINE, false, true, *$3, $2, nullptr);}
   ;

insts: stmt                                                        { $$ = new cdk::sequence_node(LINE, $1);}
     | insts stmt                                                  { $$ = new cdk::sequence_node(LINE, $2, $1);}
     ;

type: tSMALL                                                       { $$ = new basic_type(4, basic_type::TYPE_INT);}
    | smallType                                                    { $$ = $1;}
    | tHUGE                                                        { $$ = new basic_type(8, basic_type::TYPE_DOUBLE);}
    | hugeType                                                     { $$ = $1;}
    | tNEWS                                                        { $$ = new basic_type(4, basic_type::TYPE_STRING);}
    | newsType                                                     { $$ = $1;}
    ;
     
smallType: tSMALL tFAKE                                            { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = new basic_type(4, basic_type::TYPE_INT);}
         | tSMALL smallType                                        { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype= new basic_type(4, basic_type::TYPE_POINTER);}
         ;

hugeType: tHUGE tFAKE                                              { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = new basic_type(8, basic_type::TYPE_DOUBLE);}
        | tHUGE hugeType                                           { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype= new basic_type(4, basic_type::TYPE_POINTER);}
        ;

newsType: tFAKE tNEWS                                              { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = new basic_type(4, basic_type::TYPE_STRING);} 
        | tFAKE newsType                                           { $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype= new basic_type(4, basic_type::TYPE_POINTER);}
        ;

stmt : expr ';'                                             { $$ = new gr8::evaluation_node(LINE, $1); }
     | tTWEET expr ';'                                                 { $$ = new gr8::tweet_node(LINE, $2); }
     | tPOST expr  ';'                                                 { $$ = new gr8::post_node(LINE, $2); }
     | tSWEEPING lval tFROM expr tTO expr tDO ';' block                { $$ = new gr8::sweeping_node(LINE, $2, $4, $6, new cdk::integer_node(LINE, 1), $9);}
     | tSWEEPING lval tFROM expr tTO expr tBY expr tDO ';' block       { $$ = new gr8::sweeping_node(LINE, $2, $4, $6, $8, $11);}
     | tIF expr tTHEN ';' block tELSE ';' block                        { $$ = new gr8::if_else_node(LINE, $2, $5, $8);}
     | tIF expr tTHEN ';' block                                        { $$ = new gr8::if_node(LINE, $2, $5);}
     | tIF expr tTHEN ';' block elsif                                  { $$ = new gr8::if_else_node(LINE, $2, $5, $6);}
     | tAGAIN tINTEGER ';'                                             { $$ = new gr8::again_node(LINE, $2);}
     | tAGAIN          ';'                                             { $$ = new gr8::again_node(LINE, 1);}
     | tSTOP tINTEGER  ';'                                             { $$ = new gr8::stop_node(LINE, $2);}
     | tSTOP           ';'                                             { $$ = new gr8::stop_node(LINE, 1);}
     | tRETURN expr    ';'                                             { $$ = new gr8::return_node(LINE, $2);}
     | tRETURN         ';'                                             { $$ = new gr8::return_node(LINE, nullptr);}
     | tASSIGN expr tTO lval ';'                                       { $$ = new cdk::assignment_node(LINE, $4, $2); }
     | '{' insts '}'                                                   { $$ = $2; }
     ;

elsif: tELSIF expr tTHEN ';' block                                     { $$ = new gr8::if_node(LINE, $2, $5);}
     | tELSIF expr tTHEN ';' block tELSE ';' block                     { $$ = new gr8::if_else_node(LINE, $2, $5, $8);}
     | tELSIF expr tTHEN ';' block elsif                               { $$ = new gr8::if_else_node(LINE, $2, $5, $6);}
     ;

expr : tINTEGER                                                     { $$ = new cdk::integer_node(LINE, $1); }
     | tDOUBLE                                                      { $$ = new cdk::double_node(LINE, $1); }
     | '+' expr %prec tUNARY                                        { $$ = new gr8::identity_node(LINE, $2); }
     | tSTRING                                                      { $$ = new cdk::string_node(LINE, $1); }
     | '-' expr %prec tUNARY                                        { $$ = new cdk::neg_node(LINE, $2); }
     | expr tOBJECTS                                                { $$ = new gr8::mem_alloc_node(LINE, $1); }
     | expr '+' expr	                                              { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	                                              { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	                                              { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	                                              { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	                                              { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	                                              { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	                                              { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tEQUALS expr                                            { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '!' expr                                                     { $$ = new cdk::not_node(LINE, $2); }
     | expr '&' expr		                                            { $$ = new cdk::and_node(LINE, $1, $3); }
     | expr '|' expr                                                { $$ = new cdk::or_node(LINE, $1, $3); }
     | '(' expr ')'                                                 { $$ = $2; }
     | lvals                                                        { $$ = $1; } 
     | tDO tIDENTIFIER                                              { $$ = new gr8::function_call_node(LINE, nullptr, *$2);}
     | tUSE exprs tFOR tIDENTIFIER                                  { $$ = new gr8::function_call_node(LINE, $2, *$4);}
     | tINPUT                                                       { $$ = new gr8::read_node(LINE); }
     | tNULL                                                        { $$ = new gr8::null_node(LINE); }
     ;

exprs: expr                                                         { $$ = new cdk::sequence_node(LINE, $1); }
     | exprs ',' expr                                               { $$ = new cdk::sequence_node(LINE, $3, $1); }
     ;

lvals: lval    %prec pLVAL                                          { $$ = new cdk::rvalue_node(LINE, $1); } 
     | lval '?'                                                     { $$ = new gr8::address_of_node(LINE, $1);}
     ;

lval : tIDENTIFIER                                                  { $$ = new cdk::identifier_node(LINE, $1); }
     | tCELL expr tAT expr %prec pLVAL                              { $$ = new gr8::cell_node(LINE, $2, $4);}
     | '(' lval ')'                                                 {$$ = $2;}
     ;

%%
