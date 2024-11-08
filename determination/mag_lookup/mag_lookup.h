/*
    ~ Implementation of 13th Generation IGRF Model ~

References:
    [1] Davis - Mathematical Modeling of Earth's Magnetic Field (2004)
    [2] Yaguang - Spacecraft Modeling Attitude Determination and Control:
            Quaternion Based Approach (2019)

Note:
    Variable names used in this code follows reference [2].

    Rishav (2021/12/26)
*/

#ifndef _IGRF_H_
#define _IGRF_H_

#include <math.h>
#include <inttypes.h>
#include "adcs_math/vector.h"

#define PI 3.14159265358979323846
#define PI_2 1.57079632679489661923

#define IGRF_START_YEAR 2020
#define IGRF_END_YEAR 2030
#define IGRF_GEN 13

//IGRF13 outputs
extern float igrf_B_ned[3]; // {N,E,D}
extern float igrf_B_sph[3]; // {Radial, Theta, Phi}


uint8_t igrf_set_date_time(uint16_t year, uint8_t month, uint8_t day,
                           uint8_t hour, uint8_t min, uint8_t sec);

void compute_gauss_coeffs(float decimal_years_);

/*
   ~ Compute magnetic field strength in local coordinates, nT ~

Inputs:
    latitude    = Latitude measured in degrees positive from equator, radians
    longitude   = Longitude measured in degrees positive east from Greenwich, radians
    r           = Geocentric radius, km

Outputs:
    igrf_B_ned[3] = B in North, East and Up direction respectively, nT
    igrf_B_sph[3] = B in radial, theta and phi direction respectively, nT
	
	B_ned = pointer to an adcs_math vec3 struct to be modified
*/
void igrf_update(float latitude, float longitude, float radius, int interpolate_flag, vec3* B_ned);

float igrf_get_horizontal_intensity();
float igrf_get_inclination();
float igrf_get_declination();
float igrf_get_norm();

#endif // igrf.h
