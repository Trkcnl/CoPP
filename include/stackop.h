#ifndef STACKOP_H
#define STACKOP_H

#include <ijvm.h>
#include <state.h>


void bi_push(ijvm_state_t *current_state);

void i_add(ijvm_state_t *current_state);

void i_sub(ijvm_state_t *current_state);

void i_and(ijvm_state_t *current_state);

void i_or(ijvm_state_t *current_state);

void swap(ijvm_state_t *current_state);

void dup(ijvm_state_t *current_state);

word_t pop(ijvm_state_t *current_state);

void go_to(ijvm_state_t *current_state);

void ifeq(ijvm_state_t *current_state);

void iflt(ijvm_state_t *current_state);

void icempq(ijvm_state_t *current_state);

int16_t conct_2byts(ijvm_state_t *current_state);

void mem_check(stack_ijvm_t *current_state);



//word_t tos_t(ijvm_state_t *current_state);

//int stack_size_t(ijvm_state_t *current_state);

//word_t *get_stack_t(ijvm_state_t *current_state);

#endif
