#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "targets/enter_eval.h"
#include "targets/exp_eval.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_nil_node(cdk::nil_node * const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

void gr8::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  _pf.DOUBLE(node->value()); // push a double
  needConvertI2D = false;
}

void gr8::postfix_writer::do_not_node(cdk::not_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl;
  node->argument()->accept(this, lvl); // determine the value
  _pf.INT(0);
  _pf.EQ();
  _pf.JNZ("NOTtrue" + mklbl(lbl = ++_lbl));
  _pf.INT(0); //true
  _pf.JMP("NOTend" + mklbl(lbl));
  _pf.LABEL("NOTtrue" + mklbl(lbl));
  _pf.INT(1); //false
  _pf.LABEL("NOTend" +  mklbl(lbl));
}

void gr8::postfix_writer::do_and_node(cdk::and_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl;
  node->left()->accept(this, lvl);
  _pf.INT(0);
  _pf.NE();
  _pf.JZ("ANDfalse" + mklbl(lbl = ++_lbl)); //already eval left and it was false so return false
  _pf.TRASH(4); //dont care about left eval the return now depends on right argument
  node->right()->accept(this, lvl);
  _pf.INT(0);
  _pf.NE();
  _pf.JZ("ANDfalse" + mklbl(lbl));
  //true
  _pf.INT(1);
  _pf.JMP("ANDend" + mklbl(lbl));
  _pf.LABEL("ANDfalse" + mklbl(lbl));
  //false
  _pf.INT(0);
  _pf.LABEL("ANDend" + mklbl(lbl));

}

void gr8::postfix_writer::do_or_node(cdk::or_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl;
  node->left()->accept(this, lvl);
  _pf.INT(1);
  _pf.EQ();
  _pf.JNZ("ORtrue" + mklbl(lbl = ++_lbl)); //already eval left and it was true so return true
  _pf.TRASH(4); //dont care about left eval the return now depends on right argument
  node->right()->accept(this, lvl);
  _pf.INT(1);
  _pf.EQ();
  _pf.JMP("ORend" + mklbl(lbl));
  _pf.LABEL("ORtrue" + mklbl(lbl));
  _pf.INT(1);
  _pf.LABEL("ORend" + mklbl(lbl));
}

void gr8::postfix_writer::do_tweet_node(gr8::tweet_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
      _pf.CALL("printd");
      _pf.TRASH(8);
  }
  
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
}

void gr8::postfix_writer::do_post_node(gr8::post_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE){
      _pf.CALL("printd");
      _pf.TRASH(8);
  }
  
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  
  else {
    std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
    exit(1);
  }
  _pf.CALL("println"); // print a newline

}

void gr8::postfix_writer::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {
  cycleLabels.push_back(++cycle_counter);
  std::string lbl = mkcycle(cycle_counter);
  
  node->start()->accept(this, lvl);
  node->counter()->accept(this, lvl);
  _pf.STINT();
  
  _pf.LABEL("forTest" + lbl);
  node->step()->accept(this, lvl);
  _pf.INT(0);
  _pf.LT();
  _pf.JZ("stepPositive" + lbl);
  node->counter()->accept(this, lvl);
  _pf.LDINT();
  node->end()->accept(this, lvl);
  _pf.GE();
  _pf.JZ("endFor" + lbl);
  _pf.JMP("forBody" + lbl);
  
  _pf.LABEL("stepPositive" + lbl);
  node->counter()->accept(this, lvl);
  _pf.LDINT();
  node->end()->accept(this, lvl);
  _pf.LE();
  _pf.JZ("endFor" + lbl);
  
  _pf.LABEL("forBody" + lbl);
  node->block()->accept(this, lvl);
  
  _pf.LABEL("forInc" + lbl);
  node->counter()->accept(this, lvl);
  _pf.LDINT();
  node->step()->accept(this, lvl);
  _pf.ADD();
  node->counter()->accept(this, lvl);
  _pf.STINT();
  _pf.JMP("forTest" + lbl);
  
  _pf.LABEL("endFor" + lbl);

  cycleLabels.pop_back();
  
}

