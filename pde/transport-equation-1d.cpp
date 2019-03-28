/* 
 * File:   transport-equation-1d.cpp
 * Author: oberhuber
 *
 * Created on March 28, 2019, 10:41 AM
 */

#include <cstdlib>
#include "TransportEquationProblem1D.h"
#include "../ode/Euler.h"
#include "../ode/Merson.h"
#include "../ode/ode-solve.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 1.0 );
const double timeStep( 0.01 );
const double integrationTimeStep( 0.000001 );
const int size( 1000 );

int main( int argc, char** argv )
{
   TransportEquationProblem1D problem( size );
   problem.setAlpha( 5.0 );
   problem.setLFEpsilon( 0.005 );
   //problem.setScheme( FDM );
   problem.setTau( integrationTimeStep );
   problem.setScheme( LaxFriedrichs );
   problem.setScheme( Upwind );
   
   Euler integrator; 
    
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

