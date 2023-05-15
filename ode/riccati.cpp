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
#include "RungeKutta.h"

using namespace std;

const double initialTime( 1 );
const double finalTime( 2 );
const double timeStep( 0.0125 );
const double integrationTimeStep( 0.0125 );

int main( int argc, char** argv )
{
    RiccatiProblem problem;
    //Euler integrator;
    RungeKutta integrator;


    /***
     * Set initial condition
     */
    double u  = problem.getExactSolution( initialTime );
    problem.writeSolution( initialTime, 0, &u );
    
    problem.writeExactSolution( "exact-riccati.txt", 
                                initialTime,
                                finalTime,
                                timeStep );

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

