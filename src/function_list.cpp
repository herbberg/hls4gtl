#include "../headers/function_list.h"
#include "../headers/comp.h"

void init_bool_2dim_array (bool data[][], size_t size_a, size_t size_b, bool val)
{
	for (size_t i = 0; i < size_a; i++) {
		for (size_t j = 0; j < size_b; j++) {
			data[i][j] = val;
	    }
    }
}

bool requ_vs_obj (obj_t objects[max_obj], const obj_requ_t requirements[max_requ], char n_requ, char n_obj_l, char n_obj_h)
{
	bool comp_out[max_requ][max_obj];
	comp_out[max_requ][max_obj] = init_bool_2dim_array(max_requ, max_obj, true);

    for (char i = 0; i < n_requ; i++) {
        for (char j = n_obj_l; j < n_obj_h+1; j++) {
            comp_out[i][j] = comp(&requirements[i], &objects[j]);
        }
    }
    return comp_out[max_requ][max_obj];
}
