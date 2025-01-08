#include "sensors.h"

float lowpass_filter(sensor s, float filterConstant) {
    return (filterConstant * s.currValue) + ((1-filterConstant) * s.prevValue);
}

float get_sensor_calibration(sensor s, float offset, float gain)
{
    return (lowpass_filter(s, 0.5) * gain) + offset;
}
