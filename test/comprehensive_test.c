/// \brief Test program for solving Poisson's equation using Jacobi relaxation
/// \author M. P. Hayes UCECE, Significantly Modifided by, Jos Craw 2020

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include <openssl/md5.h>
#include <string.h>

/*
 * Declear the example function and user function as
 * extern as they will be included at compile time
 */
extern void demo_poisson_dirichlet (double *__restrict__ source,
                        double *__restrict__ potential,
                        double Vbound,
                        unsigned int xsize, unsigned int ysize, unsigned int zsize,
                        double delta, unsigned int maxiters, unsigned int numcores);

extern void poisson_dirichlet (double *__restrict__ source,
                        double *__restrict__ potential,
                        double Vbound,
                        unsigned int xsize, unsigned int ysize, unsigned int zsize,
                        double delta, unsigned int maxiters, unsigned int numcores);

int main (int argc, char *argv[])
{
    // Init variables
    double *source;
    double *potential;

    double *demo_source;
    double *demo_potential;

    unsigned int N;
    unsigned int numiters;
    unsigned int numcores;    
    unsigned int xsize;
    unsigned int ysize;
    unsigned int zsize;    
    double delta = 0.1;

    if (argc < 3)
    {
        fprintf (stderr, "Usage: %s size numiters\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    xsize = N;
    ysize = N;
    zsize = N;

    numiters = atoi(argv[2]);

    if (argc > 3)
        numcores = atoi(argv[3]);
    else
        numcores = 0;

    // Set source and potential to empty intially
    source = (double *)calloc(xsize * ysize * zsize, sizeof(*source));
    potential = (double *)calloc(xsize * ysize * zsize + 1, sizeof(*potential));

    source[((zsize / 2 * ysize) + ysize / 2) * xsize + xsize / 2] = 1.0;    

    demo_source = (double *)calloc(xsize * ysize * zsize, sizeof(*source));
    demo_potential = (double *)calloc(xsize * ysize * zsize + 1, sizeof(*potential));

    demo_source[((zsize / 2 * ysize) + ysize / 2) * xsize + xsize / 2] = 1.0;    
    
    // Run the users implementation
    poisson_dirichlet(source, potential, 0.25, xsize, ysize, zsize, delta,
                      numiters, numcores);

    // Run the Demo implementation
    demo_poisson_dirichlet(demo_source, demo_potential, 0.25, xsize, ysize, zsize, delta,
                      numiters, numcores);
                      
	//for (int ii = 0; ii < xsize * ysize * zsize; ii++) {
		//printf("%f %f x=%d y=%d\n", potential[ii], demo_potential[ii], ii%xsize, ii/ysize);
	//}


    // Check the hashes are equal
    assert(!memcmp(potential, demo_potential, xsize * ysize * zsize * sizeof(*source)));

    return 0;
}
