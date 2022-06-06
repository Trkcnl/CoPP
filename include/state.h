#ifndef STATE_H
#define STATE_H

#include <ijvm.h>

typedef struct ijvm_state {
   word_t const_place;
   word_t const_size;
   word_t text_place;
   word_t text_size;

   byte_t *const_pool;
   byte_t *text_pool;

   byte_t inst_list[25];
} ijvm_state_t;

#endif