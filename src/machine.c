#include <ijvm.h>
#include <fileread.h>
#include <stackop.h>


ijvm_state_t * ijvm_instance;
stack_ijvm_t * stack_instance;
word_t *stack_array;

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

   // Create ijvm instance
   if((ijvm_instance = (ijvm_state_t *) malloc(sizeof(ijvm_state_t))) == NULL)
   {  
      fprintf(stderr,"Malloc failed.");
      return -1;
   }

   if((stack_instance = (stack_ijvm_t*)malloc(sizeof(stack_ijvm_t))) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      return -1;
   }
   if((stack_array = (word_t*)malloc(sizeof(word_t) * 20)) == NULL)
   {
      fprintf(stderr,"Malloc failed");
      return -1;
   }


   // Load all instructions to ijvm instance
   load_inst_list(ijvm_instance);


   // read magic number, const index, const size
   read_word(block_arr_f, fp, 3);
   swap_word_arr(block_arr_f, 3);


   // read const pool
   byte_t const_poll[block_arr_f[2]];
   read_byte(const_poll, fp, block_arr_f[2]);

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

   // print_all(ijvm_instance);
   
   // int8_t res1 = (int8_t) text_f[1];
   // word_t res = (word_t) res1;
   // printf("%d-%d", res,res1);

   // Initiate pc as 0
   ijvm_instance->program_counter = 0;
   stack_instance->stack_size = 0;

   stack_instance->stack_pointer = stack_array;
   stack_instance->stack_bottom = stack_array;
   ijvm_instance->ijvm_stack = stack_instance;

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
      printf("NOP");
      break;
   case 0x10: // BIPUSH
      bi_push(ijvm_instance);      
      break;

   case 0x13: // LDC_W
      printf("LDC_W");
      break;

   case 0x59: // DUP
      printf("DUP");
      break;

   case 0x60: // IADD
      i_add(ijvm_instance);
      break;

   case 0x64: // ISUB
      i_sub(ijvm_instance);
      break;

   case 0x7E: // IAND
      i_and(ijvm_instance);
      break;
   
   case 0xB0: // IOR
      i_or(ijvm_instance);
      break;

   case 0x5F: // IOR
      swap(ijvm_instance);
      break;

   case 0x57: // IOR
      pop(ijvm_instance);
      break;
   
   case 0xFD:
      printf("OUT");
      break;
   default:
      break;
   }

   return true;
}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}

word_t tos()
{
   return *(stack_instance->stack_pointer);
}

int stack_size()
{
   return stack_instance->stack_size;
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
   return stack_instance->stack_bottom;
}
