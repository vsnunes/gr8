#ifndef __GR8_MEM_ALLOCNODE_H__
#define __GR8_MEM_ALLOCNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {
  /**
   * Class for describing memory alloc operation.
   */
   class mem_alloc_node : public cdk::unary_expression_node {

   public:
     inline mem_alloc_node(int lineno, cdk::expression_node *argument) :
          cdk::unary_expression_node(lineno, argument) {
     }

     void accept(basic_ast_visitor *sp, int level) {
       sp->do_mem_alloc_node(this, level);
     }

   };
} // gr8

#endif
