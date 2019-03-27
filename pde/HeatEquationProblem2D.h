/* 
 * File:   HeatEquationProblem2D.h
 * Author: oberhuber
 *
 * Created on March 26, 2019, 2:55 PM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
#include "../ode/ODEProblem.h"

class HeatEquationProblem2D : public ODEProblem
{
   public:
      
      HeatEquationProblem2D( int sizeX, int sizeY );
      
      int getDegreesOfFreedom();
      
      void setParameters();
      
      void setInitialCondition( double* u );
      
      void getRightHandSide( const double& t, double* _u, double* fu );
      
      bool writeSolution( const double& t, int step, const double* u );

      ~HeatEquationProblem2D();
      
   protected:
      
      int sizeX, sizeY;
      
      double hx, hy;
};


