#ifndef __GR8_FUNCTION_CALL_NODE_H__
#define __GR8_FUNCTION_CALL_NODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {
  /**
   * Class for describing function or procedures definition.
   */
   class function_call_node : public cdk::expression_node {
     cdk::sequence_node *_params;
     std::string _id;


   public:
     inline function_call_node(int lineno, cdk::sequence_node *params, std::string id) :
          cdk::expression_node(lineno), _params(params), _id(id){
     }

  public:
    inline cdk::sequence_node *params() {
      return _params;
    }

    inline std::string id() {
      return _id;
    }

     void accept(basic_ast_visitor *sp, int level) {
       sp->do_function_call_node(this, level);
     }

   };
} // gr8

#endif
