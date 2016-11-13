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
      
      bool getLargestEigenvalue( Vector& x, 
                                 const int max_iterations = 100000,
                                 const Real& convergence_residue = 1.0e-6,
                                 int verbose = 0 ); 
      
      bool getSmallestEigenvalue( Vector& x, 
                                 const int max_iterations = 100000,
                                 const Real& convergence_residue = 1.0e-6,
                                 int verbose = 0 ); 

   protected:
      
      const Matrix& A;
      
      int max_iterations;
      
      Real convergence_residue;
      
};