void gr8::postfix_writer::do_block_node(gr8::block_node * const node, int lvl) {
  _symtab.push(); //cre8 a new context
  if(node->declarations() != nullptr)
    node->declarations()->accept(this, lvl);
  
  if(node->instructions() != nullptr)
    node->instructions()->accept(this, lvl);
  _symtab.pop(); //cre8 a new context
}

void gr8::postfix_writer::do_function_def_node(gr8::function_def_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  std::string id = node->id();

  ids.remove(id); //just found a definition of function with header

  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
  gr8::enter_eval *enter = new enter_eval(_compiler);
  
  _symtab.push(); //cre8 a new context
  in_context = true;
  in_context_id = id;
  
  // generate the main function (RTS mandates that its name be "_main")
  _pf.TEXT();
  _pf.ALIGN();
  if(id == "covfefe") {
      if(node->isPublic())
        _pf.GLOBAL("_main", _pf.FUNC());
    _pf.LABEL("_main");
  }
  else{
    if(node->isPublic())
      _pf.GLOBAL(id, _pf.FUNC());
    _pf.LABEL(id);
  }
  
  in_context_arg = true;
  if(node->vars() != nullptr) {
    node->vars()->accept(this, lvl);
  }

  in_context_arg = false;
  
  node->block()->accept(enter, lvl);
  _pf.ENTER(enter->size_of_args()); 

  int old_offset = offset_context;
  int old_offset_args = offset_context_args;
  offset_context = 0;
  offset_context_args = OFFSET_CONTEXT_ARGS_START;
  std::string old_id = in_context_id;
  node->block()->accept(this, lvl);
  offset_context = old_offset;
  offset_context_args = old_offset_args;
  in_context_id = old_id;
  
    if(id == "covfefe") {
    // these are just a few library function imports
        _pf.EXTERN("readi");
        _pf.EXTERN("printi");
        _pf.EXTERN("printd");
        _pf.EXTERN("prints");
        _pf.EXTERN("println");

        for (std::list<std::string>::iterator s = ids.begin(); s != ids.end(); s++)
          _pf.EXTERN(*s);
    }
    _pf.LABEL("end" + id);
    _pf.LEAVE();
    _pf.RET();
  
    _symtab.pop(); //elimin8 the current context
    in_context = false;
    in_context_id = "";
    offset_context = 0;
    offset_context_args = OFFSET_CONTEXT_ARGS_START;
}

void gr8::postfix_writer::do_function_prototype_node(gr8::function_prototype_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  ids.push_back(node->id());
  
}

void gr8::postfix_writer::do_function_call_node(gr8::function_call_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(node->id());
  std::vector<int> args = symbol->functionArgs();
  std::shared_ptr<gr8::symbol> symbol_arg;
  std::vector<int>::reverse_iterator it = args.rbegin();

  if (node->params() != nullptr) { //then function have arguments to be put in the stack before call
    size_t param_size = node->params()->size();


    

    

    for (size_t i = 0; i < param_size; i++, ++it) {
      needConvertI2D = false;
      node->params()->node(param_size - 1 - i)->accept(this, lvl);
      //if argument is double then convert it

      //Need to convert int 2 double if function arg is double and passed parameter is int
      if (it != args.rend()) {
        int type = *it;

        if (needConvertI2D && type == 8) {
          _pf.I2D();
        }
      }
      
    }
  }


  _symtab.push();
  _pf.CALL(node->id());
  _symtab.pop();
  
  int totalBytes = 0;
  for (it = args.rbegin(); it != args.rend(); ++it)
   totalBytes += *it;

  _pf.TRASH(totalBytes);



  //if function returns something ...
  if (node->type()->name() != basic_type::TYPE_VOID) {
      switch (node->type()->name()) {
      case basic_type::TYPE_INT:     _pf.LDFVAL32(); break;
      case basic_type::TYPE_DOUBLE:  _pf.LDFVAL64(); break;
      case basic_type::TYPE_STRING:  _pf.LDFVAL32(); break;
      case basic_type::TYPE_POINTER: _pf.LDFVAL32(); break;
    }
  }




}

