/* 
 * File:   ode-solve.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 8:48 AM
 */


#include <iostream>
#include <cmath>
#include "ODEProblem.h"
#include "ODESolver.h"

bool solve( const double initialTime,
            const double finalTime,
            const double timeStep,
            const double integrationTimeStep, 
            ODEProblem* problem,
            ODESolver* solver,
            double* u )
{
   solver->setup( problem->getDegreesOfFreedom() );
   const int timeStepsCount = std::ceil( std::max( 0.0, finalTime - initialTime ) / timeStep );
   double time( initialTime );
   for( int k = 1; k <= timeStepsCount; k++ )
   {
      std::cout << "Solving time step " << k << " / " << timeStepsCount << " => " << 
         ( double ) k / ( double ) timeStepsCount * 100.0 << "% " << std::endl;
      if( !  solver->solve( integrationTimeStep,
                            time + timeStep,  // stopTime
                            &time,
                            problem,
                            u ) )
         return false;
      time += timeStep;
      problem->writeSolution( time, k, u );
   }
   std::cout << "Done." << std::endl;
   return true;
}

