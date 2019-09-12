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
   w *= 1.0 / w.l2Norm();
}

void HouseholderTransformation::computeTransformationTimesMatrix( const DenseMatrix& A, DenseMatrix& result )
{
}
