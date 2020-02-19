#ifndef __GR8_ADDRESS_OFNODE_H__
#define __GR8_ADDRESS_OFNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {
  /**
   * Class for describing memory addresses.
   */
   class address_of_node : public cdk::expression_node {
     cdk::lvalue_node *_value;

   public:
     inline address_of_node(int lineno, cdk::lvalue_node *value) :
          cdk::expression_node(lineno), _value(value) {
     }

     inline cdk::lvalue_node *value() {
       return _value;
     }

     void accept(basic_ast_visitor *sp, int level) {
       sp->do_address_of_node(this, level);
     }

   };
} // gr8

#endif
