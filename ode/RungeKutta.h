/* 
 * File:   RungeKutta.h
 * Author: oberhuber
 *
 * Created on February 7, 2018
 */

#pragma once

#include<algorithm>
#include "ODESolver.h"
#include "ODEProblem.h"

class RungeKutta : public ODESolver
{
   public:
      
      RungeKutta();
      
      bool setup( const int degreesOfFreedom );
      
      bool solve( const double integrationTimeStep,
                  const double stopTime,
                  double* time,
                  ODEProblem* problem,
                  double* u );
      
      ~RungeKutta();
      
   protected:
      
      double* k1;   // TODO: add other k-variables here
};

