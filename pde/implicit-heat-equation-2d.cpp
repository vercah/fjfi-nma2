/* 
 * File:   implicit-heat-equation-2d.cpp
 * Author: oberhuber
 *
 * Created on March 27, 2019, 10:41 AM
 */

#include <cstdlib>
#include "../matrices/EllpackMatrix.h"
#include "../Vector.h"
#include "../stationary/StationarySolver.h"
#include "HeatEquationProblem2D.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 0.01 );
const double timeStep( 0.01 );
const double integrationTimeStep( 0.01 );
const int size( 100 );

int main( int argc, char** argv )
{
   HeatEquationProblem2D problem( size, size );
    
   Vector u( size * size );
   problem.setInitialCondition( u.getData() );
   problem.writeSolution( 0.0, 0, u.getData() );
   
   EllpackMatrix A;
   A.setDimensions( size, size );
   Vector b( size );
   
   StationarySolver solver( A, b );
   solver.setMaxIterations( 100000 );
   
   /***
    * Set Dirichlet  boundary conditions
    */
   // TODO
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
           // TODO
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

