/* 
 * File:   TransportEquationProblem1D.h
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

enum Scheme { FDM, LaxFriedrichs, Upwind };

class TransportEquationProblem1D : public ODEProblem
{
   public:
      
      TransportEquationProblem1D( int size );
      
      int getDegreesOfFreedom();
      
      void setAlpha( const double& _alpha );
      
      void setLFEpsilon( const double& eps );
      
      void setTau( const double& tau );
      
      void setScheme( Scheme s );
      
      void setInitialCondition( double* u );
      
      void getRightHandSide( const double& t, double* _u, double* fu );
      
      bool writeSolution( const double& t, int step, const double* u );

      ~TransportEquationProblem1D();
      
   protected:
      
      int size;
      
      double h, alpha = 1.0;
      
      // Lax-Friedrichs regularization
      double lfEpsilon = 1.0;
      
      double tau = 1.0;
      
      Scheme scheme = FDM;
};


