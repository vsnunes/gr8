#ifndef __GR8_SEMANTICS_ENTER_EVAL_H__
#define __GR8_SEMANTICS_ENTER_EVAL_H__

#include <string>
#include <iostream>
#include <cdk/symbol_table.h>
#include <cdk/ast/basic_node.h>
#include "targets/symbol.h"
#include "targets/basic_ast_visitor.h"

namespace gr8 {
    
    //this class computes the size of the functions local variables
    class enter_eval: public basic_ast_visitor{
        int _size_of_args = 0;

     public:
       enter_eval(std::shared_ptr<cdk::compiler> compiler) :
          basic_ast_visitor(compiler) {
     }

     public:
       ~enter_eval() {
       os().flush();
    }

    int size_of_args() const{
        return _size_of_args;
    }
    int size_of_args(int val){
        return _size_of_args = val;
    }
    
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
