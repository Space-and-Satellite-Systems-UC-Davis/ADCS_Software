/**@file ADCS.h
 *
 * @brief Intellisat's interface to the ADCS software.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 *
 * @date 7/30/2023
 */

#ifndef ADCS_H
#define ADCS_H

#include "adcs_math/matrix.h"
#include "virtual_intellisat.h"


//State variables
mat3 realop_attitude;


typedef enum {
	ADCS_DETUMBLE,
	ADCS_HDD,
	ADCS_MRW
} adcs_mode;


void ADCS_MAIN(
	adcs_mode mode,
	int year,
	int month,
	int day,
	int hour,
	int min,
	double sec
);


#endif//ADCS_H





