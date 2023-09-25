/**@file bdot_control.c
 * 
 * @brief Implementation of the BDOT algorithm.
 * 
 * This file was transcribed from the python version on github.
 *  See github tag 'python-archive' for the original.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 *
 * @date 6/11/2023
 */

#include "bdot_control.h"
#include "adcs_math/vector.h"

//the constant that converts the cross product to amps.
const double current_constant = 67200.0;


void bdot_control(vec3 mf, vec3 av, vec3 *coils_current) {
	vec3 temp;

	vec_cross(mf, av, &temp);
	vec_scalar(current_constant, temp, &temp);

	//cap output at maximum 0.158 Amps across all coils. 
	double temp_mag = vec_mag(temp);
	if (temp_mag > 0.158f) {
		//this step is equivalent to 0.158 * normalized temp.
		vec_scalar(0.158f / temp_mag, temp, &temp);
	}

	(*coils_current) = temp;
} //TODO verify! totally unclear if this is correct!





