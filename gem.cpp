/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GEM.h"

GEM::GEM( DenseMatrix& A,
          std::vector< Real >& b )
: A( A ), b( b )
{  
   assert( A.getRows() == b.size() &&
           A.getColumns() == b.size() );
}
      
bool GEM::solve( std::vector< Real >& x )
{
   assert( b.size() == x.size() );
   
   const int n = A.getRows();
   
   for( int k = 0; k < n; k++ )
   {
      /****
       * Divide the k-th row by pivot
       */
      const Real& pivot = A( k, k );
      b[ k ] /= pivot;
      for( int j = k+1; j < n; j++ )
         A( k, j ) /= pivot;
      A( k, k ) = 1.0;
      
      /****
       * Subtract the k-th row from the rows bellow
       */
      for( int i = k+1; i < n; i++ )
      {
         for( j = k+1; j < n; j++ )
            A( i, j ) -= A( i, k ) * A( k, j );
         b[ i ] -= A( i, k ) * b[ k ];
         A( i, k ) = 0.0;
      }
   }
   
}
