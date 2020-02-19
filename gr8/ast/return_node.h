#ifndef __GR8_RETURN_NODE_H__
#define __GR8_RETURN_NODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing return nodes (only available in blocks).
   */
  class return_node: public cdk::basic_node {
    cdk::expression_node *_value;

  public:
    inline return_node(int lineno, cdk::expression_node *value) :
        cdk::basic_node(lineno), _value(value) {
    }

    inline cdk::expression_node *value() {
      return _value;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }

  };

} // gr8

#endif
