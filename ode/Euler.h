/* 
 * File:   Euler.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 9:10 AM
 */

#pragma once

#include<algorithm>
#include "ODESolver.h"
#include "ODEProblem.h"

class Euler : public ODESolver
{
   public:
      
      Euler()
      {
         this-> k = 0;
      }
      
      bool setup( const int degreesOfFreedom )
      {
         this->k = new double[ degreesOfFreedom ];
         if( ! this->k )
            return false;
         return true;
      }
      
      bool solve( const double integrationTimeStep,
                  const double stopTime,
                  double* time,
                  ODEProblem* problem,
                  double* u )
      {
         const int dofs = problem->getDegreesOfFreedom();         
         double tau = std::min( integrationTimeStep, stopTime - *time );
         while( *time < stopTime )
         {
           problem->getRightHandSide( *time, u, this->k );
           for( int i = 0; i < dofs; i++ )
              u[ i ] +=  tau * k[ i ];
            *time += tau;
            tau = std::min( integrationTimeStep, stopTime - *time );
         }
         return true;
      }
      
      ~Euler()
      {
         if( k ) delete[] k;
      }
      
   protected:
      
      double* k;   
};

