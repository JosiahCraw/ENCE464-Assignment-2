/// \brief Test program for solving Poisson's equation using Jacobi relaxation
/// \author M. P. Hayes UCECE, Significantly Modifided by, Jos Craw 2020

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <openssl/md5.h>
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
    
    // Run the users implementation
    poisson_dirichlet(source, potential, 0.25, xsize, ysize, zsize, delta,
                      numiters, numcores);

    // for (int z=0; z<zsize; z++) {
    //     for (int y=0; y<ysize; y++) {
    //         for (int x=0; x<xsize; x++) {
    //             printf("%f ", potential[((z * ysize) + y) * xsize + x]);
    //         }
    //         printf("\n");
    //     }
    //     printf("---------------------------\n");
    // }

    // The size of the potential array, this is used later
    size_t potential_size = xsize * ysize * zsize * sizeof(*source);

    // Initalise the MD5 Hash
    MD5_CTX md5;
    MD5_CTX md5_demo;

    // Init the MD5 Hash
    MD5_Init(&md5);
    MD5_Init(&md5_demo);

    // Hash the First run
    unsigned char hash[MD5_DIGEST_LENGTH];
    MD5_Update(&md5, potential, potential_size);
    MD5_Final(hash, &md5);

    // Reset the variables
    memset(potential, 0, potential_size);
    memset(source, 0, potential_size);
    source[((zsize / 2 * ysize) + ysize / 2) * xsize + xsize / 2] = 1.0;

    // Run the Demo implementation
    demo_poisson_dirichlet(source, potential, 0.25, xsize, ysize, zsize, delta,
                      numiters, numcores);
    
    // printf("\n Demo Array\n");

    // for (int z=0; z<zsize; z++) {
    //     for (int y=0; y<ysize; y++) {
    //         for (int x=0; x<xsize; x++) {
    //             printf("%f ", potential[((z * ysize) + y) * xsize + x]);
    //         }
    //         printf("\n");
    //     }
    //     printf("---------------------------\n");
    // }

    // Hash the second run
    unsigned char demo_hash[MD5_DIGEST_LENGTH];
    MD5_Update(&md5_demo, potential, potential_size);
    MD5_Final(demo_hash, &md5_demo);

    // Check the hashes are equal
    assert(!memcmp(hash, demo_hash, MD5_DIGEST_LENGTH));

    return 0;
}
