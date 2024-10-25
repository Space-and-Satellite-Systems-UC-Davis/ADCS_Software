
#include "determination/determination.h"
#include "determination/novasc3.1/novas.h"

#include "determination/pos_lookup/pos_lookup.h"
#include "determination/sun_lookup/sun_lookup.h"
#include "determination/IGRF_C/igrf.h"
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
    vec3 measured_sun
) {
    double UTC = julian_date(
        year, month, day,
        hour + minute/60.0 + second/3600.0
    );

    char tle_line1[70]; //TODO: make these persistent so that we don't
    char tle_line2[70]; //have to ask Intellisat for them every time.

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
        default:                    return DET_UNHANDLED_ERROR;
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
        default:                        return DET_UNHANDLED_ERROR;
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
        default:    return DET_UNHANDLED_ERROR;
        case 0:     return DET_IGRF_TIME_ERROR;
        case 1:     break;
    }

    igrf_update(
        geocentric_latitude, //TODO: verify this is geocentric
        longitude,
        geocentric_radius,
        1, //recalculate coefficients every time for now...
		&reference_mag
    );

    triad_run_status triad_status = 
    triad(
    	measured_sun,
        measured_mag,
    	reference_sun,
        reference_mag,
    	&realop_attitude //In ADCS.h
    );

    switch (triad_status) {
        default:                    return DET_UNHANDLED_ERROR;
        case TRIAD_NORM_FAILURE:    return DET_TRIAD_ERROR;
        case TRIAD_SUCCESS:         break;
    }

    return DET_SUCCESS;
}





