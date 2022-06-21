#ifndef FILEREAD_H
#define FILEREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <ijvm.h>
#include <state.h>
#include <string.h>

word_t swap_word(word_t num);

void swap_word_arr(word_t *buffer, const int size);

// Read word to buffer + index from fp and swap ENDIAN
void read_word(word_t * buffer, FILE *fp, const int size);

// Read byte to buffer
void read_byte(byte_t *buffer, FILE *fp, const int read_size);

void copy_buffer_to_ijvm(ijvm_state_t *current_state, word_t *buffer);

void load_text_to_ijvm(ijvm_state_t *current_state, byte_t *buffer);

void load_const_to_ijvm(ijvm_state_t *current_state, word_t *buffer);

void load_inst_list(ijvm_state_t *current_state);

bool is_inst(ijvm_state_t *current_state, byte_t byte_inst);

void extract_instructions(ijvm_state_t *current_state, byte_t *buffer);

void reset_ijvm(ijvm_state_t *current_state);

void print_all(ijvm_state_t *current_state);


// int byter_arr_to_int(byte_t * arr, int size_arr);



#endif