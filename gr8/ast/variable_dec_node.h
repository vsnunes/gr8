#ifndef __GR8_VARIABLE_DEC_NODE_H__
#define __GR8_VARIABLE_DEC_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/basic_type.h>

namespace gr8 {
  /**
   * Class for describing variables declaration.
   */
   class variable_dec_node : public cdk::typed_node {
     bool _public;
     bool _use;
     std::string _id;
     cdk::expression_node *_initValue;

   public:
     inline variable_dec_node(int lineno, bool public_q, bool use,
       std::string id, basic_type *type, cdk::expression_node *initValue) :
          typed_node(lineno), _public(public_q), _use(use), _id(id), _initValue(initValue) {
            this->type(type);
     }

     inline bool isPublic() {
       return _public;
     }

     inline bool use() {
       return _use;
     }

     inline std::string id() {
       return _id;
     }

     inline cdk::expression_node *initValue() {
       return _initValue;
     }

     void accept(basic_ast_visitor *sp, int level) {
       sp->do_variable_dec_node(this, level);
     }

   };
} // gr8

#endif
