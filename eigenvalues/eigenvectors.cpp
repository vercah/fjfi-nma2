#include <assert.h>
#include <math.h>
#include "eigenvectors.h"
#include "../Vector.h"
#include "../matrices/TriangularOperations.h"

void getEigenvectors( const DenseMatrix& R, const DenseMatrix& T, DenseMatrix& eigenvectors, bool lowerTriangularTransformation )
{
   assert( R.getColumns() == R.getRows() );
   const int size = R.getColumns();
   Vector spectrum( size );
   for( int i = 0; i < size; i++ )
      spectrum [i ] = R( i, i );
   
   /***
    * Compute eigenvectors of R
    */
   DenseMatrix eigenvectorsR( size, size );
   for( int j = size - 1; j >= 0; j-- )
      for( int i = size - 1; i >= 0; i-- )
      {
         if( j < i )
            eigenvectorsR( i, j ) = 0.0;
         if( j == i )
            eigenvectorsR( i, j ) = 1.0;
         if( j > i )
         {
            /***
             * First case of eigenvalue of higher multiplicity
             */
            if( fabs( ( R( i, i ) - spectrum[ j ] ) ) < 1.0e-8 )
               eigenvectorsR( i, j ) = 0.0;
            else
            {
               double aux( 0.0 );
               for( int k = j; k > i; k-- )
                  aux += eigenvectorsR( k, j ) * R( i, k );
               eigenvectorsR( i, j ) = -aux / ( R( i, i ) - spectrum[ j ] );
            }
         }
      }

   /***
    * Transform to eigenvectors of A by multiplying with L
    */
   if( lowerTriangularTransformation )
      computeLTimesMatrix( T, eigenvectorsR, eigenvectors );
   else
      eigenvectors.matrixMultiplication( T, eigenvectorsR );
}

