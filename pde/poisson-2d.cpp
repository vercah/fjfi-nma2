/* 
 * File:   poisson-1d.cpp
 * Author: oberhuber
 *
 * Created on Match 19, 2019, 10:41 AM
 */

#include <fstream>
#include <cmath>
#include "../Vector.h"
#include "../matrices/EllpackMatrix.h"
#include "../matrices/DenseMatrix.h"
#include "../stationary/StationarySolver.h"

const int N = 50;
const double h = 1.0 / ( double ) N;
const double h_sqr = h * h;

double f( const double& x, const double& y )
{
   //return 10.0;
   return 10.0 * x * y;
   //return 10.0 * ( 1.0 - 2.0 * x * x - 2.0 * y * y );
   //return 250.0 * x * x *sin( 10 * M_PI * ( x * x + y * y ) );
}

int main( int argc, char* argv[] )
{   
   /***
    * Set-up the linear system
    */
   const int dofs = ( N + 1 ) * ( N + 1 );
   Vector u( dofs ), b( dofs );
   EllpackMatrix A( dofs, dofs );
   A.setRowLength( 5 );
     
   for( int j = 0; j <= N; j++ )
      for( int i = 0; i <= N; i++ )
      {
         // Set-up the linear system matrix here.
      }
   
   /***
    * Solve the linear system
    */
   StationarySolver solver( A, b );
   solver.setConvergenceResidue( 1.0e-4 );
   solver.setMaxIterations( 10000 );
   solver.solve( u, "richardson", 1.0 );
   
   /****
    * Write the solution to the output file
    */
   std::fstream f;
   f.open( "poisson-2d.txt", std::ios::out );
   u.writeGnuplot2D( f, N + 1, N + 1, h, h, 0, 0 );
}

