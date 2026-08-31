# Dynamic C Numerical ODE Solver Engine (`numerical-ode-solver`)

A modular C engine designed to numerically solve initial value ordinary differential equations (ODEs) using high-precision integration algorithms (**RK4** and **Euler's Method**).

## 📌 Architectural Features
- **Pluggable System Derivatives:** Uses function pointer definitions `f(t, Y, dYdt)` allowing integration of arbitrary linear/nonlinear physical systems.
- **Runge-Kutta 4th Order (RK4):** Implements 4th-order multi-stage stepping for high numerical stability and low truncation error.
- **Damped Pendulum Model:** Real-world non-linear state modeling combining angular velocity and gravitational torque with friction damping.
- **Data Export Pipeline:** Automatic generation of structured CSV time-series datasets for numerical visualization.

## 🛠 Directory Layout
```text
numerical-ode-solver/
├── include/       # ODE solver definitions (ode.h)
├── src/           # RK4 math & derivative implementations (ode.c, system.c)
├── Makefile       # Automated build script
└── main.c         # Simulation driver & CSV writer

# Compile and run simulation
make clean && make && ./ode_solver

# View output time series
head -n 10 simulation.csv

output:

time,theta_rk4,omega_rk4
0.00,0.785398,0.000000
0.05,0.776776,-0.343678
0.10,0.751201,-0.677096
0.15,0.709337,-0.994286
0.20,0.652145,-1.289118
0.25,0.580903,-1.555299
0.30,0.497199,-1.786489
0.35,0.402940,-1.976575
0.40,0.300320,-2.120063
