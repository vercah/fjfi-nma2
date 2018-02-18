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

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 0.15 );
const double timeStep( 1.0e-4 );
const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    RiccatiProblem problem;
    Euler integrator;

    /***
     * Set initial condition
     */
    double u  = problem.getExactSolution( initialTime );

    if( ! solve( initialTime,
                 finalTime,
                 timeStep,
                 integrationTimeStep,
                 &problem,
                 &integrator,
                 &u ) )
       return EXIT_FAILURE;
    
    cout << "L1 error: " << problem.getL1Error( timeStep ) << endl
         << "L2 error: " << problem.getL2Error( timeStep ) << endl
         << "Max error: " << problem.getMaxError() << endl;
    
    return EXIT_SUCCESS;
}

