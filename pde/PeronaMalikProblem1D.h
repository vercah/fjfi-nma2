/* 
 * File:   PeronaMalikProblem1D.h
 * Author: oberhuber
 *
 * Created on March 27, 2019, 2:55 PM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
#include "../ode/ODEProblem.h"

class PeronaMalikProblem1D : public ODEProblem
{
   public:
      
      PeronaMalikProblem1D( int size );
      
      int getDegreesOfFreedom();
      
      void setParameters();
      
      void setInitialCondition( double* u );
      
      void getRightHandSide( const double& t, double* _u, double* fu );
      
      bool writeSolution( const double& t, int step, const double* u );

      ~PeronaMalikProblem1D();
      
   protected:
      
      int size;
      
      double h, K_sqr = 1.0;
      
      double* p;
};


