#include <assert.h>
#include "HouseholderTransformation.h"

HouseholderTransformation::HouseholderTransformation( int size )
: size( size )
{
}

void HouseholderTransformation::init( DenseMatrix& matrix, int row, int column )
{
   assert( matrix.getRows() == size );
   assert( matrix.getColumns() == size );
   assert( row < size );
   assert( column < size );

   w.setSize( size - row );
   for( int i = row; i < size; i++ )
      w[ i - row ] = matrix( i, column );

   const double sign_x1 = w[ 0 ] < 0.0 ? -1.0 : 1.0;
   w[ 0 ] += sign_x1 * w.l2Norm();
   //std::cout << "w -> " << w << std::endl;
   w *= 1.0 / w.l2Norm();
}

void HouseholderTransformation::apply( DenseMatrix& A )
{
   Vector A_T_w( w.getSize() );
   const int row = size - w.getSize();
   for( int i = row; i < size; i++ )
   {
      double aux( 0.0 );
      for( int j = row; j < size; j++ )
         aux += A( j, i ) * w[ j - row ];
      A_T_w[ i - row ] = aux;
   }
   //std::cout << "A_T_w = " << A_T_w << std::endl;
   for( int i = row; i < size; i++ )
      for( int j = row + 1; j < size; j++ )
         A( i, j ) -= 2.0 * w[ i ] * A_T_w[ j ];
   A( row, row ) = this->w.l2Norm();
   for( int i = row + 1; i < size; i++ )
      A( i, row ) = 0.0;
}

void HouseholderTransformation::computeQR( DenseMatrix& A, DenseMatrix& Q )
{
   const int size = A.getRows();
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j ? 1.0 : 0.0 );

   for( int i = 0; i < size - 1; i++ )
   {
      this->init( A, i, i );
      //std::cout << "w = " << w << std::endl;
      this->apply( A );
      //std::cout << "A = " << std::endl << A << std::endl;
      this->apply( Q );
   }
}
