/* 
 * File:   LUDecomposition.h
 * Author: oberhuber
 *
 * Created on October 17, 2016, 8:34 PM
 */

#pragma once

#include "../matrices/DenseMatrix.h"

class LUDecomposition
{
   public:
      
      LUDecomposition( DenseMatrix& A );
      
      bool solve( Vector& x, int verbose = 0 );
            
      bool computeByGEM( int verbose = 0 );
      
      bool computeByCrout( int verbose = 0 );
      
      void restoreMatrix( DenseMatrix& B );
      
   protected:
      
      void print( std::ostream& str = std::cout ) const;
      
      DenseMatrix& A;
};




