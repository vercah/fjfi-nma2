#include "ThomasAlgorithm.h"

ThomasAlgorithm::ThomasAlgorithm( TridiagonalMatrix& A,
                                  Vector& b )
: A( A ), b( b ), rho( b.getSize() ), mu( b.getSize() )
{
}
      
bool ThomasAlgorithm::solve( Vector& x, int verbose )
{
   /****
    * First phase: Eliminate elements under diagonal
    */
   const int n = A.getColumns();
   mu[ 0 ] = A( 0, 1 ) / A( 0, 0 );
   rho[ 0 ] = b[ 0 ] / A( 0, 0 );
   for( int k = 1; k < n; k++ )
   {
      rho[ k ] = ( b[ k ] - A( k, k - 1 ) * rho[ k - 1 ] ) / ( A( k, k ) - A( k, k - 1 ) * mu[ k - 1 ] );
      if( k < n - 1 )
         mu[ k ] = A( k, k + 1) / ( A( k, k ) - A( k, k - 1 ) * mu[ k - 1 ] );
   }
   if( verbose )
      this->print( std::cout );
   
   /****
    * Second phase: Backward substitution
    */
   x[ n - 1 ] = rho[ n - 1 ];
   for( int k = n - 2; k >= 0; k-- )
      x[ k ] = rho[ k ] - mu[ k ] * x[ k + 1 ];
   
}
      
void ThomasAlgorithm::print( std::ostream& str ) const
{
   
}
