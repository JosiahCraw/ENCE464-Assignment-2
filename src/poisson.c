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
	unsigned int numiters = cfg->numiters;
	pthread_barrier_t *barrier = cfg->barrier;

	for (unsigned int iter = 0; iter < numiters; iter++) {

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

		double* temp = potential;
		potential = input;
		input = temp;
	}

}


// Task for top block
void poisson_top_task (void* arg)
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
    unsigned int numiters = cfg->numiters;
	pthread_barrier_t *barrier = cfg->barrier;


	for (unsigned int iter = 0; iter < numiters; iter++) {

		/*
		* Macro expansion for no boundary conditions
		*/
		XYZ

		/*
		* Macro expansion for Z boundary conditions
		*/
		XY_Z_TOP

		/*
		* Macro expansion for Y boundary conditions
		*/
		X_YZ

		/*
		* Macro expansion for Y, Z boundary conditions
		*/
		X_Y_Z_TOP

		/*
		* Macro expansion for X boundary conditions
		*/
		_XYZ

		/*
		* Macro expansion for X, Z boundary conditions
		*/
		_XY_Z_TOP

		/*
		* Macro expansion for X, Y boundary conditions
		*/
		_X_YZ

		/*
		* Macro expansion for X, Y, Z boundary conditions
		*/
		_X_Y_Z_TOP

		pthread_barrier_wait(barrier);

		double* temp = potential;
		potential = input;
		input = temp;
	}
}

// Task for bottom block
void poisson_bot_task (void* arg)
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
	unsigned int numiters = cfg->numiters;
	pthread_barrier_t *barrier = cfg->barrier;

	for (unsigned int iter = 0; iter < numiters; iter++) {

		/*
		* Macro expansion for no boundary conditions
		*/
		XYZ

		/*
		* Macro expansion for Z boundary conditions
		*/
		XY_Z_BOT

		/*
		* Macro expansion for Y boundary conditions
		*/
		X_YZ

		/*
		* Macro expansion for Y, Z boundary conditions
		*/
		X_Y_Z_BOT

		/*
		* Macro expansion for X boundary conditions
		*/
		_XYZ

		/*
		* Macro expansion for X, Z boundary conditions
		*/
		_XY_Z_BOT

		/*
		* Macro expansion for X, Y boundary conditions
		*/
		_X_YZ

		/*
		* Macro expansion for X, Y, Z boundary conditions
		*/
		_X_Y_Z_BOT

		pthread_barrier_wait(barrier);

		double* temp = potential;
		potential = input;
		input = temp;
	}
}

// Task for middle block
void poisson_mid_task (void* arg)
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
	unsigned int numiters = cfg->numiters;
	pthread_barrier_t *barrier = cfg->barrier;

	for (unsigned int iter = 0; iter < numiters; iter++) {

	    /*
	    * Macro expansion for no boundary conditions
	    */
	    XYZ

		/*
		* Macro expansion for Y boundary conditions
		*/
		X_YZ


		/*
		* Macro expansion for X boundary conditions
		*/
		_XYZ

		/*
		* Macro expansion for X, Y boundary conditions
		*/
		_X_YZ

		pthread_barrier_wait(barrier);

		double* temp = potential;
		potential = input;
		input = temp;
	}
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

	pthread_t threads[numcores];
	pthread_barrier_t barrier;
	unsigned count = numcores;
	int ret;

	ret = pthread_barrier_init(&barrier, NULL, count);

	if (ret) {
		fprintf(stderr, "Failed to create pthread barrier\n");
	}


	unsigned int zslice = 0;


	if (numcores == 1) {
		poisson_cfg_t* cfg = (poisson_cfg_t*)malloc(sizeof(poisson_cfg_t));
		cfg->source = source;
		cfg->potential = potential;
		cfg->input = input;
		cfg->Vbound = Vbound;
		cfg->xsize = xsize;
		cfg->ysize = ysize;
		cfg->zsize = zsize;
		cfg->delta = delta;
		cfg->numiters = numiters;
		cfg->barrier = &barrier;

		pthread_create(&threads[0], NULL, poisson_task, (void*)cfg);

	} else {
		// Split into top, bottom, and possibly middle threads
		unsigned int deltaz_init = zsize / numcores;
		unsigned int deltaz = deltaz_init;
		unsigned int rem = zsize % numcores;

		// Create top thread
		if (rem) {
			deltaz = deltaz_init + 1;
				rem--;
		} else {
			deltaz = deltaz_init;
		}

		poisson_cfg_t* cfg = (poisson_cfg_t*)malloc(sizeof(poisson_cfg_t));
		cfg->source = source + zslice * ysize * zsize;
		cfg->potential = potential + zslice * ysize * zsize;
		cfg->input = input + zslice * ysize * zsize;
		cfg->Vbound = Vbound;
		cfg->xsize = xsize;
		cfg->ysize = ysize;
		cfg->zsize = deltaz + 1;
		cfg->delta = delta;
		cfg->numiters = numiters;
		cfg->barrier = &barrier;

		pthread_create(&threads[0], NULL, poisson_top_task, (void*)cfg);

		zslice += deltaz;


		 // Create Middle Threads
		 if (numcores > 2) {
			for (int t=1; t<numcores-1; t++) {
				poisson_cfg_t* cfg = (poisson_cfg_t*)malloc(sizeof(poisson_cfg_t));

				if (rem) {
					deltaz = deltaz_init + 1;
					rem--;
				} else {
					deltaz = deltaz_init;
				}

				cfg->source = source + (zslice - 1) * ysize * zsize;
				cfg->potential = potential + (zslice - 1) * ysize * zsize;
				cfg->input = input + (zslice - 1) * ysize * zsize;
				cfg->Vbound = Vbound;
				cfg->xsize = xsize;
				cfg->ysize = ysize;
				cfg->zsize = deltaz + 2;
				cfg->delta = delta;
				cfg->numiters = numiters;
				cfg->barrier = &barrier;

				zslice += deltaz;

				pthread_create(&threads[t], NULL, poisson_mid_task, (void*)cfg);
			}

		}
		// Create Bottom Thread
		if (rem) {
			deltaz = deltaz_init + 1;
				rem--;
		} else {
			deltaz = deltaz_init;
		}

		poisson_cfg_t* cfg_b = (poisson_cfg_t*)malloc(sizeof(poisson_cfg_t));
		cfg_b->source = source + (zslice - 1) * ysize * zsize;
		cfg_b->potential = potential + (zslice - 1) * ysize * zsize;
		cfg_b->input = input + (zslice - 1) * ysize * zsize;
		cfg_b->Vbound = Vbound;
		cfg_b->xsize = xsize;
		cfg_b->ysize = ysize;
		cfg_b->zsize = deltaz + 1;
		cfg_b->delta = delta;
		cfg_b->numiters = numiters;
		cfg_b->barrier = &barrier;

		pthread_create(&threads[numcores-1], NULL, poisson_bot_task, (void*)cfg_b);
	}



	for (int t=0; t<numcores; t++) {
		pthread_join(threads[t], NULL);
	}


	// Check potential and input are pointing at the correct locations
	if (!(numiters % 2)) {
		// Input is pointing at the original potential location, so copy potential to input, and swap the pointers
		memcpy(potential,input,size);
	}

	free(input);
}
