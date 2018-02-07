/* 
 * File:   nbody.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "NBodyProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "NBodySolver.h"
#include "ode-solve.h"

using namespace std;

typedef NBodyProblem Problem;
const double initialTime( 0.0 );
const double finalTime( 1.0e3 );
const double timeStep( 4.0e-2 );
const double integrationTimeStep( 1.0e-6 );
const int particlesCount( 100 );

int main( int argc, char** argv )
{
   Problem problem( particlesCount );
   
   Euler integrator; 
   //integrator.setAdaptivity( 1.0e-8 );
    
   double* u = new double[ problem.getDegreesOfFreedom() ];
   problem.setInitialCondition( u );
   
   if( ! solve( initialTime,
            finalTime,
            timeStep,
            integrationTimeStep,
            &problem,
            &integrator,
            u ) )
   {
      delete[] u;
      return EXIT_FAILURE;
   }
   delete[] u;
   return EXIT_SUCCESS;
}

