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
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef LorenzProblem Problem;
//typedef Euler< Problem > Integrator;
typedef Merson< Problem > Integrator;
const double initialTime( 0.0 );
const double finalTime( 100.0 );
const double timeStep( 1.0e-2 );

const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    Problem problem;
    problem.setParameters( 10.0, 28.0, 8.0/3.0 );
    Integrator integrator( problem );
    ODESolution solution;
    integrator.setIntegrationTimeStep( integrationTimeStep );
    ODESolver< Problem, Integrator > solver( problem, integrator );
    double initialCondition[ 3 ] = { 1.0, 1.0, 1.0 };
    solver.setInitialCondition( initialCondition );
    solver.solve( solution, initialTime, finalTime, timeStep );
    solution.write( "lorenz.txt" );
    return EXIT_SUCCESS;
}

