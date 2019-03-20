/* 
 * File:   species.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "SpeciesProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "ode-solve.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 10.0 );
const double timeStep( 1.0e-2 );

const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    SpeciesProblem problem;
    problem.setParameters( 0.5, 0.25, 0.5, 0.95 );
    Merson integrator;

    double u[ 2 ] = { 7.5, 0.25 };
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