void gr8::postfix_writer::do_variable_dec_node(gr8::variable_dec_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  std::string id = node->id();
  gr8::exp_eval *exp = new exp_eval(_compiler);
       
  //In_context means that are local vars and thus we use LOCAL postfix to get its address
  if(in_context){
      std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
      symbol->isGlobal(false);
      int offset;

      //In case of function args the offset is positive and starts at +4
      if (in_context_arg) {
        //Search function whose var is going to be declared
        std::shared_ptr<gr8::symbol> symbolFunc = _symtab.find(in_context_id);
        //store type in order to check if this argument need to be converted I2D
        symbolFunc->addfunctionArgsId(symbol->type()->size());

        offset = offset_context_args;
        offset_context_args += symbol->type()->size();
      }
      else {
        offset_context -= symbol->type()->size();
        offset = offset_context;
      }
      
      //define offset symbol
      symbol->offset(offset);
      if(node->initValue() != nullptr){
          
        node->initValue()->accept(this, lvl);
        _pf.LOCAL(offset);

        switch (node->type()->name()) {
          case basic_type::TYPE_INT:     _pf.STINT();    break;
          case basic_type::TYPE_DOUBLE:  _pf.STDOUBLE(); break;
          case basic_type::TYPE_STRING:  _pf.STINT();    break;
          case basic_type::TYPE_POINTER: _pf.STINT();    break;
          
        }
      }
  }
  
  else{ //global vars
    if (node->use())
    _pf.EXTERN(id);
      else{
               
      if (node->type()->name() == basic_type::TYPE_STRING) {
          node->initValue()->accept(this, lvl);
        }

        if (node->initValue() == nullptr)
         _pf.BSS();
        else _pf.DATA();
    
         _pf.ALIGN();  //aligns mem
    
        
         if (node->isPublic())
            _pf.GLOBAL(id, _pf.OBJ()); //for global vars
    
         _pf.LABEL(id);

        
        
         if (node->initValue() == nullptr)
           _pf.SALLOC(node->type()->size());
         else {
                    
           //only computes the expression val
           node->initValue()->accept(exp, lvl);
  
            switch (node->type()->name()) {
              case basic_type::TYPE_INT:    _pf.SINT(exp->result());    break;
              case basic_type::TYPE_DOUBLE: _pf.SDOUBLE(exp->resultDouble()); break;
              case basic_type::TYPE_POINTER: _pf.SALLOC(exp->result() * node->type()->subtype()->size()); break;
              case basic_type::TYPE_STRING: _pf.SADDR(mklbl(_lbl)); break;
              
            }

         }
         
      }    
  }
  

  
  
}

void gr8::postfix_writer::do_cell_node(gr8::cell_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->pointer()->accept(this, lvl);
  node->address()->accept(this, lvl);
  
  size_t size = node->pointer()->type()->subtype()->size();
  _pf.INT(size); //calculates pointer offset based on size of type
  _pf.MUL();
  _pf.ADD();
  
}

void gr8::postfix_writer::do_identity_node(gr8::identity_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
}

void gr8::postfix_writer::do_mem_alloc_node(gr8::mem_alloc_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl);
  _pf.INT(node->type()->_subtype->size());
  _pf.MUL();
  _pf.ALLOC();

  _pf.SP(); //put stack pointer into the stack to be stored as the first address to the array

}

