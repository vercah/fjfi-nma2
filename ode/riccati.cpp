/* 
 * File:   riccati.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "RiccatiProblem.h"
#include "Euler.h"
#include "ode-solve.h"
#include "ODESolution.h"

using namespace std;

const double initialTime( 0.12 );
const double finalTime( 0.15 );
const double timeStep( 1.0e-3 );
const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    RiccatiProblem problem;
    Euler integrator;

    double u  = problem.getExactSolution( initialTime );

    if( ! solve( initialTime,
                 finalTime,
                 timeStep,
                 integrationTimeStep,
                 &problem,
                 &integrator,
                 &u ) )
       return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

