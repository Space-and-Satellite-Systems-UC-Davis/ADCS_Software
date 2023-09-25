/**@file pos_lookup.h
 *
 * @brief Interface to SGP4 orbit propagator.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 * @date 9/4/2023
 */

#ifndef POS_LOOKUP_H
#define POS_LOOKUP_H


/**@brief Calculate geodetic position given TLE and time.
 *
 * @param tle_line1,tle_line2 Both lines of the TLE as C strings.
 * @param UTC1,UTC2 The julian date divided however is easiest.
 * @param longitude,latitude,altitude Pointers to geodetic output.
 * @param geocentric_radius Pointer to geocentric radius output.
 * @param geocentric_latitude Pointer to geocentric latitude output.
 *
 * Longitude and latitude are in degrees.
 * Altitude is in meters.
 * Geocentric radius is in kilometers.
 * Geocentric latitude is in radians.
 *
 * @return Error code: zero means success, anything else failure.
 */
int pos_lookup (
	char *tle_line1,
	char *tle_line2,
	double UTC1,
	double UTC2,
	double *longitude,
	double *latitude,
	double *altitude,
    double *geocentric_radius,
    double *geocentric_latitude
);


#endif//POS_LOOKUP_H





