/* 
 * File:   SpeciesProblem.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include "ODEProblem.h"

using namespace std;

class SpeciesProblem : public ODEProblem
{
   public:
      
      SpeciesProblem();
      
      int getDegreesOfFreedom();
      
      void setParameters( const double& _a,
                          const double& _b,
                          const double& _c,
                          const double& _d );
      
      void getRightHandSide( const double& t, double* _u, double* fu );
         
      bool writeSolution( const double& t, int step, const double* u );
      
   protected:
      
      double a,b,c,d;
};