/* 
 * File:   implicit-heat-equation-1d.cpp
 * Author: oberhuber
 *
 * Created on March 27, 2019, 10:41 AM
 */

#include <cstdlib>
#include "../matrices/TridiagonalMatrix.h"
#include "../Vector.h"
#include "../gem/ThomasAlgorithm.h"
#include "../stationary/StationarySolver.h"
#include "PeronaMalikProblem1D.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 0.5 );
const double timeStep( 0.01 );
const double integrationTimeStep( 0.001 );
const int size( 100 );
const double K_sqr = 0.001;

int main( int argc, char** argv )
{
   PeronaMalikProblem1D problem( size );
    
   Vector u( size ), p( size );
   problem.setInitialCondition( u.getData() );
   problem.writeSolution( 0.0, 0, u.getData() );
   
   TridiagonalMatrix A;
   A.setDimensions( size, size );
   Vector b( size );
   
   //ThomasAlgorithm solver( A, b );
   StationarySolver solver( A, b );
   solver.setMaxIterations( 100000 );
   
   /***
    * Set Dirichlet  boundary conditions
    */
   A.setElement( 0, 0, 1.0 );
   A.setElement( 0, 1, 0.0 );
   A.setElement( size - 1, size - 2, 0.0 );
   A.setElement( size - 1, size - 1, 1.0 );
   double time = initialTime;
   double lastTau = -1.0;
   const double h = 1.0 / ( double ) size;
   const double h_sqr = h * h;
   int step( 0 );
   while( time < finalTime )
   {
      double stopTime = std::min( time + timeStep, finalTime );
      std::cout << "Time = " << time << " step = " << step << std::endl;
      while( time < stopTime )
      {
         double currentTau = std::min( integrationTimeStep, stopTime - time );
         if( currentTau != lastTau )
         {
            /***
             * Set-up linear system
             */
            const double h_sqr = h * h;
            for( int i = 1; i < size - 1; i++ )
            {
               const double u_x = ( u[ i ] - u[ i -1 ] ) / h;
               p[ i ] = 1.0 / ( 1.0 + fabs( u_x ) / K_sqr );
            }
            
            const double lambda = currentTau / ( h_sqr );
            for( int i = 1; i < size - 1; i++ )
            {
               A.setElement( i, i - 1, -lambda * p[ i ]);
               A.setElement( i, i, 1.0 + lambda * ( p[ i ] + p[ i + 1 ] ) );
               A.setElement( i, i + 1, -lambda * p[ i + 1 ] );
            }
         }
         
         /***
          * Set-up right-hand side b
          */
         for( int i = 0; i < size; i++ )
            b[ i ] = u[ i ];
         
         /***
          * Solve the linear system
          */
         solver.solve( u );
         time += currentTau;
         lastTau = currentTau;
      }
      step++;
      problem.writeSolution( time, step, u.getData() );
   }
   return EXIT_SUCCESS;
}

