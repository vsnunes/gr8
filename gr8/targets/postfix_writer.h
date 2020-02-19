#ifndef __GR8_SEMANTICS_POSTFIX_WRITER_H__
#define __GR8_SEMANTICS_POSTFIX_WRITER_H__

#include <string>
#include <iostream>
#include <list>
#include <cdk/symbol_table.h>
#include <cdk/emitters/basic_postfix_emitter.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace gr8 {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class postfix_writer: public basic_ast_visitor {
    cdk::symbol_table<gr8::symbol> &_symtab;
    cdk::basic_postfix_emitter &_pf;
    int _lbl;
    bool in_context = false;
    std::string in_context_id = "";
    bool in_context_arg = false;
    int offset_context = 0;
    int cycle_counter = 0;
    bool needConvertI2D = false;

    /** Store id of function prototype **/
    std::list<std::string> ids;

    std::vector<int> cycleLabels;

    /** Offset of the first function argument **/
    static const int OFFSET_CONTEXT_ARGS_START = 8;
    int offset_context_args = OFFSET_CONTEXT_ARGS_START;
    int expression_val = 0;

  public:
    postfix_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<gr8::symbol> &symtab,
                   cdk::basic_postfix_emitter &pf) :
        basic_ast_visitor(compiler), _symtab(symtab), _pf(pf), _lbl(0) {
    }

  public:
    ~postfix_writer() {
      os().flush();
    }

  protected:
    //Checks and converts integer to doubles when one of the binary expression argument is a double
    bool processMixedIntsAndDoublesBinOp(cdk::binary_expression_node *node, int lvl);

  private:
    /** Method used to generate sequential labels. */
    inline std::string mklbl(int lbl) {
      std::ostringstream oss;
      if (lbl < 0)
        oss << ".L" << -lbl;
      else
        oss << "_L" << lbl;
      return oss.str();
    }
    
    inline std::string mkcycle(int counter) {
      std::ostringstream oss;
      if (counter < 0)
        oss << ".L" << -counter;
      else
        oss << "_L" << counter;
      return oss.str();
    }

  public:
  // do not edit these lines
#define __IN_VISITOR_HEADER__
#include "ast/visitor_decls.h"       // automatically generated
#undef __IN_VISITOR_HEADER__
  // do not edit these lines: end

  };

} // gr8

#endif
