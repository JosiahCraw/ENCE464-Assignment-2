/// Solve Poisson's equation for a rectangular box with Dirichlet
/// boundary conditions on each face.
/// \param source is a pointer to a flattened 3-D array for the source function
/// \param potential is a pointer to a flattened 3-D array for the calculated potential
/// \param xsize is the number of elements in the x-direction
/// \param ysize is the number of elements in the y-direction
/// \param zsize is the number of elements in the z-direction
/// \param delta is the voxel spacing in all directions
/// \param numiters is the number of iterations to perform
/// \param numcores is the number of CPU cores to use.  If 0, an optimal number is chosen
/// \return 0 on success.
int poisson_dirichlet (double * __restrict__ source, double *__restrict__ potential,
                       unsigned int xsize,  unsigned int ysize, unsigned int zsize,
                       double delta, unsigned int numiters, unsigned int numcores)
{
    // source[i, j, k] is accessed with source[((k * ysize) + j) * xsize + i]
    
    return 0;
}
