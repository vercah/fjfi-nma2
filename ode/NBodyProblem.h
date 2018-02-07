/* 
 * File:   NBodyProblem.h
 * Author: oberhuber
 *
 * Created on March 10, 2017, 2:55 PM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
#include "ODEProblem.h"

class NBodyProblem : public ODEProblem
{
   public:
      
      NBodyProblem( int particlesCount, int dimension = 2 );
      
      int getDegreesOfFreedom();
      
      void setParameters();
      
      void setInitialCondition( double* u );
      
      void getRightHandSide( const double& t, const double* _u, double* fu );
      
      bool writeSolution( const double& t, int step, const double* u );

      ~NBodyProblem();
      
   protected:
      
      int dimension, particlesCount;
      
      double* masses;
      
      double g;
};


