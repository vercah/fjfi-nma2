/* 
 * File:   nbody.cpp
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#include <cstdlib>
#include "NBodyProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "NBodySolver.h"

using namespace std;

typedef NBodyProblem Problem;
//typedef Euler< Problem > Integrator;
typedef Merson< Problem > Integrator;
const double initialTime( 0.0 );
const double finalTime( 1.0e3 );
const double timeStep( 4.0e-2 );
const double integrationTimeStep( 1.0e-6 );
const int particlesCount( 100 );

int main( int argc, char** argv )
{
    Problem problem( particlesCount );
    //problem.setParameters( 1.5, 1.0, 3.0, 1.0 );
    Integrator integrator( problem );
    integrator.setIntegrationTimeStep( integrationTimeStep );
    //integrator.setAdaptivity( 1.0e-8 );
    NBodySolver< Problem, Integrator > solver( problem, integrator );
    solver.solve( finalTime, timeStep );
    return EXIT_SUCCESS;
}