void gr8::postfix_writer::do_stop_node(gr8::stop_node * const node, int lvl) {
  std::vector<int>::reverse_iterator it;
  int i = 1;
  int lbl_number;
  for (it = cycleLabels.rbegin(); it != cycleLabels.rend() && i <= node->cycle(); ++it, i++) {
    lbl_number = *it;
  }
  //pop values from cycleLabels
  while(cycleLabels.back() != node->cycle()) {
    cycleLabels.pop_back();
  }

  _pf.JMP("endFor" + mkcycle(lbl_number));
}

void gr8::postfix_writer::do_again_node(gr8::again_node * const node, int lvl) {
  std::vector<int>::reverse_iterator it;
  int i = 1;
  int lbl_number;
  for (it = cycleLabels.rbegin(); it != cycleLabels.rend() && i <= node->cycle(); ++it, i++) {
    lbl_number = *it;
  }
  _pf.JMP("forInc" + mkcycle(lbl_number));
}

void gr8::postfix_writer::do_return_node(gr8::return_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;

  std::shared_ptr<gr8::symbol> symbolFunc = _symtab.find(in_context_id);

  // put the result on the stack
  node->value()->accept(this, lvl);

  if (node->value()->type()->name() == basic_type::TYPE_INT && symbolFunc->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }

  switch (symbolFunc->type()->name()) {
    case basic_type::TYPE_INT:    _pf.STFVAL32(); break;
    case basic_type::TYPE_POINTER:_pf.STFVAL32(); break;
    case basic_type::TYPE_DOUBLE: _pf.STFVAL64(); break;
    case basic_type::TYPE_STRING: _pf.STFVAL32(); break;
  }

  _pf.JMP("end" + in_context_id);
  
  
}

void gr8::postfix_writer::do_address_of_node(gr8::address_of_node * const node, int lvl) {
   ASSERT_SAFE_EXPRESSIONS;
   node->value()->accept(this, lvl);
}

void gr8::postfix_writer::do_null_node(gr8::null_node * const node, int lvl) {
  _pf.INT(0); //store zero in a null pointer
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  _pf.INT(node->value()); // push an integer
   needConvertI2D = true;
}



void gr8::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
  needConvertI2D = false;
  int lbl1;

  /* generate the string */
  _pf.RODATA(); // strings are DATA readonly
  _pf.ALIGN(); // make sure we are aligned
  _pf.LABEL(mklbl(lbl1 = ++_lbl)); // give the string a name
  _pf.SSTRING(node->value()); // output string characters

  //only need to leave address on the stack if appears inside function
  if (in_context) {
  /* leave the address on the stack */
  _pf.TEXT(); // return to the TEXT segment
  _pf.ADDR(mklbl(lbl1)); // the string to be printed
  }
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  _pf.NEG(); // 2-complement
}

//---------------------------------------------------------------------------

bool gr8::postfix_writer::processMixedIntsAndDoublesBinOp(cdk::binary_expression_node *node, int lvl) {
  node->left()->accept(this, lvl);
  if ((node->left()->type()->name() == basic_type::TYPE_INT) && (node->right()->type()->name() == basic_type::TYPE_DOUBLE))
    _pf.I2D();

  node->right()->accept(this, lvl);
  if ((node->left()->type()->name() == basic_type::TYPE_DOUBLE) && (node->right()->type()->name() == basic_type::TYPE_INT))
    _pf.I2D();

  return ((node->left()->type()->name() == basic_type::TYPE_DOUBLE) || (node->right()->type()->name() == basic_type::TYPE_DOUBLE));
}

