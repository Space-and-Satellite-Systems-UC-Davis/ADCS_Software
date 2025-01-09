#include "sensors.h"

float lowpass_filter(float currValue, float prevValue, float filterConstant) {
    return (filterConstant * currValue) + ((1-filterConstant) * prevValue);
}

float get_sensor_calibration(float currValue, float prevValue, float offset, float gain)
{
    return (lowpass_filter(currValue, prevValue, 0.5) * gain) + offset;
}

int get_delta_t(int currTime, int prevTime) {
    if (prevTime <= currTime) {
        return currTime - prevTime;
    } else {
        return (INT_MAX - prevTime) + currTime;
    }
}
