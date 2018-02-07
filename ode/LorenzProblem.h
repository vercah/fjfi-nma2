/* 
 * File:   LorenzProblem.h
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

class LorenzProblem : public ODEProblem
{
   public:
      
      LorenzProblem();
      
      void setParameters( const double& sigma,
                          const double& rho,
                          const double& beta );
      
      int getDegreesOfFreedom();
      
      void getRightHandSide( const double& t, const double* _u, double* fu );
      
      bool writeSolution( const double& t, int step, const double* u );
         
   protected:
      
      double sigma, rho, beta;
};

