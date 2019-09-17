#include "LUDecomposition.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <math.h>

#include "LUDecomposition.h"

LUDecomposition::LUDecomposition( DenseMatrix& A )
: A( A )
{
}

bool LUDecomposition::solve( Vector& b, int verbose )
{
   const int n = A.getRows();

   if( verbose )
      this->print();

   /****
    * Forward substitution
    */
   for( int k = 0; k < n; k++ )
   {
      for( int j = 0; j < k; j++ )
         b[ k ] -= b[ j ] * A( k, j );
      if( A( k, k ) == 0.0 )
         return false;
      b[ k ] /= A( k, k );
   }

   /****
    * Backward substitution
    */
   for( int k = n - 1; k >= 0; k-- )
   {
      //x[ k ] = b[ k ];
      for( int j = k + 1; j < n; j++ )
         b[ k ] -= b[ j ] * A( k, j );
   }
   return true;
}


bool LUDecomposition::computeByGEM( int verbose )
{
   const int n = A.getRows();

   if( verbose )
      this->print();

   for( int k = 0; k < n; k++ )
   {
      /****
       * Divide the k-th row by pivot
       */
      const Real& pivot = A( k, k );
      if( pivot == 0.0 )
         return false;

      for( int j = k+1; j < n; j++ )
         A( k, j ) /= pivot;
      //A( k, k ) = 1.0;

      if( verbose > 1 )
      {
         std::cout << "Dividing by the pivot ... " << std::endl;
         this->print();
      }

      /****
       * Subtract the k-th row from the rows bellow
       */
      for( int i = k+1; i < n; i++ )
      {
         for( int j = k+1; j < n; j++ )
            A( i, j ) -= A( i, k ) * A( k, j );
         //A( i, k ) = 0.0;
      }

      if( verbose > 1 )
      {
         std::cout << "Subtracting the " << k << "-th row from the rows bellow ... " << std::endl;
         this->print();
      }
   }
   return true;
}

bool LUDecomposition::computeByCrout( int verbose )
{
   const int n = A.getRows();

   for( int step = 0; step < n; step++ )
   {
      /****
       * Compute j-th column of matrix L
       */
      for( int i = step; i < n; i++ )
      {
         Real aux( 0.0 );
         for( int k = 0; k < step; k++ )
            aux += A( i, k ) * A( k, step );
         A( i, step ) -=  aux;
      }
      if( verbose > 1 )
         std::cout << "Computing the " << step << "-th column of L:" << std::endl << A << std::endl;

      /****
       * Compute i-th row of matrix U (except diagonal part)
       */
      for( int j = step + 1; j < n; j++ )
      {
         Real aux( 0.0 );
         for( int k = 0; k < step; k++ )
            aux += A( step, k ) * A( k, j );
         A( step, j ) -=  aux;
         if( A( step, step ) == 0.0 )
            return false;
         A( step, j ) /= A( step, step );
      }
      if( verbose > 1 )
         std::cout << "Computing the " << step << "-th row of U:" << std::endl << A << std::endl;
   }
   return true;
}

bool LUDecomposition::computeByDoolitle( int verbose )
{
   const int n = A.getRows();

   for( int step = 0; step < n; step++ )
   {
      /****
       * Compute i-th row of matrix U (except diagonal part)
       */
      for( int j = step; j < n; j++ )
      {
         Real aux( 0.0 );
         for( int k = 0; k < step; k++ )
            aux += A( step, k ) * A( k, j );
         A( step, j ) -=  aux;
      }
      if( verbose > 1 )
         std::cout << "Computing the " << step << "-th row of U:" << std::endl << A << std::endl;

      /****
       * Compute j-th column of matrix L
       */
      for( int i = step + 1; i < n; i++ )
      {
         Real aux( 0.0 );
         for( int k = 0; k < step; k++ )
            aux += A( i, k ) * A( k, step );
         A( i, step ) -=  aux;
         if( A( i, i ) == 0.0 )
            return false;
         A( i, step ) /= A( step, step );
      }
      if( verbose > 1 )
         std::cout << "Computing the " << step << "-th column of L:" << std::endl << A << std::endl;
   }
   return true;
}


void LUDecomposition::restoreMatrix( DenseMatrix& B, bool ones_on_U )
{
   assert( B.getColumns() == A.getColumns() );
   assert( B.getRows() ==  A.getRows() );
   const int n = A.getColumns();

   if( ones_on_U )
      for( int i = 0; i < n; i++ )
         for( int j = 0; j < n; j++ )
         {
            Real aux( 0.0 );
            for( int k = 0; k <= std::min( i, j ); k++ )
               if( k == j )  // There are ones on the diagonal of U
                  aux += A( i, k );
               else
                  aux += A( i, k ) * A( k, j );
            B( i, j ) = aux;
         }
   else
      for( int i = 0; i < n; i++ )
         for( int j = 0; j < n; j++ )
         {
            Real aux( 0.0 );
            for( int k = 0; k <= std::min( i, j ); k++ )
               if( k == i )  // There are ones on the diagonal of L
                  aux += A( k, j );
               else
                  aux += A( i, k ) * A( k, j );
            B( i, j ) = aux;
         }
}

void LUDecomposition::getError( DenseMatrix& A, double& max_error, bool ones_on_L )
{
   assert( A.getRows() == A.getColumns() );
   const int size = A.getRows();
   DenseMatrix m( size, size );
   this->restoreMatrix( m, ones_on_L );
   m -= A;
   max_error = m.maxNorm();
}

void LUDecomposition::print( std::ostream& str ) const
{
   const int n = this->A.getRows();
   const int precision( 18 );
   const std::string zero( "." );
   for( int row = 0; row < n; row++ )
   {
      str << "| ";
      for( int column = 0; column < n; column++ )
      {
         const double& value = A( row, column );
         if( value == 0.0 )
            str << std::setw( precision + 6 ) << zero;
         else str<< std::setprecision( precision ) << std::setw( precision + 6 )  << value;
      }
      str << " | " << std::endl;
   }
}