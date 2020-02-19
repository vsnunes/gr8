#include "targets/enter_eval.h"
#include "ast/all.h"

void gr8::enter_eval::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

void gr8::enter_eval::do_block_node(gr8::block_node * const node, int lvl) {
  if(node->declarations() != nullptr)
    node->declarations()->accept(this, lvl);
  if(node->instructions() != nullptr)
  node->instructions()->accept(this, lvl);
  
}

//---------------------------------------------------------------------------

void gr8::enter_eval::do_nil_node(cdk::nil_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_data_node(cdk::data_node * const node, int lvl) {
  // EMPTY
}

void gr8::enter_eval::do_double_node(cdk::double_node * const node, int lvl) {
  _size_of_args += 8;
}

void gr8::enter_eval::do_not_node(cdk::not_node * const node, int lvl) {
}

void gr8::enter_eval::do_and_node(cdk::and_node * const node, int lvl) {
}

void gr8::enter_eval::do_or_node(cdk::or_node * const node, int lvl) {
}

void gr8::enter_eval::do_tweet_node(gr8::tweet_node * const node, int lvl) {
}

void gr8::enter_eval::do_post_node(gr8::post_node * const node, int lvl) {
}

void gr8::enter_eval::do_sweeping_node(gr8::sweeping_node * const node, int lvl) {
    node->counter()->accept(this, lvl);
}

void gr8::enter_eval::do_function_def_node(gr8::function_def_node * const node, int lvl) {
  node->block()->accept(this, lvl);
}

void gr8::enter_eval::do_function_prototype_node(gr8::function_prototype_node * const node, int lvl) {
}

void gr8::enter_eval::do_function_call_node(gr8::function_call_node * const node, int lvl) {
}

void gr8::enter_eval::do_variable_dec_node(gr8::variable_dec_node * const node, int lvl) {
      _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_cell_node(gr8::cell_node * const node, int lvl) {
}

void gr8::enter_eval::do_identity_node(gr8::identity_node * const node, int lvl) {
}

void gr8::enter_eval::do_mem_alloc_node(gr8::mem_alloc_node * const node, int lvl) {
}

void gr8::enter_eval::do_stop_node(gr8::stop_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_again_node(gr8::again_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_return_node(gr8::return_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_address_of_node(gr8::address_of_node * const node, int lvl) {
}

void gr8::enter_eval::do_null_node(gr8::null_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void gr8::enter_eval::do_integer_node(cdk::integer_node * const node, int lvl) {
  _size_of_args += 4;
}

void gr8::enter_eval::do_string_node(cdk::string_node * const node, int lvl) {
  _size_of_args += 4;
}

//---------------------------------------------------------------------------

void gr8::enter_eval::do_neg_node(cdk::neg_node * const node, int lvl) {
}

//---------------------------------------------------------------------------


void gr8::enter_eval::do_add_node(cdk::add_node * const node, int lvl) {
  _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_sub_node(cdk::sub_node * const node, int lvl) {
  _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_mul_node(cdk::mul_node * const node, int lvl) {
  _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_div_node(cdk::div_node * const node, int lvl) {
  _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_mod_node(cdk::mod_node * const node, int lvl) {
  _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_lt_node(cdk::lt_node * const node, int lvl) {
}

void gr8::enter_eval::do_le_node(cdk::le_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_ge_node(cdk::ge_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_gt_node(cdk::gt_node * const node, int lvl) {
}

void gr8::enter_eval::do_ne_node(cdk::ne_node * const node, int lvl) {
  //EMPTY
}

void gr8::enter_eval::do_eq_node(cdk::eq_node * const node, int lvl) {
}
//---------------------------------------------------------------------------

void gr8::enter_eval::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  if (node->type() != nullptr)
    _size_of_args += node->type()->size();
}

void gr8::enter_eval::do_rvalue_node(cdk::rvalue_node * const node, int lvl) {
}

void gr8::enter_eval::do_assignment_node(cdk::assignment_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void gr8::enter_eval::do_evaluation_node(gr8::evaluation_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void gr8::enter_eval::do_read_node(gr8::read_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void gr8::enter_eval::do_if_node(gr8::if_node * const node, int lvl) {
  node->block()->accept(this, lvl);
}

void gr8::enter_eval::do_if_else_node(gr8::if_else_node * const node, int lvl) {
  node->thenblock()->accept(this, lvl);
  node->elseblock()->accept(this, lvl);
}

