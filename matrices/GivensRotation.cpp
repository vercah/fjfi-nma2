#include <assert.h>
#include "GivensRotation.h"

GivensRotation::GivensRotation( int size )
: size( size )
{
}

void GivensRotation::init( DenseMatrix& matrix, int row1, int row2, int column )
{
   assert( matrix.getRows() == size );
   assert( matrix.getColumns() == size );
   assert( row < size );
   assert( column < size );

   const double x_i = matrix( column, row1 );
   const double x_j = matrix( column, row2 );
   const double norm = sqrt( x_i * x_i + x_j * x_j );
   this->c = x_i / norm;
   this->s = x_j / norm;
}

void GivensRotation::apply( DenseMatrix& A )
{
   for( int j = 0; j < size; j++ )
   {
      const double aux1 = this->c  * A( row1, j ) + this->s * A( row2, j );
      const double aux2 = -this->s * A( row1, j ) + this->c * A( row2, j );
      A( row1, j ) = aux1;
      A( row2, j ) = aux2;
   }
}

void GivensRotation::computeQR( DenseMatrix& A, DenseMatrix& Q )
{
   const int size = A.getRows();
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j ? 1.0 : 0.0 );

   for( int i = 0; i < size - 1; i++ )
      for( int j = 0; j < size; j++ )
      {
      }
}
