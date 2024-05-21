/**@file bdot_control.c
 * 
 * @brief Implementation of the BDOT algorithm.
 * 
 * This file was transcribed from the python version on github.
 *  See github tag 'python-archive' for the original.
 * BDOT should only use magnetometer and time readings.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 *
 * @date 6/11/2023
 */

#include "bdot_control.h"
#include "adcs_math/vector.h"

const double control_constant = 67200.0; //TODO: tune :p


void bdot_control(
    vec3    mag,
    vec3    last_mag,
    double  delta_t,
    vec3   *coils_current
) {
    vec3 derivative;    // = (mag - last_mag)/delta_t

    vec_scalar(-1.0, last_mag, &last_mag);
    vec_add(mag, last_mag, &derivative);
    vec_scalar(1.0/delta_t, derivative, &derivative);

	vec3 coils_output;  // = (-1) * derivative

	vec_scalar(-1.0, derivative, &derivative);
	vec_cross(mag, derivative, &coils_output);
	vec_scalar(control_constant, coils_output, &coils_output);

	//cap output at maximum 0.158 Amps across all coils. 
	double temp_mag = vec_mag(coils_output);
	if (temp_mag > 0.158f) {
		//this step is equivalent to 0.158 * normalized temp.
		vec_scalar(0.158f / temp_mag, coils_output, &coils_output);
	}

	(*coils_current) = coils_output;
}





