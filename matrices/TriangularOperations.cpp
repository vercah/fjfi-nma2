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

void computeRTimesL( const DenseMatrix& LU, DenseMatrix& result )
{
   int size = LU.getRows();
   assert( size == LU.getColumns() );
   assert( size == result.getRows() );
   assert( size == result.getColumns() );

   DenseMatrix L( size, size ), R( size, size );
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
      {
         if( i > j )
         {
            L( i, j ) = LU( i, j );
            R( i, j ) = 0.0;
         }
         if( i == j )
         {
            L( i, j ) = 1.0;
            R( i, j ) = LU( i, j );
         }
         if( i < j )
         {
            L( i, j ) = 0.0;
            R( i, j ) = LU( i, j );
         }
      }
   result.matrixMultiplication( R, L );

   /*for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
      {
         double aux( 0.0 );
         for( int k = std::max( i, j ); k < size; k++ )
            if( k == i )
               aux += LU( k, j );
            else aux += LU( i, k ) * LU( k, j );
         result( i, j ) = aux;
      }*/
}