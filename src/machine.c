#include <ijvm.h>
#include <fileread.h>


ijvm_state_t * ijvm_instance;

int init_ijvm(char *binary_file)
{
  // Implement loading of binary here

   FILE *fp;

   if((fp = fopen(binary_file,"r")) == NULL)
   {
      fprintf(stderr, "File read Error!");
      return -1;
   }

   word_t block_arr_f[6];
   block_arr_f[5] = '\0';

   ijvm_instance = (ijvm_state_t *) malloc(sizeof(ijvm_state_t));

   load_inst_list(ijvm_instance);
   // read magic number, const index, const size
   read_word(block_arr_f, fp, 3);
   swap_word_arr(block_arr_f, 3);

   byte_t const_poll[block_arr_f[2]];
   read_byte(const_poll, fp, block_arr_f[2]);

   // read text and text_size
   read_word(block_arr_f + 3, fp, 2);
   swap_word_arr(block_arr_f + 3, 2);

   byte_t text_f[block_arr_f[4]];
   read_byte(text_f, fp, block_arr_f[4]);

   copy_buffer_to_ijvm(ijvm_instance, block_arr_f);


   printf("%x-%x-%x-%x", ijvm_instance->const_place, 
   ijvm_instance->const_size, ijvm_instance->text_place, 
   ijvm_instance->text_size);

   extract_instructions(ijvm_instance, text_f);

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
  // Step while you can
}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}
