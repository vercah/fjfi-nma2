/* 
 * File:   Euler.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 9:10 AM
 */

#ifndef EULER_H
#define	EULER_H

#include<algorithm>
#include "IntegratorBase.h"

template< typename Problem >
class Euler : public IntegratorBase
{
   public:
      
      Euler( Problem& problem )
      {
         this->k = new double[ problem.getDegreesOfFreedom() ];
      }
      
      bool solve( Problem& problem,
                  double* u )
      {
         const int dofs = problem.getDegreesOfFreedom();         
         double tau = std::min( this->integrationTimeStep, this->stopTime - this->time );
         while( this->time < this->stopTime )
         {
           problem.getRightHandSide( this->time, u, this->k );
           for( int i = 0; i < dofs; i++ )
              u[ i ] +=  tau * k[ i ];
            this->time += tau;
            tau = std::min( this->integrationTimeStep, this->stopTime - this->time );
         }
         return true;
      }
      
      ~Euler()
      {
         delete[] k;
      }
      
   protected:
      
      double* k;   
};

#endif	/* EULER_H */

