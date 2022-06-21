#ifndef STATE_H
#define STATE_H

#include <ijvm.h>


typedef struct stack_ijvm
{
   word_t *stack_pointer;
   word_t *stack_bottom;

   int stack_size;
}stack_ijvm_t;

typedef struct node
{
   stack_ijvm_t *stack_begin;
   struct node *frame_next;
}node_t;


typedef struct ijvm_state 
{
   word_t const_place;
   word_t const_size;
   word_t text_place;
   word_t text_size;

   word_t *const_pool;
   byte_t *text_pool;

   byte_t inst_list[25];

   stack_ijvm_t *ijvm_stack;

   node_t *current_frame;
   int frame_size;

   FILE *ijvm_output;
   FILE *ijvm_input;

   int program_counter;
} ijvm_state_t;

#endif