/* 
 * File:   gem.h
 * Author: oberhuber
 *
 * Created on September 28, 2016, 5:30 PM
 */

#pragma once

#include "../matrices/DenseMatrix.h"
#include "../Vector.h"
#include "../real.h"
#include <ostream>

class GEM
{
   public:
      
      GEM( DenseMatrix& A,
           Vector& b );
      
      bool solve( Vector& x, int verbose = 0 );
      
      bool solveWithPivoting( Vector& x, int verbose = 0 );
      
      bool computeLUDecomposition( int verbose = 0 );
      
   protected:
      
      void print( std::ostream& str = std::cout ) const;
      
      DenseMatrix& A;
      
      Vector& b;
};

