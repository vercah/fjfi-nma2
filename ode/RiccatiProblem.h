/* 
 * File:   RiccatiProblem.h
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

class RiccatiProblem : public ODEProblem
{
   public:
      
      RiccatiProblem();
      
      int getDegreesOfFreedom();
      
      void getRightHandSide( const double& t, const double* _u, double* fu );
      
      double getExactSolution( const double& t ,
                               const double& c = 1.0 );
      
      bool writeExactSolution( const char*  fileName, 
                               const double& initialTime,
                               const double& finalTime,
                               const double& timeStep,
                               const double& c = 1.0 );
      
      bool writeSolution( const double& t, int step, const double* u );
      
      double getL1Error( const double timeStep );
      
      double getL2Error( const double timeStep );
      
      double getMaxError();
      
   protected:
      
      double l1Error, l2Error, maxError;
};

