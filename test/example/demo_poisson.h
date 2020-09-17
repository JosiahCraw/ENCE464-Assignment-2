#ifndef POISSON_DEMO_H
#define POISSON_DEMO_H

// Solve Poisson's equation for a rectangular box with Dirichlet
// boundary conditions on each face.
void demo_poisson_dirichlet (double *__restrict__ source,
                        double *__restrict__ potential,
                        double Vbound,
                        unsigned int xsize, unsigned int ysize, unsigned int zsize,
                        double delta, unsigned int maxiters, unsigned int numcores);
#endif
