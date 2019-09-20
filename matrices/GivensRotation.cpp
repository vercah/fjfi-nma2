#include <assert.h>
#include "GivensRotation.h"
#include <math.h>

GivensRotation::GivensRotation( int size )
: size( size )
{
}

bool GivensRotation::init( DenseMatrix& matrix, int row1, int row2 )
{
   assert( matrix.getRows() == size );
   assert( matrix.getColumns() == size );
   assert( row < size );
   assert( column < size );

   this->row1 = row1;
   this->row2 = row2;
   const double x_i = matrix( row1, row1 );
   const double x_j = matrix( row2, row1 );
   const double norm = sqrt( x_i * x_i + x_j * x_j );
   if( norm == 0.0 )
      return false;
   this->c = x_i / norm;
   this->s = x_j / norm;
   return true;
}

void GivensRotation::applyFromLeft( DenseMatrix& A )
{
   for( int j = 0; j < size; j++ )
   {
      const double aux1 = this->c  * A( this->row1, j ) + this->s * A( this->row2, j );
      const double aux2 = -this->s * A( this->row1, j ) + this->c * A( this->row2, j );
      A( row1, j ) = aux1;
      A( row2, j ) = aux2;
   }
}

void GivensRotation::applyFromRight( DenseMatrix& A )
{
   for( int i = 0; i < size; i++ )
   {
      const double aux1 = this->c * A( i, this->row1 ) + this->s * A( i, this->row2 );
      const double aux2 = -this->s * A( i, this->row1 ) + this->c * A( i, this->row2 );
      A( i, row1 ) = aux1;
      A( i, row2 ) = aux2;
   }
}

bool GivensRotation::computeQR( DenseMatrix& A, DenseMatrix& Q )
{
   const int size = A.getRows();
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j ? 1.0 : 0.0 );

   for( int j = 0; j < size - 1; j++ )
      for( int i = j + 1; i < size; i++ )
      {
         if( ! this->init( A, j, i ) )
            return false;
         this->applyFromLeft( A );
         this->applyFromRight( Q );
      }
   return true;
}
