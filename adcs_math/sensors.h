/**
 * @file sensors.h
 * 
 * @brief Interface for general sensor functions
 * 
 * @author Tarini Maram (tarini.maram@gmail.com) 1/8/2025
*/
#ifndef SENSORS_H
#define SENSORS_H

typedef struct Sensor {
    float currValue;
    float prevValue;
} sensor;

/**
 * @brief Implement lowpass filter on sensor raw values to mitigate the effect of noise from abnormally high values
 * 
 * @param s sensor to filter values from
 * @param filterConstant constant between 0-1; a lower value is a greater damp on unusually large jumps in sensor value
 * 
 * @return filtered sensor value
*/
float lowpass_filter(sensor s, float filterConstant);

/**
 * @brief Calculates sensor calibration value after filtering data through simple lowpass filter with default constant 0.5
 * 
 * @param s sensor to get raw value from 
 * @param offset constant the sensor reads when it is not supposed to read anything
 * @param gain constant multiplier for sensor raw values
 * 
 * @return sensor calibration value after filtration 
*/
float get_sensor_calibration(sensor s, float offset, float gain);

#endif

