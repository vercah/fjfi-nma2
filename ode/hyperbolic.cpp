/* 
 * File:   hyperbolic.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include "HyperbolicProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "ode-solve.h"

typedef HyperbolicProblem Problem;

const double initialTime( 0.0 );
const double finalTime( 100.0 );
const double timeStep( 1.0e-1 );
const double integrationTimeStep( 0.1 );

int main( int argc, char** argv )
{
    HyperbolicProblem problem;
    problem.setEpsilon( 0.0 );
    Merson integrator;

    //integrator.setAdaptivity( 1.0e-5 );
        
    double u[ 2 ] = { 0.0, 1.0 };
    
    if( ! solve( initialTime,
                 finalTime,
                 timeStep,
                 integrationTimeStep,
                 &problem,
                 &integrator,
                 u ) )
       return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

