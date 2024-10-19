/**@file detumble.h
 *
 * @brief Detumbling routine for REALOP.
 * 
 * The detumble() function calls virtual_intellisat.h functions to 
 *  get magnetometer and accelerometer measurements, then calls
 *  bdot_control and issues that command to the magnetorquers. It
 *  continues doing this on a loop until the satellite's angular 
 *  velocity is below a required threshold.
 *
 * @author Charles Kvoriak (charles.kvoriak@gmail.com) 10/04/2024
 */

#ifndef DETUMBLE_H
#define DETUMBLE_H

typedef enum detumble{
    DETUMBLING_SUCCESS,
    DETUMBLING_FAILURE
} detumble_status;


/**@brief Detumbling function.
 *
 * @return detumble_status A return code.
 */
detumble_status detumble();

#endif//DETUMBLE_H
