/* 
 * File:   HyperbolicProblem.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include "ODEProblem.h"


class HyperbolicProblem : public ODEProblem
{
   public:
      
      HyperbolicProblem()
      { 
         this->epsilon = 1.0;
      }
      
      int getDegreesOfFreedom() { return 2; }
      
      void setEpsilon( const double& eps )
      {
         this->epsilon = eps;
      }
      
      void getRightHandSide( const double& t, const double* _u, double* fu )
      {
         const double& u1 = _u[ 0 ];
         const double& u2 = _u[ 1 ];
         fu[ 0 ] = u2;
         fu[ 1 ] = -u1 - this->epsilon * u1 * u1 * u2;
         //std::cout << " t = " << t << " " << fu[ 0 ] << " " << fu[ 1 ] << std::endl;
      }
      
      bool writeSolution( const double& t, int step, const double* u )
      {
         
      }
      
         
   protected:
      
      double epsilon;
};

