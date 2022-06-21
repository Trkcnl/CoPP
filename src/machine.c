#include <ijvm.h>
#include <fileread.h>
#include <stackop.h>
#include <frame.h>


ijvm_state_t * ijvm_instance;



int init_ijvm(char *binary_file)
{
   // Implement loading of binary here
   //open file
   FILE *fp;

   if((fp = fopen(binary_file,"r")) == NULL)
   {
      fprintf(stderr, "File read Error!");
      return -1;
   }
   // Create a buffer to read file
   word_t block_arr_f[6];
   block_arr_f[5] = '\0';

   // Allocations
   if((ijvm_instance = (ijvm_state_t *) malloc(sizeof(ijvm_state_t))) == NULL)
   {  
      fprintf(stderr,"Malloc failed.");
      return -1;
   }
   
   stack_ijvm_t * stack_instance;
   if((stack_instance = (stack_ijvm_t*)malloc(sizeof(stack_ijvm_t))) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      return -1;
   }

   word_t *stack_array;
   if((stack_array = (word_t*)malloc(sizeof(word_t) * 256)) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      return -1;
   }


   // Initialize output stream
   set_output(stdout);
   set_input(stdin);

   // Load all instructions to ijvm instance
   load_inst_list(ijvm_instance);


   // read magic number, const index, const size
   read_word(block_arr_f, fp, 3);
   swap_word_arr(block_arr_f, 3);


   // read const pool
   word_t const_poll[block_arr_f[2] / 4];
   read_word(const_poll, fp, block_arr_f[2] / 4);
   swap_word_arr(const_poll, block_arr_f[2] / 4);

   // read text and text_size
   read_word(block_arr_f + 3, fp, 2);
   swap_word_arr(block_arr_f + 3, 2);


   // read text pool
   byte_t text_f[block_arr_f[4]];
   read_byte(text_f, fp, block_arr_f[4]);


   // Copy all readings to ijvm instance (e.g. cont size, text size...)
   copy_buffer_to_ijvm(ijvm_instance, block_arr_f);

   // Print only the isntructions
   // extract_instructions(ijvm_instance, text_f);

   // load text pool to ijvm instance
   load_text_to_ijvm(ijvm_instance, text_f);
   // load const pool to ijvm instance
   load_const_to_ijvm(ijvm_instance, const_poll);

   // print_all(ijvm_instance);

   // Initiate pc as 0
   ijvm_instance->program_counter = 0;
   stack_instance->stack_size = 0;

   stack_instance->stack_pointer = stack_array;
   stack_instance->stack_bottom = stack_array;
   ijvm_instance->ijvm_stack = stack_instance;

   ijvm_instance->current_frame = new_node();
   ijvm_instance->frame_size = 1;

   fclose(fp);

   return 0;
}

void destroy_ijvm()
{
  // Reset IJVM state
  reset_ijvm(ijvm_instance);
}

void run()
{
  while(step()){}
}

bool step()
{
   if(get_program_counter() >= text_size())
   {
      return false;
   }
   byte_t next_inst = get_text()[get_program_counter()];
   ijvm_instance->program_counter++;

   switch (next_inst)
   {
   case 0x00:
      break;
   case OP_BIPUSH: // BIPUSH
      bi_push(ijvm_instance);      
      break;

   case OP_ILOAD: // BIPUSH
      iload(ijvm_instance);      
      break;

   case OP_LDC_W: // LDC_W
      ldc_w(ijvm_instance);
      break;

   case OP_ISTORE: // ISTORE
      istore(ijvm_instance);
      break;

   case OP_POP: // POP
      pop(ijvm_instance);
      break;

   case OP_DUP: // DUP
      dup(ijvm_instance);
      break;

   case OP_SWAP: // SWAP
      swap(ijvm_instance);
      break;

   case OP_IADD: // IADD
      i_add(ijvm_instance);
      break;

   case OP_ISUB: // ISUB
      i_sub(ijvm_instance);
      break;

   case OP_IAND: // IAND
      i_and(ijvm_instance);
      break;
   case OP_IINC: // IINC
      iinc(ijvm_instance);
      break;

   case OP_IFEQ: // IFEQ
      ifeq(ijvm_instance);
      break;

   case OP_IFLT: // IFLT
      iflt(ijvm_instance);
      break;

   case OP_ICMPEQ: // ICEMPQ
      icempq(ijvm_instance);
      break;
   
   case OP_GOTO: // GOTO
      go_to(ijvm_instance);
      break;
   
   case OP_IOR: // IOR
      i_or(ijvm_instance);
      break;
   case OP_INVOKEVIRTUAL: // INVOKEVIRTUAL
      invoke(ijvm_instance);
      break;
   
   case OP_OUT:
      fprintf(ijvm_instance->ijvm_output,"%c",pop(ijvm_instance));
      
      break;
   case OP_HALT: // HALT
      return true;
      break;
   default:
      break;
   }

   return true;
}

void set_input(FILE *fp)
{
   ijvm_instance->ijvm_input = fp;
}

void set_output(FILE *fp)
{
   ijvm_instance->ijvm_output = fp;
}

word_t tos()
{
   return *(ijvm_instance->ijvm_stack->stack_pointer);
}

int stack_size()
{
   return ijvm_instance->ijvm_stack->stack_size;
}

byte_t *get_text()
{  
   return ijvm_instance->text_pool;
}

int text_size()
{
   return ijvm_instance->text_size;
}

int get_program_counter()
{
   return ijvm_instance->program_counter;
}

word_t *get_stack()
{
   return ijvm_instance->ijvm_stack->stack_bottom;
}

word_t get_local_variable(int i)
{
   
   return *(ijvm_instance->current_frame->stack_begin->stack_bottom + i);
}
