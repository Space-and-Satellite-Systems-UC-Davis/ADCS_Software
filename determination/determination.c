#include "determination/determination.h"
#include "determination/novasc3.1/novas.h"

#include "determination/pos_lookup/pos_lookup.h"
#include "determination/sun_lookup/sun_lookup.h"
#include "determination/mag_lookup/mag_lookup.h"
#include "determination/TRIAD/triad.h"

#include "adcs_math/vector.h"
#include "adcs_math/matrix.h"

#include "virtual_intellisat.h"
#include "ADCS.h"


determination_status
determination(
    int year,
    int month,
    int day,
    int hour,
    int minute,
    double second,
    vec3 measured_mag,
    vec3 measured_sun,
    mat3 *attitude
) {
    double UTC = julian_date(
        year, month, day,
        hour + minute/60.0 + second/3600.0
    );

    int update_IGRF = 0; //false
    char *tle_line1;
    char *tle_line2;


    vi_get_TLE_status tle_status =
    vi_get_TLE(tle_line1, tle_line2);

    switch (tle_status) {
        case GET_TLE_FAILURE: return DET_NO_TLE;
        case GET_TLE_SUCCESS_OLD: break;
        case GET_TLE_SUCCESS_NEW: update_IGRF = 1; break;
        // update IGRF when we get a new TLE, including the 1st time
    }


    double longitude;
    double latitude;
    double altitude;
    double geocentric_radius;
    double geocentric_latitude;

    pos_lookup_status pos_status =
    pos_lookup(
    	tle_line1,
    	tle_line2,
    	UTC,
    	0.0,
    	&longitude,
    	&latitude,
    	&altitude,
        &geocentric_radius,
        &geocentric_latitude
    );

    switch (pos_status) {
        case SGP4_ERROR:            return DET_POS_LOOKUP_ERROR;
        case TEME2ITRS_ERROR:       return DET_POS_LOOKUP_ERROR;
        case ITRS2LLA_ERROR:        return DET_POS_LOOKUP_ERROR;
        case POS_LOOKUP_SUCCESS:    break;
    }


	vec3 reference_sun;

    sun_lookup_status sun_status =
    sun_lookup(
    	longitude,
    	latitude,
    	altitude,
    	year,
    	month,
    	day,
    	hour,
    	minute,
    	second,
	    &reference_sun
    );

    switch (sun_status) {
        case SUN_LOOKUP_BAD_DATE:       return DET_POS_LOOKUP_ERROR;
        case SUN_LOOKUP_BAD_ENVIRONMENT:return DET_POS_LOOKUP_ERROR;
        case SUN_LOOKUP_BAD_LLA:        return DET_POS_LOOKUP_ERROR;
        case SUN_LOOKUP_SUCCESS:        break;
    }


    vec3 reference_mag;

    int igrf_time_status =
    igrf_set_date_time(
        year,
        month,
        day,
        hour,
        minute,
        second
    ); //recalculate every time for now...

    switch (igrf_time_status) {
        case IGRF_SET_DATE_OUT_OF_BOUNDS:
            return DET_IGRF_TIME_ERROR;
        case IGRF_SET_DATE_SUCCESS:
            break;
    }

    igrf_update(
        geocentric_latitude,
        longitude,
        geocentric_radius,
        update_IGRF, //recalculate coefficients on new TLE
		&reference_mag
    );


    triad_run_status triad_status = 
    triad(
    	measured_sun,
        measured_mag,
    	reference_sun,
        reference_mag,
    	attitude
    );

    switch (triad_status) {
        case TRIAD_NORM_FAILURE:    return DET_TRIAD_ERROR;
        case TRIAD_SUCCESS:         break;
    }

    return DET_SUCCESS;
}





