#ifndef POISSON_H
#define POISSON_H

typedef struct poisson_cfg
{
    double *__restrict__ source;
    double *__restrict__ potential;
    double* input;
    double Vbound;
    unsigned int xsize;
    unsigned int ysize;
    unsigned int zsize;
    double delta;
    unsigned int numiters;
	pthread_barrier_t *barrier;
} poisson_cfg_t;


// Solve Poisson's equation for a rectangular box with Dirichlet
// boundary conditions on each face.
void poisson_dirichlet (double *__restrict__ source,
                        double *__restrict__ potential,
                        double Vbound,
                        unsigned int xsize, unsigned int ysize, unsigned int zsize,
                        double delta, unsigned int maxiters, unsigned int numcores);

#endif
