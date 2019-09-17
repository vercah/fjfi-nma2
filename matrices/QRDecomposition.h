/*
 * File:   QRDecomposition.h
 * Author: oberhuber
 *
 * Created on September 17, 2019, 8:34 PM
 */

#pragma once

#include "../matrices/DenseMatrix.h"

class QRDecomposition
{
   public:

      QRDecomposition( DenseMatrix& A );

      /**
       * Compute QR decomposition
       * @param verbose
       * @return
       */
      bool computeByGrammSchmidt( DenseMatrix& Q, DenseMatrix& R, int verbose = 0 );

      /**
       * Compute QR decomposition
       * @param verbose
       * @return
       */
      bool computeByHouseholderTransformations( DenseMatrix& Q, DenseMatrix& R, int verbose = 0 );

      /**
       * Compute QR decomposition
       * @param verbose
       * @return
       */
      bool computeByGivensRotations( DenseMatrix& Q, DenseMatrix& R, int verbose = 0 );

      void restoreMatrix( DenseMatrix& Q, DenseMatrix& R, DenseMatrix& B );

      void getError( DenseMatrix& Q, DenseMatrix& R, DenseMatrix& A, double& max_error );

      void checkOrthogonality( const DenseMatrix& Q, double& error );

   protected:

      void print( std::ostream& str = std::cout ) const;

      DenseMatrix& A;
};




