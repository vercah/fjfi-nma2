/* 
 * File:   gem.h
 * Author: oberhuber
 *
 * Created on September 28, 2016, 5:30 PM
 */

#pragma once

#include "matrices/DenseMatrix.h"
#include "real.h"

class GEM
{
   public:
      
      GEM( DenseMatrix& A,
           std::vector< Real >& b );
      
      bool solve( std::vector< Real >& x );
      
   protected:
      
      DenseMatrix& A;
      
      std::vector< Real >& b;
};