void gr8::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if(node->left()->type()->name() == basic_type::TYPE_POINTER && (node->right()->type()->name() == basic_type::TYPE_INT)) {
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    _pf.INT(node->left()->type()->_subtype->size());
    _pf.MUL();
    _pf.ADD();
  }
  else if(node->left()->type()->name() == basic_type::TYPE_INT && (node->right()->type()->name() == basic_type::TYPE_POINTER)) {
    node->right()->accept(this, lvl);
    node->left()->accept(this, lvl);
    _pf.INT(node->right()->type()->_subtype->size());
    _pf.MUL();
    _pf.ADD();
  }
 else {
    if (processMixedIntsAndDoublesBinOp(node, lvl))
     _pf.DADD();
    else _pf.ADD();

  }

}
void gr8::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl;
  if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER) {
    node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    _pf.SUB();
    _pf.INT(node->left()->type()->_subtype->size());
    _pf.DIV();
    _pf.DUP32();
    _pf.INT(0);
    _pf.GT();
    _pf.JNZ("subPointer" + mklbl(lbl = ++_lbl));
    _pf.NEG();
    _pf.LABEL("subPointer" + mklbl(lbl));
  }
  else {
    if (processMixedIntsAndDoublesBinOp(node, lvl))
     _pf.DSUB();
    else _pf.SUB();
  }
}
void gr8::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if (processMixedIntsAndDoublesBinOp(node, lvl))
   _pf.DMUL();
  else _pf.MUL();
}
void gr8::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  if (processMixedIntsAndDoublesBinOp(node, lvl))
   _pf.DDIV();
  else _pf.DIV();
}
void gr8::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void gr8::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LT();
}
void gr8::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.LE();
}
void gr8::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GE();
}
void gr8::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.GT();
}
void gr8::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.NE();
}
void gr8::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.EQ();
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  // simplified generation: all variables are global
  std::string id = node->name();
  std::shared_ptr<gr8::symbol> symbol = _symtab.find(id);
  
  if(symbol->isGlobal()){
    _pf.ADDR(id);
  }else
    _pf.LOCAL(symbol->offset());
}

void gr8::postfix_writer::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->lvalue()->accept(this, lvl);

  // depends on type size
  switch (node->type()->name()) {
    //if type is int then we may need to convert in next step
    case basic_type::TYPE_INT:     _pf.LDINT();    needConvertI2D = true; break;
    case basic_type::TYPE_DOUBLE:  _pf.LDDOUBLE(); needConvertI2D = false; break; //is double no need to convert!
    case basic_type::TYPE_STRING:  _pf.LDINT();    break;
    case basic_type::TYPE_POINTER: _pf.LDINT();    break;
  }
   
}

void gr8::postfix_writer::do_assignment_node(cdk::assignment_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->rvalue()->accept(this, lvl); // determine the new value
  //Convert if necessary when type is double and passed argument is int
  if (needConvertI2D && node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.I2D();
  }
  node->lvalue()->accept(this, lvl); // where to store the value
  
  // store the value at address
  switch (node->type()->name()) {
    case basic_type::TYPE_INT:     _pf.STINT();    break;
    case basic_type::TYPE_DOUBLE:  _pf.STDOUBLE(); break;
    case basic_type::TYPE_STRING:  _pf.STINT();    break;
    case basic_type::TYPE_POINTER: _pf.STINT();    break;
  }
 
}

void gr8::postfix_writer::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type() != nullptr) {
      if (node->argument()->type()->name() == basic_type::TYPE_INT) {
      _pf.TRASH(4); // delete the evaluated value
    } else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
      _pf.TRASH(4); // delete the evaluated value's address
    } else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.TRASH(8); // delete the evaluated value's address
    } else if (node->argument()->type()->name() == basic_type::TYPE_POINTER) {
      _pf.TRASH(4); // delete the evaluated value's address
    } else if (node->argument()->type()->name() == basic_type::TYPE_VOID) {
      //dont trash its void function
    }else {
      std::cerr << "ERROR: CANNOT HAPPEN!" << std::endl;
      exit(1);
    }
  }
  
}

void gr8::postfix_writer::do_read_node(gr8::read_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  _pf.CALL("readi");
  _pf.LDFVAL32();
}

void gr8::postfix_writer::do_if_node(gr8::if_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
}

//---------------------------------------------------------------------------

void gr8::postfix_writer::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  ASSERT_SAFE_EXPRESSIONS;
  int lbl1, lbl2;
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
}
