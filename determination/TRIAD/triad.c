/**@file triad.c
 *
 * @brief Implementation of the TRIAD algorithm.
 *
 * This file was transcribed from the python version on github.
 *
 * The basis vectors are normalized at the end instead of
 *  normalizing all input vectors at the beginning because it
 *  should lead to a more orthonormal bod_triad matrix.
 * This better validates the crucial predicate that the transposition
 *  of bod_triad is its inverse only if it's orthonormal. 
 * It's not that important but since this is technically
 *  less efficient (6 vs 4 norms) it serves to explain the reasoning.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 *
 * @date 7/17/2023
 */

#include "adcs_math/vector.h"
#include "adcs_math/matrix.h"


void triad(
	vec3 bod_sun, vec3 bod_mag,
	vec3 ref_sun, vec3 ref_mag,
	mat3 *output
) {
	vec3 bod_basis1 = bod_mag;
	vec_norm(bod_basis1, &bod_basis1);

	vec3 bod_basis2;
	vec_cross(bod_mag, bod_sun, &bod_basis2);
	vec_norm(bod_basis2, &bod_basis2);

	vec3 bod_basis3;
	vec_cross(bod_basis1, bod_basis2, &bod_basis3);
	vec_norm(bod_basis3, &bod_basis3);

	mat3 bod_triad;
	mat_set_from_vec(
		bod_basis1,
		bod_basis2,
		bod_basis3,
		&bod_triad
	);


	vec3 ref_basis1 = ref_mag;
	vec_norm(ref_basis1, &ref_basis1);

	vec3 ref_basis2;
	vec_cross(ref_mag, ref_sun, &ref_basis2);
	vec_norm(ref_basis2, &ref_basis2);

	vec3 ref_basis3;
	vec_cross(ref_basis1, ref_basis2, &ref_basis3);
	vec_norm(ref_basis3, &ref_basis3);

	mat3 ref_triad;
	mat_set_from_vec(
		ref_basis1,
		ref_basis2,
		ref_basis3,
		&ref_triad
	);

	mat_transpose(ref_triad, &ref_triad);


	mat_mult(
		bod_triad,
		ref_triad,
		output
	); //TODO verify the order of multiplication.
}





