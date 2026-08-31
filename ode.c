#include <stdio.h>
#include <stdlib.h>
#include "../include/ode.h"

State* createState(int dim) {
    State *s = (State*)malloc(sizeof(State));
    s->dim = dim;
    s->values = (double*)calloc(dim, sizeof(double));
    return s;
}

void freeState(State *s) {
    if (!s) return;
    free(s->values);
    free(s);
}

// Euler Method: Y_{n+1} = Y_n + dt * f(t, Y_n)
void stepEuler(SystemDerivative f, double t, const State *y, double dt, State *y_next) {
    State *dydt = createState(y->dim);
    f(t, y, dydt);

    for (int i = 0; i < y->dim; i++) {
        y_next->values[i] = y->values[i] + dt * dydt->values[i];
    }

    freeState(dydt);
}

// Runge-Kutta 4th Order (RK4) Method
void stepRK4(SystemDerivative f, double t, const State *y, double dt, State *y_next) {
    int dim = y->dim;
    State *k1 = createState(dim);
    State *k2 = createState(dim);
    State *k3 = createState(dim);
    State *k4 = createState(dim);
    State *temp = createState(dim);

    // k1 = f(t, y)
    f(t, y, k1);

    // k2 = f(t + dt/2, y + (dt/2)*k1)
    for (int i = 0; i < dim; i++) temp->values[i] = y->values[i] + 0.5 * dt * k1->values[i];
    f(t + 0.5 * dt, temp, k2);

    // k3 = f(t + dt/2, y + (dt/2)*k2)
    for (int i = 0; i < dim; i++) temp->values[i] = y->values[i] + 0.5 * dt * k2->values[i];
    f(t + 0.5 * dt, temp, k3);

    // k4 = f(t + dt, y + dt*k3)
    for (int i = 0; i < dim; i++) temp->values[i] = y->values[i] + dt * k3->values[i];
    f(t + dt, temp, k4);

    // Y_{n+1} = Y_n + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
    for (int i = 0; i < dim; i++) {
        y_next->values[i] = y->values[i] + (dt / 6.0) * (k1->values[i] + 2.0 * k2->values[i] + 2.0 * k3->values[i] + k4->values[i]);
    }

    freeState(k1);
    freeState(k2);
    freeState(k3);
    freeState(k4);
    freeState(temp);
}