#ifndef __GR8_SWEEPINGNODE_H__
#define __GR8_SWEEPINGNODE_H__

#include <cdk/ast/expression_node.h>

namespace gr8 {

  /**
   * Class for describing sweeping-cycle nodes.
   */
  class sweeping_node: public cdk::basic_node {
    cdk::lvalue_node *_counter;
    cdk::expression_node *_start;
    cdk::expression_node *_end;
    cdk::expression_node *_step;
    block_node *_block;

  public:
    inline sweeping_node(int lineno, cdk::lvalue_node *counter, cdk::expression_node *start,
      cdk::expression_node *end, cdk::expression_node *step, block_node *block) :
        basic_node(lineno), _counter(counter), _start(start), _end(end), _step(step), _block(block) {
    }

  public:
    inline cdk::lvalue_node *counter() {
      return _counter;
    }
    inline cdk::expression_node *start() {
      return _start;
    }
    inline cdk::expression_node *end() {
      return _end;
    }
    inline cdk::expression_node *step() {
      return _step;
    }
    inline block_node *block() {
      return _block;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_sweeping_node(this, level);
    }

  };

} // gr8

#endif
