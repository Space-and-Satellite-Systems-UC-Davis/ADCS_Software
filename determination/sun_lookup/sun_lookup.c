/**@file sun_lookup.c
 *
 * @brief Implementation of wrapper for NREL's SPA.
 *
 * TODO: make sure the calendar dates we get from Intellisat allign
 * 	with SPA's requirements!
 * 	Also check delta_t and atmospheric refraction.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 * @date 8/29/2023
 */

#include <math.h>
#include "determination/sun_lookup/sun_lookup.h"
#include "determination/sun_lookup/spa.h"


int sun_lookup(
	double longitude,
	double latitude,
	double altitude,
	int year,
	int month,
	int day,
	int hour,
	int minute,
	double second,
	vec3 *output
) {
	spa_data spa;

	spa.year = year;
	spa.month = month;
	spa.day = day;
	spa.hour = hour;
	spa.minute = minute;
	spa.second = second;
	spa.delta_ut1 = 0.0; //accounts for fractional second errors, not necessary
	spa.delta_t = 70.0; //from: maia.usno.navy.mil/products/deltaT TODO: update with better approximation
	spa.timezone = 0;
	spa.longitude = longitude;
	spa.latitude = latitude;
	spa.elevation = altitude;
	spa.pressure = 0.0;
	spa.temperature = 0.0;
	spa.slope = 0.0;
	spa.azm_rotation = 0.0;
	spa.atmos_refract = 0.5667; //TODO: an inaccurate value can cause error of 5 degrees
	spa.function = SPA_ZA;

	int status = spa_calculate(&spa);	
	if (status) return status;

	//Azimuth and Zenith to radians, Zenith to Elevation.
	double az = (spa.azimuth * M_PI / 180.0);
	double el = (-spa.zenith * M_PI / 180.0) + M_PI / 2.0;

	//Azimuth and Elevation to East, North, and Azimuth
	//cartesian coordinates.
	vec_set(
		(float) sin(az)*cos(el),
		(float) cos(az)*cos(el),
		(float) sin(el),
		output
	); 

	return 0;
}





