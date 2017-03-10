/* 
 * File:   lorentz.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "LorentzProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "ODESolver.h"
#include "ODESolution.h"

using namespace std;

typedef LorentzProblem Problem;
//typedef Euler< Problem > Integrator;
typedef Merson< Problem > Integrator;
const double initialTime( 0.0 );
const double finalTime( 50.0 );
const double timeStep( 1.0e-2 );

const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    Problem problem;
    problem.setParameters( 1.2, 7.0/3.0, 0.9 );
    Integrator integrator( problem );
    ODESolution solution;
    integrator.setIntegrationTimeStep( integrationTimeStep );
    ODESolver< Problem, Integrator > solver( problem, integrator );
    double initialCondition[ 3 ] = { 1.0, 1.0, 1.0 };
    solver.setInitialCondition( initialCondition );
    solver.solve( solution, initialTime, finalTime, timeStep );
    solution.write( "lorentz.txt" );
    return EXIT_SUCCESS;
}

