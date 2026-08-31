#ifndef ODE_H
#define ODE_H

// State vector representation (e.g., [position, velocity])
typedef struct {
    double *values;
    int dim;
} State;

// Function pointer signature for system derivatives: dY/dt = f(t, Y)
typedef void (*SystemDerivative)(double t, const State *y, State *dydt);

// Allocate and free state vectors
State* createState(int dim);
void freeState(State *s);

// Single integration steps
void stepEuler(SystemDerivative f, double t, const State *y, double dt, State *y_next);
void stepRK4(SystemDerivative f, double t, const State *y, double dt, State *y_next);

#endif