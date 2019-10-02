#include <assert.h>
#include <math.h>
#include "HouseholderTransformation.h"

HouseholderTransformation::HouseholderTransformation( int size )
: size( size )
{
}

bool HouseholderTransformation::init( DenseMatrix& matrix, int row, int column )
{
   assert( matrix.getRows() == size );
   assert( matrix.getColumns() == size );
   assert( row < size );
   assert( column < size );

   w.setSize( size - row );
   for( int i = row; i < size; i++ )
      w[ i - row ] = matrix( i, column );

   this->x1_sign = w[ 0 ] < 0.0 ? -1.0 : 1.0;
   this->x_norm = w.l2Norm();
   w[ 0 ] -= this->x1_sign * this->x_norm;
   //std::cout << "w -> " << w << std::endl;
   const double w_norm = w.l2Norm();
   if( ! w_norm )
      return false;
   w *= 1.0 / w_norm;
   return true;
}

void HouseholderTransformation::applyFromLeft( DenseMatrix& A )
{
   /*Vector A_T_w( w.getSize() );
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
      for( int j = row; j < size; j++ )
         A( i, j ) -= 2.0 * w[ i - row  ] * A_T_w[ j - row ];
    */
   Vector A_T_w( size );
   const int row = size - w.getSize();
   for( int i = 0; i < size; i++ )
   {
      double aux( 0.0 );
      for( int j = row; j < size; j++ )
         aux += A( j, i ) * w[ j - row ];
      A_T_w[ i ] = aux;
   }
   //std::cout << "A_T_w = " << A_T_w << std::endl;
   for( int i = row; i < size; i++ )
      for( int j = 0; j < size; j++ )
         A( i, j ) -= 2.0 * w[ i - row  ] * A_T_w[ j ];
}

void HouseholderTransformation::applyFromRight( DenseMatrix& A )
{
   Vector A_w( size );
   const int row = size - w.getSize();
   for( int i = 0; i < size; i++ )
   {
      double aux( 0.0 );
      for( int j = row; j < size; j++ )
         aux += A( i, j ) * w[ j - row ];
      A_w[ i ] = aux;
   }
   //std::cout << "A_T_w = " << A_T_w << std::endl;
   for( int i = 0; i < size; i++ )
      for( int j = row; j < size; j++ )
         A( i, j ) -= 2.0 * w[ j - row  ] * A_w[ i ];
}

bool HouseholderTransformation::computeQR( DenseMatrix& A, DenseMatrix& Q )
{
   const int size = A.getRows();
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j ? 1.0 : 0.0 );

   for( int i = 0; i < size - 1; i++ )
   {
      if( ! this->init( A, i, i ) )
         return false;
      this->applyFromLeft( A );
      //std::cout << "A = " << std::endl << A << std::endl;
      this->applyFromRight( Q );
      //std::cout << "Q = " << std::endl << Q << std::endl;
   }
   return true;
}

bool HouseholderTransformation::computeHessenbergForm( DenseMatrix& A, DenseMatrix& Q )
{
   const int size = A.getRows();
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j ? 1.0 : 0.0 );

   DenseMatrix m( size, size );
   m = A;
   for( int i = 0; i < size - 2; i++ )
   {
      if( ! this->init( A, i + 1, i ) )
         return false;
      std::cout << "w = " << w << std::endl;
      this->applyFromLeft( A );
      this->applyFromRight( A );
      std::cout << "A = " << std::endl << A << std::endl;
      this->applyFromLeft( Q );
      std::cout << "Q = " << std::endl << Q << std::endl;
      double err;
      checkHessenbergForm( A, Q, m, err );
      std::cout << "Max.err.= " << err << std::endl;
      std::cout << "Q orthogonality: " << Q.checkOrthogonality() << std::endl;
      std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
   }
   return true;
}

void HouseholderTransformation::checkHessenbergForm( DenseMatrix& H, DenseMatrix& Q, DenseMatrix& A, double& max_error )
{
   assert( H.getRows() == H.getColumns() );
   assert( H.getRows() == Q.getRows() );
   assert( H.getColumns() == Q.getColumns() );
   assert( H.getRows() == A.getRows() );
   assert( H.getColumns() == A.getColumns() );

   const int n = H.getRows();
   DenseMatrix M1( n, n ), M2( n, n );
   M1.matrixMultiplication( Q, H );
   M2.matrixMultiplication( M1, Q );
   M2 -= A;
   std::cout << "Err. = " << std::endl << M2 << std::endl;
   max_error = M2.maxNorm();
}