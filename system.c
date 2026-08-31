#include <math.h>
#include "../include/ode.h"

// Parameters: g = 9.81 m/s^2, L = 1.0 m, b = 0.25 (damping)
void dampedPendulum(double t, const State *y, State *dydt) {
    (void)t; // Unused time variable for autonomous system
    double theta = y->values[0]; // Angle
    double omega = y->values[1]; // Angular velocity

    double g = 9.81;
    double L = 1.0;
    double b = 0.25;

    dydt->values[0] = omega;
    dydt->values[1] = -(g / L) * sin(theta) - b * omega;
}