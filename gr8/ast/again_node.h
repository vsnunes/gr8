#ifndef __GR8_AGAIN_NODE_H__
#define __GR8_AGAIN_NODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing again nodes (only available in cycles).
   */
  class again_node: public cdk::basic_node {
    int _cycle;

  public:
    inline again_node(int lineno, int cycle) :
        cdk::basic_node(lineno), _cycle(cycle) {
    }

    inline int cycle() {
      return _cycle;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_again_node(this, level);
    }

  };

} // gr8

#endif
