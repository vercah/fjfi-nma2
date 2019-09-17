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

      /**
       * Compute LU decomposition with ones on diagonal of R (U)
       * @param verbose
       * @return
       */
      bool computeByGEM( int verbose = 0 );

      /**
       * Compute LU decomposition with ones on diagonal of R (U)
       * @param verbose
       * @return
       */
      bool computeByCrout( int verbose = 0 );

      /**
       * Compute LU decomposition with ones on diagonal of L
       * @param verbose
       * @return
       */
      bool computeByDoolitle( int verbose = 0 );

      void restoreMatrix( DenseMatrix& B, bool ones_on_L = false );

      void getError( DenseMatrix& A, double& max_error, bool ones_on_L = false );

   protected:

      void print( std::ostream& str = std::cout ) const;

      DenseMatrix& A;
};




