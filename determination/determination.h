#include "adcs_math/vector.h"


typedef enum {
    DET_SUCCESS,
    DET_NO_TLE,
    DET_POS_LOOKUP_ERROR,
    DET_IGRF_TIME_ERROR,
    DET_TRIAD_ERROR,
    DET_UNHANDLED_ERROR
} determination_status;

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
);
