#include <ijvm.h>
#include <state.h>
#include <stackop.h>
#include <stdlib.h>


void bi_push(ijvm_state_t *current_state)
{
   stack_ijvm_t *temp_stack = current_state->ijvm_stack;
   if (temp_stack + 1 == NULL)
   {
      temp_stack->stack_bottom 
      = (word_t *)realloc(get_stack(), sizeof(word_t) * stack_size() * 2);
   }

      int8_t next_arg = (int8_t) get_text()[get_program_counter()];
      const word_t next_word = (word_t) next_arg;
      current_state->program_counter++;

      temp_stack->stack_pointer++;
      temp_stack->stack_size++;
      *temp_stack->stack_pointer = next_word;
}

void i_add(ijvm_state_t *current_state)
{
   const word_t add_arg1 = pop(current_state);
   const word_t add_arg2 = pop(current_state);
   const word_t add_res = add_arg1 + add_arg2;
   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = add_res;
}


void i_sub(ijvm_state_t *current_state)
{  
   const word_t sub_arg1 = pop(current_state);
   const word_t sub_arg2 = pop(current_state);
   const word_t sub_res = sub_arg2 - sub_arg1;
   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = sub_res;
}


void i_and(ijvm_state_t *current_state)
{
   const word_t and_arg1 = pop(current_state);
   const word_t and_arg2 = pop(current_state);
   const word_t and_res = and_arg1 & and_arg2;
   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = and_res;
}


void i_or(ijvm_state_t *current_state)
{
   const word_t or_arg1 = pop(current_state);
   const word_t or_arg2 = pop(current_state);
   const word_t or_res = or_arg1 | or_arg2;
   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = or_res;
}

void swap(ijvm_state_t *current_state)
{
   const word_t temp1 = pop(current_state);
   const word_t temp2 = pop(current_state);

   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = temp1;

   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = temp2;
}

void dup(ijvm_state_t *current_state)
{
   word_t word_to_copy = tos();

   if (current_state->ijvm_stack->stack_pointer + 1 == NULL)
   {
      current_state->ijvm_stack->stack_bottom 
      = (word_t *)realloc(get_stack(), sizeof(word_t) * stack_size() * 2);
   }

   current_state->ijvm_stack->stack_pointer++;
   *current_state->ijvm_stack->stack_pointer = word_to_copy;
}

word_t pop(ijvm_state_t *current_state)
{
   word_t top_word = *(current_state->ijvm_stack->stack_pointer);
   current_state->ijvm_stack->stack_pointer--;
   current_state->ijvm_stack->stack_size--;

   return top_word;
}

void go_to(ijvm_state_t *current_state)
{
   byte_t first_byte = current_state->text_pool[get_program_counter()];
   current_state->program_counter++;
   byte_t second_byte = current_state->text_pool[get_program_counter()];
   int16_t next_arg = second_byte + (first_byte << 8);

   current_state->program_counter += (next_arg - 2);
}

void ifeq(ijvm_state_t *current_state)
{
   if(pop(current_state) == 0)
   {
      byte_t first_byte = current_state->text_pool[get_program_counter()];
      current_state->program_counter++;
      byte_t second_byte = current_state->text_pool[get_program_counter()];
      int16_t next_arg = second_byte + (first_byte << 8);

      current_state->program_counter += (next_arg - 2);
   }
   else
   {
      current_state->program_counter += 2;
   }

}

void iflt(ijvm_state_t *current_state)
{
   if(pop(current_state) < 0)
   {
      byte_t first_byte = current_state->text_pool[get_program_counter()];
      current_state->program_counter++;
      byte_t second_byte = current_state->text_pool[get_program_counter()];
      int16_t next_arg = second_byte + (first_byte << 8);

      current_state->program_counter += (next_arg - 2);
   }
   else
   {
      current_state->program_counter += 2;
   }

}

void icempq(ijvm_state_t *current_state)
{
   if((pop(current_state) == pop(current_state)))
   {
      byte_t first_byte = current_state->text_pool[get_program_counter()];
      current_state->program_counter++;
      byte_t second_byte = current_state->text_pool[get_program_counter()];
      int16_t next_arg = second_byte + (first_byte << 8);

      current_state->program_counter += (next_arg - 2);
   }
   else
   {
      current_state->program_counter += 2;
   }

}