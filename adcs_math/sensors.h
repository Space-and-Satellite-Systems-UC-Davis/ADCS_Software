/**
 * @file sensors.h
 * 
 * @brief Interface for general sensor functions
 * 
 * @author Tarini Maram (tarini.maram@gmail.com) 1/8/2025
*/
#ifndef SENSORS_H
#define SENSORS_H

/**
 * @brief Implement lowpass filter on sensor raw values to mitigate the effect of noise from abnormally high values
 * 
 * @param currValue current sensor raw value
 * @param prevValue previous sensor raw value
 * @param filterConstant constant between 0-1; a lower value is a greater damp on unusually large jumps in sensor value
 * 
 * @return filtered sensor value
*/
float lowpass_filter(float currValue, float prevValue, float filterConstant);

/**
 * @brief Calculates sensor calibration value after filtering data through simple lowpass filter with default constant 0.5
 * 
 * @param currValue current sensor raw value
 * @param prevValue previous sensor raw value
 * @param offset constant the sensor reads when it is not supposed to read anything
 * @param gain constant multiplier for sensor raw values
 * 
 * @return sensor calibration value after filtration 
*/
float get_sensor_calibration(float currValue, float prevValue, float offset, float gain);

#endif

