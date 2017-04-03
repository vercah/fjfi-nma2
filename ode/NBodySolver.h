/* 
 * File:   NBodySolver.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 8:48 AM
 */

#ifndef NBodySOLVER_H
#define	NBodySOLVER_H

#include <iostream>
#include <cmath>

template< typename Problem,
          typename Integrator >
class NBodySolver
{
   public:
      
      NBodySolver( Problem& problem,
                 Integrator& integrator )
      : problem( problem ),
        integrator( integrator )
      {
         this->u = new double[ problem.getDegreesOfFreedom() ];
      }
      
      void setInitialCondition( const double* initialCondition )
      {
         for( int i = 0; i < problem.getDegreesOfFreedom(); i++ )
            u[ i ] = initialCondition[ i ];
      }
      
      bool solve( const double& finalTime,
                  const double& timeStep )
      {
         const int timeStepsCount = std::ceil( finalTime / timeStep );
         problem.setInitialCondition( this->u );
         problem.writeSolution( this->u, 0 );
         double time( 0.0 );         
         for( int k = 1; k <= timeStepsCount; k++ )
         {
            //std::cout << "Solving time step " << k << " / " << timeStepsCount << " => " << 
            //   ( double ) k / ( double ) timeStepsCount * 100.0 << "% " << std::endl;
            this->integrator.setTime( time );
            this->integrator.setStopTime( time + timeStep );
            if( ! this->integrator.solve( problem, u ) )
               return false;
            problem.writeSolution( this->u, k );
            time += timeStep;
         }
         std::cout << "Done." << std::endl;
         return true;
      }
      
   protected:
      
      Problem& problem;
      
      Integrator& integrator;
      
      double* u;
};


#endif	/* NBodySOLVER_H */

