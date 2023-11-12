
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


int determination(
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

    int tle_status = get_tle(
        tle_line1,
        tle_line2
    );


    double longitude;
    double latitude;
    double altitude;
    double geocentric_radius;
    double geocentric_latitude;

    int pos_lookup_status = pos_lookup(
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


	vec3 reference_sun;

    int sun_lookup_status = sun_lookup(
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


    vec3 reference_mag;

    int igrf_time_status = igrf_set_date_time(
        year,
        month,
        day,
        hour,
        minute,
        second
    ); //recalculate every time for now...

    igrf_update(
        geocentric_latitude, //TODO: verify this is geocentric
        longitude,
        geocentric_radius,
        1 //recalculate coefficients every time for now...
    );

    vec_set(
        (double) B_ned[0],
        (double) B_ned[1],
        (double) B_ned[2],
        &reference_mag
    );

    triad(
    	measured_sun,
        measured_mag,
    	reference_sun,
        reference_mag,
    	&realop_attitude //In ADCS.h
    );
}


//TODO: handle errors

