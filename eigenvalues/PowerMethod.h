/* 
 * File:   PowerMethod.h
 * Author: oberhuber
 *
 * Created on November 12, 2016, 2:44 PM
 */

#pragma once

#include "../matrices/Matrix.h"

class PowerMethod
{
   public:
      
      PowerMethod( const Matrix& A );
      
      void setMaxIterations( const int max_iterations );
      
      void setConvergenceResidue( const Real& convergence_resideu );      
      
      bool getEigenvalue( Vector& x, 
                          Real& lambda,
                          bool smallest = false,
                          int verbose = 0 ) const; 

   protected:
      
      const Matrix& A;
      
      int max_iterations;
      
      Real convergence_residue;
};

