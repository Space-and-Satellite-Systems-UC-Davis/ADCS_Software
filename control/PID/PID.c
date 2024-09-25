#include "PID.h"

double PID_command(
	PID_struct *PID_controller,
	double target,
	double state,
	int t_curr
) {
	double e_curr = target - state;
	double dt = t_curr - (PID_controller->t_prev);
	double e_derivative = (e_curr - PID_controller->e_prev)/dt;

	double command = (PID_controller->P_gain)*e_curr
				   + (PID_controller->I_gain)*(PID_controller->e_cumulative)
				   + (PID_controller->D_gain)*e_derivative;

	PID_controller->e_cumulative = PID_controller->e_cumulative + dt*e_curr;
	PID_controller->e_prev = e_curr;
	
	return command;
}
