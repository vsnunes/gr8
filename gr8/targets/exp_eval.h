#ifndef __GR8_SEMANTICS_EXP_EVAL_H__
#define __GR8_SEMANTICS_EXP_EVAL_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/symbol.h"
#include "targets/basic_ast_visitor.h"

namespace gr8 {
    
    //this class computes the value of an expression
    class exp_eval: public basic_ast_visitor{
        double _result = 0;

     public:
       exp_eval(std::shared_ptr<cdk::compiler> compiler) :
          basic_ast_visitor(compiler) {
     }

     public:
       ~exp_eval() {
       os().flush();
    }

    int result() const{
        return (int)_result;
    }
    int result(int val){
        return (int)(_result = val);
    }
    double resultDouble() const{
        return _result;
    }
    double resultDouble(double val){
        return _result = val;
    }

    void processBinaryExpression(cdk::binary_expression_node * const node, int lvl, int option);
    
     public:
        // do not edit these lines
        #define __IN_VISITOR_HEADER__
        #include "ast/visitor_decls.h"       // automatically generated
        #undef __IN_VISITOR_HEADER__
        // do not edit these lines: end

  };

 // gr8
    
    
    
}

#endif
