#include <assert.h>
#include "HessenbergForm.h"
#include "HouseholderTransformation.h"

bool computeHessenbergForm( DenseMatrix& A, DenseMatrix& Q )
{
   assert( A.getRows() == A.getColumns() );
   Q.setDimensions( A.getRows(), A.getColumns() );
   const int size = A.getRows();
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j );
   
   for( int j = 0; j < size - 1; j++ )
   {
      HouseholderTransformation transformation( A );
      transformation
   }
}