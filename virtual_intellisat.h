/**@file virtual_intellisat.h
 *
 * @brief ADCS Software's interface to Intellisat.
 *
 * This file contains the function prototype for every
 *  actuator-commanding and sensor-reading function
 *  the ADCS Software needs from Intellisat.
 *
 * Their corresponding definitions will be written in the Intellisat
 *  repo by the CS team. While this means any ADCS code that uses
 *  these functions cannot run outside of the Intellisat repo, 
 *  this approach allows for complete separation of the two repos,
 *  which vastly simplifies development for everyone. And, while
 *  such code will not run, it will still compile!
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 * @date 9/25/2023
 */

#ifndef VIRTUAL_INTELLISAT_H
#define VIRTUAL_INTELLISAT_H


typedef enum {
    TLE_SUCCESS,
    NO_TLE,
} get_tle_status;


/**@brief Load most recent TLE strings.
 *
 * @param tle_line1 The first  line of the TLE (70 chars).
 * @param tle_line2 The second line of the TLE (70 chars).
 *
 * These should be directly modifiable as tle_line1[i] 
 *  and tle_line2[j].
 * It may be easier to modify a char**; just say the word!
 *
 * @return get_tle_status SUCCESS_TLE or NO_TLE.
 */
get_tle_status
get_tle(
    char *tle_line1,
    char *tle_line2
);




#endif//VIRTUAL_INTELLISAT_H





