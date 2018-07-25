#ifndef CONDITION_H_
#define CONDITION_H_

#include "comp.h"
#include "definitions.h"

ap_uint<1> condition (const obj_t objects[MAX_OBJ], const obj_requ_t requirements[MAX_REQ], size_t n_requ, size_t n_obj);

#endif
