/* 
 * File:   poisson-1d.cpp
 * Author: oberhuber
 *
 * Created on Match 19, 2019, 10:41 AM
 */

#include <fstream>
#include "../Vector.h"
#include "../matrices/TridiagonalMatrix.h"
#include "../matrices/DenseMatrix.h"
#include "../gem/ThomasAlgorithm.h"
#include "../gem/GEM.h"
#include "../stationary/StationarySolver.h"

const int N = 100;
const double h = 1.0 / ( double ) N;
const double h_sqr = h * h;
const double gamma_1 = 0.0;
const double gamma_2 = 1.0;

const bool useDirectSolver = true;

double f( const double& x )
{
   return 10.0 * ( 1.0 - 4.0 * x * x );
}

int main( int argc, char* argv[] )
{   
   /***
    * Set-up the linear system
    */
   Vector u( N + 1 ), b( N + 1 );
   TridiagonalMatrix A( N+ 1, N + 1 );
  
   u[ 0 ] = 0;
   b[ 0 ] = gamma_1;
   A( 0, 0 ) = 1.0;
   A( 0, 1 ) = 0.0;
   for( int i = 1; i < N; i++ )
   {
      u[ i ] = 0;
      b[ i ] = h_sqr * f( i * h );
      A( i, i - 1 ) = -1.0;
      A( i, i ) = 2.0;
      A( i, i + 1 ) = -1.0;
   }
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
      solver.solve( u, "richardson", 1.0 );
   }
   
   /****
    * Write the solution to the output file
    */
   std::fstream f;
   f.open( "poisson-1d.txt", std::ios::out );
   for( int i = 0; i <= N; i++ )
      f << i * h << " " << u[ i ] << std::endl;
}

