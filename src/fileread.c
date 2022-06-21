#include <fileread.h>


void print_all(ijvm_state_t *current_state)
{
   printf("Constant:%x ", current_state->const_place);
   printf("%x- ", current_state->const_size);
   for(int i = 0; i < current_state->const_size; i++)
   {
      printf("%x ", current_state->const_pool[i]);
   }
   printf("\nText%x ", current_state->text_place);
   printf("%x- ", current_state->text_size);
   for(int i = 0; i < current_state->text_size; i++)
   {
      printf("%x ", current_state->text_pool[i]);
   }
}

void load_inst_list(ijvm_state_t *current_state)
{
   
   current_state->inst_list[0] = OP_BIPUSH;
   current_state->inst_list[1] = OP_DUP;
   current_state->inst_list[2] = OP_ERR;
   current_state->inst_list[3] = OP_GOTO;
   current_state->inst_list[4] = OP_HALT;
   current_state->inst_list[5] = OP_IADD;
   current_state->inst_list[6] = OP_IAND;
   current_state->inst_list[7] = OP_IFEQ;
   current_state->inst_list[8] = OP_IFLT;
   current_state->inst_list[9] = OP_ICMPEQ;
   current_state->inst_list[10] = OP_IINC;
   current_state->inst_list[11] = OP_ILOAD;
   current_state->inst_list[12] = OP_IN;
   current_state->inst_list[13] = OP_INVOKEVIRTUAL;
   current_state->inst_list[14] = OP_IOR;
   current_state->inst_list[15] = OP_IRETURN;
   current_state->inst_list[16] = OP_ISTORE;
   current_state->inst_list[17] = OP_ISUB;
   current_state->inst_list[18] = OP_LDC_W;
   current_state->inst_list[19] = OP_NOP;
   current_state->inst_list[20] = OP_OUT;
   current_state->inst_list[21] = OP_POP;
   current_state->inst_list[22] = OP_SWAP;
   current_state->inst_list[23] = OP_WIDE;
   current_state->inst_list[24] = '\0';
}

word_t swap_word(word_t num)
{
  return((num>>24)&0xff) | ((num<<8)&0xff0000) |((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

void swap_word_arr (word_t *buffer, const int size)
{
   for(int i = 0; i < size; i++)
   {
      buffer[i] = swap_word (buffer[i]);
   }

}

void read_word(word_t * buffer, FILE *fp, const int size)
{
   fread(buffer, sizeof(word_t), size, fp);

}

void read_byte(byte_t *buffer, FILE *fp, const int read_size)
{
   fread(buffer, sizeof(byte_t), read_size, fp );
}

void copy_buffer_to_ijvm(ijvm_state_t *current_state, word_t *buffer)
{
   current_state->const_place = buffer[1];
   current_state->const_size = buffer[2] / 4;
   current_state->text_place = buffer[3];
   current_state->text_size = buffer[4];
}

void load_text_to_ijvm(ijvm_state_t *current_state, byte_t *buffer)
{
   current_state->text_pool = (byte_t*)malloc(sizeof(byte_t) * current_state->text_size + 1);
   
   for(int i = 0; i < current_state->text_size; i++)
   {
      current_state->text_pool[i] = buffer[i];
   }

   current_state->text_pool[current_state->text_size] = '\0';
}

void load_const_to_ijvm(ijvm_state_t *current_state, word_t *buffer)
{
   word_t *cont_arr = (word_t*)malloc((sizeof(word_t) * current_state->const_size ));
   current_state->const_pool = cont_arr;
   
   for(int i = 0; i < current_state->const_size; i++)
   {
      current_state->const_pool[i] = buffer[i];
   }
}

bool is_inst(ijvm_state_t *current_state, byte_t byte_inst)
{
   for(int i = 0; i < 24; i++)
   {
      if(byte_inst == current_state->inst_list[i])
      {
         return true;
      }
   }
   return false;
}

void extract_instructions(ijvm_state_t *current_state, byte_t *buffer)
{
   for(int i = 0; i < current_state->text_size; i++)
   {
      if(is_inst(current_state, buffer[i]))
      {
         printf("%x-", buffer[i]);
      }
   }
}



void reset_ijvm(ijvm_state_t *current_state)
{
   free(current_state->current_frame->stack_begin->stack_bottom);
   free(current_state->current_frame->stack_begin);
   free(current_state->current_frame);
   free(current_state->ijvm_stack->stack_bottom);
   free(current_state->ijvm_stack);
   free(current_state->text_pool);
   free(current_state->const_pool);
   free(current_state);
}