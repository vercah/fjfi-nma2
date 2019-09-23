#include <assert.h>
#include <math.h>
#include "GrammSchmidt.h"
#include "DenseMatrix.h"

bool GrammSchmidt::computeQR( DenseMatrix& Q, DenseMatrix& R )
{
   assert( Q.getRows() == Q.getColumns() );
   const int n = Q.getRows();
   R.setDimensions( n , n );

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
      if( R( k, k ) == 0.0 )
         return false;

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