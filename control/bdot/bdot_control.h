/**@file bdot_control.h
 * 
 * @brief Interface to the BDOT algorithm.
 *
 * BDOT calculates the optimal direction in which to create a
 *  magnetic dipole in order to slow REALOP during detumbling.
 * The result should have REALOP aligned north-south longways,
 *  spinning on only the longways axis.
 * 
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 *
 * @date 6/11/2023
 */

#ifndef BDOT_CONTROL
#define BDOT_CONTROL

#include "adcs_math/vector.h"


/**@brief Calculate a dipole command for all three coils given our
 *  magnetic field and angular velocity data.
 * 
 * @param mf The magnetic field vector.
 * 		Format: [X, Y, Z] Micro Teslas
 * @param av The angular velocity vector.
 *		Format: [X, Y, Z] Radians per Second
 * @param coils_current The vec3* that will hold the coil outputs.
 * 		Format: [X, Y, Z] Amperes
 *
 * @return Void.
 */
void bdot_control(vec3 mf, vec3 av, vec3 *coils_current);


#endif//BDOT_CONTROL





