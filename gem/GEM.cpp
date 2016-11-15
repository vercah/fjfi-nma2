/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GEM.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <math.h>

GEM::GEM( DenseMatrix& A,
          Vector& b )
: A( A ), b( b )
{  
   assert( A.getRows() == b.getSize() &&
           A.getColumns() == b.getSize() );
}
      
bool GEM::solve( Vector& x, int verbose )
{
   assert( b.getSize() == x.getSize() );
   
   const int n = A.getRows();

   if( verbose )
      this->print();

   for( int k = 0; k < n; k++ )
   {
      /****
       * Divide the k-th row by pivot
       */
      if( k % 10 == 0 )
         std::cout << "Elimination: " << k << "/" << n << std::endl;
      const Real& pivot = A( k, k );
      if( pivot == 0.0 )
      {
         std::cerr << "Zero pivot has appeared in " << k << "-th step. GEM has failed." << std::endl;
         return false;
      }
      b[ k ] /= pivot;
      for( int j = k+1; j < n; j++ )
         A( k, j ) /= pivot;
      A( k, k ) = 1.0;
      
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
         b[ i ] -= A( i, k ) * b[ k ];
         A( i, k ) = 0.0;
      }

      if( verbose > 1 )
      {
         std::cout << "Subtracting the " << k << "-th row from the rows bellow ... " << std::endl;
         this->print();
      }
   }
   
   /****
    * Backward substitution
    */
   for( int k = n - 1; k >= 0; k-- )
   {
      //if( k % 10 == 0 )
      //   std::cout << "Substitution: " << k << "/" << n << std::endl;
      x[ k ] = b[ k ];
      for( int j = k + 1; j < n; j++ )
         x[ k ] -= x[ j ] * A( k, j );         
   }   
}

bool GEM::solveWithPivoting( Vector& x, int verbose )
{
   assert( b.getSize() == x.getSize() );
   
   const int n = A.getRows();

   if( verbose )
      this->print();

   for( int k = 0; k < n; k++ )
   {
      std::cout << "Step " << k << "/" << n << ".... \r";
      /****
       * Find the pivot - the largest in k-th row
       */
      int pivotPosition( k );
      for( int i = k + 1; i < n; i++ )
         if( fabs( A( i, k ) > fabs( A( pivotPosition, k ) ) ) )
            pivotPosition = i;
         
      /****
       * Swap the rows ...
       */
      if( pivotPosition != k )
      {
         for( int j = k; j < n; j++ )
            std::swap( A( k, j ), A( pivotPosition, j ) );
         std::swap( b[ k ], b[ pivotPosition ] );
      }
      
      if( verbose > 1 )
      {
         std::cout << std::endl;
         std::cout << "Choosing element at " << pivotPosition << "-th row as pivot..." << std::endl;
         std::cout << "Swaping " << k << "-th and " << pivotPosition <<  "-th rows ... " << std::endl;
      }
            
      /****
       * Divide the k-th row by pivot
       */
      const Real& pivot = A( k, k );
      if( pivot == 0.0 )
      {
         std::cerr << "Zero pivot has appeared in " << k << "-th step. GEM has failed." << std::endl;
         return false;
      }      
      b[ k ] /= pivot;
      for( int j = k+1; j < n; j++ )
         A( k, j ) /= pivot;
      A( k, k ) = 1.0;
      
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
         b[ i ] -= A( i, k ) * b[ k ];
         A( i, k ) = 0.0;
      }

      if( verbose > 1 )
      {
         std::cout << "Subtracting the " << k << "-th row from the rows bellow ... " << std::endl;
         this->print();
      }
   }
   
   /****
    * Backward substitution
    */
   for( int k = n - 1; k >= 0; k-- )
   {
      x[ k ] = b[ k ];
      for( int j = k + 1; j < n; j++ )
         x[ k ] -= x[ j ] * A( k, j );         
   }   
}

bool GEM::computeLUDecomposition( int verbose )
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
      b[ k ] /= pivot;
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
         b[ i ] -= A( i, k ) * b[ k ];
         //A( i, k ) = 0.0;
      }

      if( verbose > 1 )
      {
         std::cout << "Subtracting the " << k << "-th row from the rows bellow ... " << std::endl;
         this->print();
      }
   }   
}

void GEM::print( std::ostream& str ) const
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
      str << " | " << std::setprecision( precision ) << std::setw( precision + 6 ) << b[ row ] << " |" << std::endl;
   }
}