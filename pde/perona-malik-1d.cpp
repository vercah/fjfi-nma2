/* 
 * File:   heat-equation-1d.cpp
 * Author: oberhuber
 *
 * Created on March 26, 2019, 10:41 AM
 */

#include <cstdlib>
#include "HeatEquationProblem1D.h"
#include "../ode/Euler.h"
#include "../ode/Merson.h"
#include "../ode/ode-solve.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 0.01 );
const double timeStep( 0.0001 );
const double integrationTimeStep( 0.0001 );
const int size( 1000 );

int main( int argc, char** argv )
{
   HeatEquationProblem1D problem( size );
   
   Euler integrator; 
   //integrator.setAdaptivity( 1.0e-8 );
    
   double* u = new double[ problem.getDegreesOfFreedom() ];
   problem.setInitialCondition( u );
   problem.writeSolution( 0.0, 0, u );
   
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

