#ifndef PID_H
#define PID_H

/*
    Implements a tamed PID controller with integral clamping
*/

struct PIDParams {
    double kp;
    double ki;
    double kd;
    double tau;
    double limit_max;
    double limit_min;
};

class PID {
    public:
        PID(double, PIDParams);

        void setGains(double, double, double, double);
        void setLimits(double, double);
        double getAction(double, double);

        double kp;
        double ki;
        double kd;
        double tau;

    private:
        void init();

        double getIntegralAction(double);
        double getDerivativeAction(double);
        double checkSaturation(double);

        double cycle_time;

        double b_int;
        double a_der;
        double b_der;

        double action;
        double saturated_action;

        double prev_process_output;
        double prev_error;
        double prev_integral_action;
        double prev_derivative_action;
        
        double limit_min;
        double limit_max;
};

#endif
