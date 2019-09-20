#include "QRDecomposition.h"
#include "../matrices/HouseholderTransformation.h"
#include "../matrices/GivensRotation.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <math.h>

#include "QRDecomposition.h"

QRDecomposition::QRDecomposition( DenseMatrix& A )
: A( A )
{
}

bool QRDecomposition::computeByGrammSchmidt( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   const int n = A.getRows();

   Q = A;

   for( int k = 0; k < n; k++ )
   {
      
      for( int j = 0; j < k - 1; j++ )
      {
         /**
          * Compute the scalar product of j-th and k-th column
          */
         double aux( 0.0 );
         for( int i = 0; i < n; i ++  )
            aux += Q( i, j ) * Q( i, k );

         /**
          * Store the result into the matrix R
          */
         R( j, k ) = aux;

         /**
          * Subtract projection of j-th column from k-th column
          */
         for( int i = 0; i < n; i++ )
            Q( i, k ) -= aux * Q( i, j );
      }

      /**
       * Compute norm of the k-th column
       */
      double norm( 0.0 );
      for( int i = 0; i < n; i++ )
         norm += Q( i, k ) * Q( i, k );

      /**
       * Store it on the diagonal of matrix R
       */
      R( k, k ) = sqrt( norm );

      /**
       * Normalize k-th column of matrix Q
       */
      for( int i = 0; i < n; i++ )
         Q( i, k ) /= R( k, k );

      /**
       * Reset the rest of k-th column of matrix R
       */
      for( int i = k + 1; i < n; i++ )
         R( i, k ) = 0.0;
   }
   return true;
}

bool QRDecomposition::computeByHouseholderTransformations( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   HouseholderTransformation householder( A.getRows() );
   R = A;
   householder.computeQR( R, Q );
   return true;
}

bool QRDecomposition::computeByGivensRotations( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   GivensRotation givens( A.getRows() );
   R = A;
   return givens.computeQR( R, Q );
}


void QRDecomposition::restoreMatrix( DenseMatrix& Q, DenseMatrix& R, DenseMatrix& B )
{
   assert( B.getColumns() == A.getColumns() );
   assert( B.getRows() ==  A.getRows() );

   B.matrixMultiplication( Q, R );
}

void QRDecomposition::getError( DenseMatrix& Q, DenseMatrix& R, DenseMatrix& A, double& max_error )
{
   assert( A.getRows() == A.getColumns() );
   const int size = A.getRows();
   DenseMatrix m( size, size );
   this->restoreMatrix( Q, R, m );
   m -= A;
   max_error = m.maxNorm();
}