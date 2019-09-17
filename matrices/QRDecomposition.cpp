#include "QRDecomposition.h"
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
         double aux( 0.0 );
         for( int i = 0; i < n; i ++  )
            aux += Q( i, j ) * Q( j, k );
         R( j, k ) = aux;

         for( int i = 0; i < n; i++ )
            Q( i, k ) -= aux * Q( i, j );
      }
      double norm( 0.0 );
      for( int i = 0; i < n; i++ )
         norm += Q( i, k ) * Q( i, k );
      R( k, k ) = sqrt( norm );
      for( int i = 0; i < n; i++ )
         Q( i, k ) /= R( k, k );
      for( int i = k + 1; i < n; i++ )
         R( i, k ) = 0.0;
   }
   return true;
}

bool QRDecomposition::computeByHouseholderTransformations( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   const int n = A.getRows();

   return true;
}

bool QRDecomposition::computeByGivensRotations( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   const int n = A.getRows();

   return true;
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

void QRDecomposition::checkOrthogonality( const DenseMatrix& Q, double& error )
{
   
}

