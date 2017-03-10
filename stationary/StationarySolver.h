/* 
 * File:   JacobiSolver.h
 * Author: oberhuber
 *
 * Created on October 23, 2016, 7:35 PM
 */

#pragma once

#include "../matrices/Matrix.h"
#include "../Vector.h"
#include "../real.h"
#include <ostream>

class StationarySolver
{
   public:
      
      StationarySolver( const Matrix& A,
                        Vector& b );
      
      void setMaxIterations( const int max_iterations );
      
      void setConvergenceResidue( const Real& convergence_residue );
      
      bool solve( Vector& x, 
                  const std::string& method = "sor",
                  const Real& relaxation = 1.0,
                  int verbose = 0 );            
      
   protected:
      
      const Matrix& A;
      
      Vector& b;
      
      int max_iterations;
      
      Real convergence_residue;
};

