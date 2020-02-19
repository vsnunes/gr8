#ifndef __GR8_FUNCTION_PROTOTYPENODE_H__
#define __GR8_FUNCTION_PROTOTYPENODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/basic_type.h>

namespace gr8 {
  /**
   * Class for describing function or procedures prototypes (header).
   */
   class function_prototype_node : public cdk::typed_node {
     bool _public;
     std::string _id;
     cdk::sequence_node *_vars;

   public:
     inline function_prototype_node(int lineno, bool public_quant,
         std::string id, basic_type *type, cdk::sequence_node *vars) :
         typed_node(lineno), _public(public_quant), _id(id), _vars(vars) {
           this->type(type);
     }

     inline bool isPublic() {
       return _public;
     }

     inline std::string id() {
       return _id;
     }

     inline cdk::sequence_node *vars() {
       return _vars;
     }

     void accept(basic_ast_visitor *sp, int level) {
       sp->do_function_prototype_node(this, level);
     }

   };
} // gr8

#endif
