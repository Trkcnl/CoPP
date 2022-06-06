#include <fileread.h>


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
   current_state->const_size = buffer[2];
   current_state->text_place = buffer[3];
   current_state->text_size = buffer[4];
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
   free(current_state);
}

// void copy_const_pool_to_ijvm(ijvm_state_t *current_state, byte_t *buffer)
// {
//    current_state->const_pool = malloc()
// }



// int byter_arr_to_int(byte_t * arr, const int size_arr)
// {
//    int result = 0x0, j = 0x01;

//    for(int i = size_arr - 1; i > -1; i--)
//    {
//       result += arr[i] * (0x1 * j);
//       j *= 0x100;
//    }

//    return result;
// }