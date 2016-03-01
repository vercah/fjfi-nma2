/* 
 * File:   hyperbolic.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "HyperbolicProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef HyperbolicProblem Problem;
typedef Euler< Problem > Integrator;
//typedef Merson< Problem > Integrator;
const double initialTime( 0.065 );
const double finalTime( 0.1125 );
const double timeStep( 1.0e-4 );

const double integrationTimeStep( 1.0e-10 );

int main( int argc, char** argv )
{
    Problem problem;
    Integrator integrator( problem );
    ODESolution solution;
    integrator.setIntegrationTimeStep( integrationTimeStep );
    ODESolver< Problem, Integrator > solver( problem, integrator );
    double initialCondition[ 1 ];
    initialCondition[ 0 ] = problem.getExactSolution( initialTime );
    solver.setInitialCondition( initialCondition );
    solver.solve( solution, initialTime, finalTime, timeStep );
    solution.write( "hyperbolic.txt", initialTime, timeStep );
    problem.writeExactSolution( "exact-hyperbolic.txt", initialTime, finalTime, timeStep, 1.0 );
    return EXIT_SUCCESS;
}

