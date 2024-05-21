/**@file ADCS.c
 *
 * @brief Implementation of Intellisat's interface to the ADCS software.
 *
 * @author Jacob Tkeio (jacobtkeio@gmail.com)
 * @date 8/5/2023
 */

#include "ADCS.h"
#include "virtual_intellisat.h"
#include "determination.h"
#include "detumble.h"

adcs_main_status
ADCS_MAIN(adcs_mode mode) {
	switch(mode) {
		case ADCS_DETUMBLE:
			detumble_status detumble_status = detumble();

			switch(detumble_status) {
				case DETUMBLE_ERROR:
					return ADCS_MAIN_DETUMBLE_ERROR;
					break;
			}

			break;

		case ADCS_HDD_EXPERIMENT:
			HDD_experiment_status HDD_experiment_status = HDD_experiment();

			switch(HDD_experiment_status) {
				case HDD_EXPERIMENT_SUCCESS:
					return ADCS_MAIN_SUCCESS;
					break;

				case HDD_EXPERIMENT_FAILURE:
					return ADCS_MAIN_HDD_ERR;
					break;
			}

			break;

		case ADCS_MRW_EXPERIMENT:
			MRW_experiment_status MRW_experiment_status = MRW_experiment();
			
			switch(MRW_experiment_status) {
				case MRW_EXPERIMENT_SUCCESS:
					return ADCS_MAIN_SUCCESS;
					break;

				case MRW_EXPERIMENT_FAILURE:
					return ADCS_MAIN_MRW_ERR;
					break;
			}

			break;
	}
}


// ADCS recommend mode function for REALOP 0.5. HDD experiment will be the only available mode.
adcs_mode ADCS_recommend_mode(){
	return ADCS_HDD_EXPERIMENT;
}




