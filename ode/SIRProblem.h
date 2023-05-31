#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include "ODEProblem.h"

using namespace std;

class SIRProblem : public ODEProblem
{
   public:

      SIRProblem();

      void setParameters( const double& N,
                          const double& nat,
                          const double& m,
                          const double& b,
                          const double& c,
                          const double& f );

      int getDegreesOfFreedom();

      void getRightHandSide( const double& t, double* _sir, double* fsir );

      bool writeSolution( const double& t, int step, const double* sir );

   protected:

      double N, nat, m, b, c, f;
};

