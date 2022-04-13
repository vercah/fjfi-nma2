/* 
 * File:   poisson-1d.cpp
 * Author: oberhuber
 *
 * Created on Match 19, 2019, 10:41 AM
 */

#include <fstream>
#include <cmath>
#include "../Vector.h"
#include "../matrices/TridiagonalMatrix.h"
#include "../matrices/DenseMatrix.h"
#include "../gem/ThomasAlgorithm.h"
#include "../gem/GEM.h"
#include "../stationary/StationarySolver.h"

const int N = 1000;
const double h = 1.0 / ( double ) N;
const double h_sqr = h * h;
const double gamma_1 = 0.0;
const double gamma_2 = 0.1;

const bool useDirectSolver = false;

double f( const double& x )
{
   //return 10.0;
   //return 10.0 * x;
   //return 10.0 * ( 1.0 - 4.0 * x * x );
   return 250.0 * x * x *sin( 10 * M_PI * x );
}

int main( int argc, char* argv[] )
{   
   /***
    * Set-up the linear system
    */
   Vector u( N + 1 ), b( N + 1 );
   TridiagonalMatrix A( N+ 1, N + 1 );
  
   /***
    * Left boundary condition
    */
   u[ 0 ] = 0;
   b[ 0 ] = gamma_1;
   A( 0, 0 ) = 1.0;
   A( 0, 1 ) = 0.0;
   
   /****
    * Interior points
    */
   for( int i = 1; i < N; i++ )
   {
      u[ i ] = 0;
      b[ i ] = h_sqr * f( i * h );
      A( i, i - 1 ) = -1.0;
      A( i, i ) = 2.0;
      A( i, i + 1 ) = -1.0;
   }
   
   /****
    * Right boundary conditions
    */
   u[ N ] = 0;
   b[ N ] = gamma_2;
   A( N, N - 1 ) = 0.0;
   A( N, N ) = 1.0;
   
   /***
    * Solve the linear system
    */
   if( useDirectSolver )
   {
      ThomasAlgorithm solver( A, b );
      solver.solve( u );
   }
   else
   {
      StationarySolver solver( A, b );
      solver.setConvergenceResidue( 1.0e-4 );
      solver.setMaxIterations( 10000 );
      solver.solve( u, "sor", 1.9 );
   }
   
   /****
    * Write the solution to the output file
    */
   std::fstream f;
   f.open( "poisson-1d.txt", std::ios::out );
   u.writeGnuplot1D( f, h, 0 );
}

