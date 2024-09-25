#ifndef PID_H
#define PID_H

typedef struct PID_struct {
	double P_gain;
	double I_gain;
	double D_gain;
	double e_prev;
	double e_cumulative;
	int t_prev;
} PID_struct;

double PID_command(
	PID_struct *PID_controller, 
	double target,
	double state,
	int t_curr
);

#endif //PID_H
