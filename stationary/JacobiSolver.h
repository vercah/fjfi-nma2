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

class JacobiSolver
{
   public:
      
      JacobiSolver( Matrix& A,
                    Vector& b );
      
      bool solve( Vector& x, 
                  const int max_iterations = 100000,
                  const Real& convergence_residue = 1.0e-6,
                  int verbose = 0 );            
      
   protected:
      
      Matrix& A;
      
      Vector& b;
};

