#ifndef FRAME_H
#define FRAME_H

#include <ijvm.h>
#include <state.h>

node_t *new_node();

void ldc_w(ijvm_state_t *current_state);

void istore(ijvm_state_t *current_state);

void iload(ijvm_state_t *current_state);

void iinc(ijvm_state_t *current_state);

void invoke(ijvm_state_t *current_state);



#endif