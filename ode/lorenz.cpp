/* 
 * File:   lorentz.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "LorenzProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "ode-solve.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 100.0 );
const double timeStep( 1.0e-2 );

const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    LorenzProblem problem;
    problem.setParameters( 10.0, 28.0, 8.0/3.0 );
    
    Merson integrator;

    double u[ 3 ] = { 1.0, 1.0, 1.0 };

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

