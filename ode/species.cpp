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
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef SpeciesProblem Problem;
//typedef Euler< Problem > Integrator;
typedef Merson< Problem > Integrator;
const double initialTime( 0.0 );
const double finalTime( 10.0 );
const double timeStep( 1.0e-2 );

const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    Problem problem;
    problem.setParameters( 1.5, 1.0, 3.0, 1.0 );
    Integrator integrator( problem );
    ODESolution solution;
    integrator.setIntegrationTimeStep( integrationTimeStep );
    ODESolver< Problem, Integrator > solver( problem, integrator );
    double initialCondition[ 2 ] = { 7.5, 0.25 };
    solver.setInitialCondition( initialCondition );
    solver.solve( solution, initialTime, finalTime, timeStep );
    solution.write( "species-1.txt", initialTime, timeStep, 0 );
    solution.write( "species-2.txt", initialTime, timeStep, 1 );
    solution.write( "species.txt" );
    return EXIT_SUCCESS;
}

