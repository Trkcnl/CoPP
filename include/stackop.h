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

word_t pop(ijvm_state_t *current_state);


//word_t tos_t(ijvm_state_t *current_state);

//int stack_size_t(ijvm_state_t *current_state);

//word_t *get_stack_t(ijvm_state_t *current_state);

#endif
