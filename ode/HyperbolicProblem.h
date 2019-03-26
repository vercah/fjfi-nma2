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

using namespace std;

class HyperbolicProblem : public ODEProblem
{
   public:
      
      HyperbolicProblem();
      
      void setEpsilon( const double& eps );
      
      int getDegreesOfFreedom();
     
      void getRightHandSide( const double& t, double* _u, double* fu );
      
      bool writeSolution( const double& t, int step, const double* u );      
         
   protected:
      
      double epsilon;
};

