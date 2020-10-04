#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "poisson.h"
#include "poisson_macros.h"

void poisson_task (void* arg)
{
	poisson_cfg_t* cfg = (poisson_cfg_t*)arg;
	double *source = cfg->source;
    double *potential = cfg->potential;
	double *input = cfg->input;
    double Vbound = cfg->Vbound;
    unsigned int xsize = cfg->xsize;
    unsigned int ysize = cfg->ysize;
    unsigned int zsize = cfg->zsize;
    double delta = cfg->delta;
	/*
	* Macro expansion for no boundary conditions
	*/
	XYZ

	/*
	* Macro expansion for Z boundary conditions
	*/
	XY_Z

	/*
	* Macro expansion for Y boundary conditions
	*/
	X_YZ

	/*
	* Macro expansion for Y, Z boundary conditions
	*/
	X_Y_Z

	/*
	* Macro expansion for X boundary conditions
	*/
	_XYZ

	/*
	* Macro expansion for X, Z boundary conditions
	*/
	_XY_Z

	/*
	* Macro expansion for X, Y boundary conditions
	*/
	_X_YZ

	/*
	* Macro expansion for X, Y, Z boundary conditions
	*/
	_X_Y_Z

	// free(cfg);

}

/// Solve Poisson's equation for a rectangular box with Dirichlet
/// boundary conditions on each face.
/// \param source is a pointer to a flattened 3-D array for the source function
/// \param potential is a pointer to a flattened 3-D array for the calculated potential
/// \param Vbound is the potential on the boundary
/// \param xsize is the number of elements in the x-direction
/// \param ysize is the number of elements in the y-direction
/// \param zsize is the number of elements in the z-direction
/// \param delta is the voxel spacing in all directions
/// \param numiters is the number of iterations to perform
/// \param numcores is the number of CPU cores to use.  If 0, an optimal number is chosen
void poisson_dirichlet (double * __restrict__ source,
                        double * __restrict__ potential,
                        double Vbound,
                        unsigned int xsize, unsigned int ysize, unsigned int zsize, double delta,
                        unsigned int numiters, unsigned int numcores)
{
    size_t size = (size_t)ysize * zsize * xsize * sizeof(double);
	double *input = (double *)malloc(size);
	if (!input) {
		fprintf(stderr, "malloc failure\n");
		return;
	}

	if (numcores == 0) {
		numcores = 1;
	}
	memcpy(input, source, size);
	for (unsigned int iter = 0; iter < numiters; iter++) {
		pthread_t threads[numcores];

		unsigned int zslice = 0;
		unsigned int deltaz = zsize / numcores;

		for (int t=0; t<numcores; t++) {
			poisson_cfg_t* cfg = (poisson_cfg_t*)malloc(sizeof(poisson_cfg_t));

			deltaz += (deltaz % numcores && t == numcores - 1) ? 1 : 0; 
			printf("zslice: %d, deltaz: %d\n", zslice, deltaz);
			cfg->source = source + zslice * ysize * zsize;
			cfg->potential = potential + zslice * ysize * zsize;
			cfg->input = input + zslice * ysize * zsize;
			cfg->Vbound = Vbound;
			cfg->xsize = xsize;
			cfg->ysize = ysize;
			cfg->zsize = deltaz;
			cfg->delta = delta;

			zslice += deltaz;

			pthread_create(&threads[t], NULL, poisson_task, (void*)cfg);
		}

		for (int t=0; t<numcores; t++) {
			pthread_join(threads[t], NULL);
		}

		memcpy(input, potential, size);
	}
	free(input);
}