#include "ThomasAlgorithm.h"

ThomasAlgorithm::ThomasAlgorithm( TridiagonalMatrix& A,
                                  Vector& b )
: A( A ), b( b )
{
}
      
bool ThomasAlgorithm::solve( Vector& x, int verbose )
{
   /****
    * First phase: Eliminate elements under diagonal
    */
   const int n = A.getColumns();
   A( 0, 1 ) /= A( 0, 0 );
   b[ 0 ] /= A( 0, 0 );
   A( 0, 0 ) = 1.0;
   for( int k = 1; k < n; k++ )
   {
      b[ k ] = ( b[ k ] - A( k, k - 1 ) * b[ k - 1 ] ) / ( A( k, k ) - A( k, k - 1 ) * A( k - 1, k) );
      if( k < n - 1 )
      {
         A( k, k + 1 ) = A( k, k + 1) / ( A( k, k ) - A( k, k - 1 ) * A( k - 1, k ) );
         A( k, k ) = 1.0;
      }
   }
   if( verbose )
      this->print( std::cout );
   
   /****
    * Second phase: Backward substitution
    */
   for( int k = n - 2; k >= 0; k-- )
      b[ k ] = b[ k ] - A( k, k+1 ) * b[ k + 1 ];
   
}
      
void ThomasAlgorithm::print( std::ostream& str ) const
{
   
}
