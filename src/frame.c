#include <ijvm.h>
#include <state.h>
#include <frame.h>
#include <stdlib.h>
#include <stackop.h>

void local_push(stack_ijvm_t *current_stack,int offset_t, word_t next_arg);

node_t *new_node()
{
   node_t *node_instance;
   stack_ijvm_t * stack_instance;
   word_t *array_instance;

   if((node_instance = (node_t*)malloc(sizeof(node_t))) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      //halt();
   }

   if((stack_instance = (stack_ijvm_t*)malloc(sizeof(stack_ijvm_t))) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      //halt();
   }

   if((array_instance = (word_t*)malloc(sizeof(word_t) * 256)) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      //halt();
   }
   stack_instance->stack_bottom = array_instance;
   stack_instance->stack_pointer = array_instance;
   stack_instance->stack_size = 0;

   node_instance->stack_begin = stack_instance;
   
   return node_instance;

}

void ldc_w(ijvm_state_t *current_state)
{
   int16_t offset_const = conct_2byts(current_state);
   word_t word_to_copy = current_state->const_pool[offset_const];
   
   mem_check(current_state->ijvm_stack);

   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = word_to_copy;
}

void istore(ijvm_state_t *current_state)
{
   byte_t offset_frame = current_state->text_pool[get_program_counter()];
   current_state->program_counter++;

   local_push(current_state->current_frame->stack_begin
   , offset_frame, pop(current_state));
}

void iload(ijvm_state_t *current_state)
{
   node_t *temp = current_state->current_frame;
   word_t offset_stack = (word_t)current_state->text_pool[get_program_counter()];
   
   current_state->program_counter++;
   
   word_t word_to_push 
   = *(temp->stack_begin->stack_bottom + offset_stack);

   mem_check(current_state->ijvm_stack);

   current_state->ijvm_stack->stack_size++;
   current_state->ijvm_stack->stack_pointer++;
   *(current_state->ijvm_stack->stack_pointer) = word_to_push;
   
}

void iinc(ijvm_state_t *current_state)
{
   byte_t first_byte = current_state->text_pool[get_program_counter()];
   current_state->program_counter++;
   int8_t second_word = (int8_t) current_state->text_pool[get_program_counter()];
   current_state->program_counter++;
   

   mem_check(current_state->ijvm_stack);

   int8_t temp_int = (int8_t)get_local_variable(first_byte);
   temp_int += second_word;

   word_t temp_word = (word_t) temp_int;

   local_push(current_state->current_frame->stack_begin, first_byte,temp_word);
}

void invoke(ijvm_state_t *current_state)
{
   




}

void local_push(stack_ijvm_t *current_stack,int offset_t, word_t next_arg)
{
   
   mem_check(current_stack);
   
   *(current_stack->stack_bottom + offset_t) = next_arg;
}
