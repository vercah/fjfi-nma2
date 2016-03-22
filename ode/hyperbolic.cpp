/* 
 * File:   hyperbolic.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "HyperbolicProblem.h"
#include "Euler.h"
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef HyperbolicProblem Problem;
typedef Euler< Problem > Integrator;
const double initialTime( 0.0 );
const double finalTime( 1000.0 );
const double timeStep( 1.0e-1 );

const double integrationTimeStep( 1.0e-2 );

int main( int argc, char** argv )
{
    Problem problem;
    problem.setEpsilon( 0.0 );
    Integrator integrator( problem );
    ODESolution solution;
    integrator.setIntegrationTimeStep( integrationTimeStep );
    ODESolver< Problem, Integrator > solver( problem, integrator );
    double initialCondition[ 2 ] = { 0.0, 1.0 };
    solver.setInitialCondition( initialCondition );
    solver.solve( solution, initialTime, finalTime, timeStep );
    solution.write( "hyperbolic.txt", initialTime, timeStep, 0 );
    return EXIT_SUCCESS;
}

