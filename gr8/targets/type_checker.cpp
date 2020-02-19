#include <string>
#include "targets/type_checker.h"
#include "targets/enter_eval.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void gr8::type_checker::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  // EMPTY 
}

void gr8::type_checker::do_block_node(gr8::block_node * const node, int lvl) {
  // EMPTY  
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_nil_node(cdk::nil_node * const node, int lvl) {
  //EMPTY
}

void gr8::type_checker::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("not argument must be int");
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_and_node(cdk::and_node * const node, int lvl) {
  processBinaryExpressionInts(node, lvl);
}

void gr8::type_checker::do_or_node(cdk::or_node * const node, int lvl) {
  processBinaryExpressionInts(node, lvl);
}

void gr8::type_checker::do_tweet_node(gr8::tweet_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_POINTER)
    throw std::string("pointer type is not allowed inside tweet");
}

void gr8::type_checker::do_post_node(gr8::post_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_POINTER)
    throw std::string("pointer type is not allowed inside post");
}

void gr8::type_checker::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {
  node->counter()->accept(this, lvl + 2);
  
}

void gr8::type_checker::do_function_def_node(gr8::function_def_node * const node, int lvl) {

  std::string id = node->id();

  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
  //check if function exists in symbol table
  if (symbol != nullptr) {
    if (symbol->functionType() == 1) //already exists a prototype no need to add new symbol
      symbol->functionType(0);
  }
  else {
    //In case we define a procedure
    if (node->type() == nullptr)
      node->type(new basic_type(0, basic_type::TYPE_VOID));

    std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(node->type(), id, 0);

    symbol->functionType(0); //mark as function def

    if(!_symtab.insert(id, symbol))
        throw id + " redeclared";

    _parent->set_new_symbol(symbol);
  }
}

void gr8::type_checker::do_function_prototype_node(gr8::function_prototype_node * const node, int lvl) {
  
  std::string id = node->id();

   //In case we define a procedure
    if (node->type() == nullptr)
      node->type(new basic_type(0, basic_type::TYPE_VOID));

  std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(node->type(), id, 0);
  symbol->functionType(1); //mark as prototype
  if(!_symtab.insert(id, symbol))
    throw id + " prototype redeclared";

  gr8::enter_eval *enter = new enter_eval(_compiler);
  if (node->vars() != nullptr) {
    node->vars()->accept(enter, lvl);
  }
  //store type in order to check if this argument need to be converted I2D
  symbol->addfunctionArgsId(enter->size_of_args());

  _parent->set_new_symbol(symbol);
}

void gr8::type_checker::do_function_call_node(gr8::function_call_node * const node, int lvl) {
  std::string id = node->id();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
  //check if function exists in symbol table
  if (symbol == nullptr) {
    throw id + " not declared on this scope";
  }

  //check function args if function contains args
  if (node->params())
    node->params()->accept(this, lvl + 2);


  node->type(symbol->type());
}

void gr8::type_checker::do_variable_dec_node(gr8::variable_dec_node * const node, int lvl) {
  std::string id = node->id();
  std::shared_ptr<gr8::symbol> symbol = std::make_shared<gr8::symbol>(node->type(), id, 0);
  if(_symtab.find_local(id) != nullptr)
      throw id + " redeclared";

  _symtab.insert(id, symbol);
  
  if(node->initValue() != nullptr){
      node->initValue()->accept(this, lvl + 2);
      
    if(node->type()->name() == basic_type::TYPE_DOUBLE && node->initValue()->type()->name() == basic_type::TYPE_INT)
      node->initValue()->type(new basic_type(8, basic_type::TYPE_DOUBLE));
      
    if (node->type()->name() != node->initValue()->type()->name())
      throw std::string("wrong type for initial value");

    if (node->type()->name() == basic_type::TYPE_POINTER) {
      node->initValue()->type()->_subtype = node->type()->_subtype;
    }
    
  }
      
  _parent->set_new_symbol(symbol);
}

