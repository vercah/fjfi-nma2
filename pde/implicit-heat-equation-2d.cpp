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
const double timeStep( 0.001 );
const double integrationTimeStep( 0.0001 );
const int size( 50 );

int main( int argc, char** argv )
{
   HeatEquationProblem2D problem( size, size );

   Vector u( size * size );
   problem.setInitialCondition( u.getData() );
   problem.writeSolution( 0.0, 0, u.getData() );

   EllpackMatrix A;
  A.setRowLength( 5 );
  A.setDimensions( size*size, size*size );

   Vector b( size * size );

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
   const double h = 1.0 / ( double ) (size-1);
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
            double lambda = currentTau/h_sqr;
            for (int i = 0; i<size*size; i++){
                for (int j = 0; j<size*size; j++){
                    if (i==j){
                        if((i < size)||(i >= size * size - size ) || ((i+1) % (size) == 1) || ((i+1)%(size)==0)){
                            A.setElement(i, j, 1);
                            continue;
                        }else{
                            A.setElement(i, j, 1 + 4 * lambda);
                            continue;
                        }
                    }
                    if (((j == i+1)||(j == i-1)||(j==i-(size))||j==i+(size)) && ((i+1) % (size) > 1) && ((i+1) % (size) < size - 1)
                    && ( i >= size) && ( i < size*size - (size))){
                        A.setElement(i,j,-lambda);
                        continue;
                    }
                }
            }
         }

         /***
          * Set-up right-hand side b
          */
         for( int i = 0; i < size*size; i++ )
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

