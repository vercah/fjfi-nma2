#include <assert.h>
#include "TriangularOperations.h"


void computeMatrixTimesL( const DenseMatrix& A, const DenseMatrix& LU, DenseMatrix& result )
{
   int size = A.getRows();
   assert( size == A.getColumns() );
   assert( size == LU.getRows() );
   assert( size == LU.getColumns() );
   assert( size == result.getRows() );
   assert( size == result.getColumns() );

   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
      {
         double aux( A( i, j ) );
         for( int k = j + 1; k < size; k++ )
            aux += A( i, k ) * LU( k, j );
         result( i, j ) = aux;
      }
}

void computeLTimesMatrix( const DenseMatrix& LU, const DenseMatrix& A, DenseMatrix& result )
{
   int size = A.getRows();
   assert( size == A.getColumns() );
   assert( size == LU.getRows() );
   assert( size == LU.getColumns() );
   assert( size == result.getRows() );
   assert( size == result.getColumns() );

   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
      {
         double aux( A( i, j ) );
         for( int k = 0; k < i; k++ )
            aux += LU( i, k ) * A( k, j );
         result( i, j ) = aux;
      }
}