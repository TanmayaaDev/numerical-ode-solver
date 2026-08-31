#include <stdio.h>
#include <stdlib.h>
#include "include/ode.h"

void dampedPendulum(double t, const State *y, State *dydt);

int main() {
    printf("=========================================\n");
    printf("      C NUMERICAL ODE SOLVER ENGINE      \n");
    printf("=========================================\n\n");

    double t0 = 0.0, t_end = 10.0, dt = 0.05;
    int steps = (int)((t_end - t0) / dt);

    State *y_rk4 = createState(2);
    State *y_next = createState(2);

    // Initial state: theta = 45 deg (0.785398 rad), omega = 0.0
    y_rk4->values[0] = 0.785398; 
    y_rk4->values[1] = 0.0;

    FILE *csv = fopen("simulation.csv", "w");
    if (!csv) {
        perror("Failed to open file");
        return 1;
    }

    fprintf(csv, "time,theta_rk4,omega_rk4\n");
    fprintf(csv, "%.2f,%.6f,%.6f\n", t0, y_rk4->values[0], y_rk4->values[1]);

    double t = t0;
    for (int i = 0; i < steps; i++) {
        stepRK4(dampedPendulum, t, y_rk4, dt, y_next);

        // Copy state over
        y_rk4->values[0] = y_next->values[0];
        y_rk4->values[1] = y_next->values[1];
        t += dt;

        fprintf(csv, "%.2f,%.6f,%.6f\n", t, y_rk4->values[0], y_rk4->values[1]);
    }

    fclose(csv);
    freeState(y_rk4);
    freeState(y_next);

    printf("Simulation completed successfully!\n");
    printf("Output saved to 'simulation.csv' (%d steps).\n", steps);
    return 0;
}