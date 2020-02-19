#ifndef __GR8_CELLNODE_H__
#define __GR8_CELLNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing cell nodes.
   */
  

  class cell_node: public cdk::lvalue_node {
    cdk::expression_node *_address, *_pointer;

  public:
    inline cell_node(int lineno, cdk::expression_node *address, cdk::expression_node *pointer) :
        cdk::lvalue_node(lineno), _address(address), _pointer(pointer){
    }

  public:
    inline cdk::expression_node *address() {
      return _address;
    }
    inline cdk::expression_node *pointer() {
      return _pointer;
    }
    

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_cell_node(this, level);
    }

  };

} // gr8

#endif