void gr8::type_checker::do_cell_node(gr8::cell_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->pointer()->accept(this, lvl);
  if (node->pointer()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("index base must be a pointer");
  
  node->address()->accept(this, lvl);
  if (node->address()->type()->name() != basic_type::TYPE_INT)
      throw std::string("invalid address, must be an int");

  node->type(node->pointer()->type()->subtype());
}

void gr8::type_checker::do_identity_node(gr8::identity_node * const node, int lvl) {
  processUnaryExpressionDoubles(node, lvl);
}

void gr8::type_checker::do_mem_alloc_node(gr8::mem_alloc_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("invalid objects value, must be an int");

  node->type(new basic_type(4, basic_type::TYPE_POINTER));

  node->type()->_subtype = objectType;
}

void gr8::type_checker::do_stop_node(gr8::stop_node * const node, int lvl) {
  //EMPTY
}

void gr8::type_checker::do_again_node(gr8::again_node * const node, int lvl) {
  //EMPTY
}

void gr8::type_checker::do_return_node(gr8::return_node * const node, int lvl) {
  node->value()->accept(this, lvl);
}

void gr8::type_checker::do_address_of_node(gr8::address_of_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->value()->accept(this, lvl);
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
  node->type()->_subtype = node->value()->type();
}

void gr8::type_checker::do_null_node(gr8::null_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

void gr8::type_checker::processUnaryExpressionDoubles(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT && node->argument()->type()->name() != basic_type::TYPE_DOUBLE)
      throw std::string("wrong type in argument of unary expression");

  if (node->argument()->type()->name() != basic_type::TYPE_DOUBLE)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  else
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT )
      throw std::string("wrong type in argument of unary expression");

  // in Simple, expressions were always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpressionDoubles(node, lvl);
}

//---------------------------------------------------------------------------

void gr8::type_checker::processBinaryExpressionInts(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
      throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
      throw std::string("wrong type in right argument of binary expression");

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void gr8::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE)
      throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE)
      throw std::string("wrong type in right argument of binary expression");

  if (node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_DOUBLE)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  else
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}


void gr8::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in right argument of binary expression");
  
  //checks if both operands are pointers
  if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER)
      throw std::string("illegal add expression between two pointers");
  
  //checks if you're adding a pointer with a double
  else if((node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER) && (node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE))
      throw std::string("illegal add expression between pointer and double");

  if (node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() 
  == basic_type::TYPE_INT)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  
  else if ( (node->left()->type()->name() == basic_type::TYPE_INT) && (node->right()->type()->name() == basic_type::TYPE_POINTER))
      {node->type(new basic_type(4, basic_type::TYPE_POINTER));
        node->type()->_subtype = node->right()->type()->_subtype;
      }
  
  else if ( (node->left()->type()->name() == basic_type::TYPE_POINTER) && (node->right()->type()->name() == basic_type::TYPE_INT))
      {node->type(new basic_type(4, basic_type::TYPE_POINTER));
        node->type()->_subtype = node->left()->type()->_subtype;
      }
  else
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in right argument of binary expression");
  
  //checks if you're subtracting a pointer with a double
  if((node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER) && (node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE))
      throw std::string("illegal sub expression between pointer and double");
  

  if (node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_DOUBLE)
      node->type(new basic_type(4, basic_type::TYPE_INT));
  
  else if ( (node->left()->type()->name() == basic_type::TYPE_INT || node->right()->type()->name() == basic_type::TYPE_INT) && (node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER))
      throw std::string("wrong types for subtraction pointers and ints");
  
  else if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER) 
      {
        if (node->left()->type()->_subtype->name() != node->right()->type()->_subtype->name())
          throw std::string("wrong subtype of pointers in sub");
      node->type(new basic_type(4, basic_type::TYPE_INT)); //subtraction of pointers is the number of items
      node->type()->_subtype = node->left()->type()->_subtype;

      }
  else
      node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void gr8::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void gr8::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void gr8::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpressionInts(node, lvl);
}

void gr8::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void gr8::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

void gr8::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  // EMPTY
}

void gr8::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE && node->left()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && node->right()->type()->name() != basic_type::TYPE_POINTER)
      throw std::string("wrong type in right argument of binary expression");
  
  //checks if you're adding a pointer with a double
  if((node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER) && (node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE))
      throw std::string("illegal equals expression between pointer and double");
  

  node->type(new basic_type(4, basic_type::TYPE_INT));

}
//---------------------------------------------------------------------------

void gr8::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);

  if (symbol != nullptr) {
    node->type(symbol->type());
  } else {
    throw id ;
  }
}

void gr8::type_checker::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  try {
    node->lvalue()->accept(this, lvl);
    node->type(node->lvalue()->type());
  } catch (const std::string &id) {
    throw "undeclared variable '" + id + "'";
  }
}

void gr8::type_checker::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;
    node->lvalue()->accept(this, lvl);

  if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER){
    objectType = node->lvalue()->type()->_subtype;
  }
  node->rvalue()->accept(this, lvl + 2);
  if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT)
      node->rvalue()->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  
  else if(node->lvalue()->type()->name() != node->rvalue()->type()->name())
      throw std::string("different types in left and right arguments of assignment");

  node->type(node->lvalue()->type());
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void gr8::type_checker::do_read_node(gr8::read_node * const node, int lvl) {
    // EMPTY 
}

void gr8::type_checker::do_if_node(gr8::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void gr8::type_checker::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}
