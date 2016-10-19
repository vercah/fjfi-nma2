/* 
 * File:   denseMatrix.cpp
 * Author: oberhuber
 * 
 * Created on September 28, 2016, 5:31 PM
 */

#include <string>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "TridiagonalMatrix.h"
#include "../string-split.h"

TridiagonalMatrix::TridiagonalMatrix()
{
}
TridiagonalMatrix::TridiagonalMatrix( const int rows, const int columns )
: Matrix( rows, columns )
{
   this->elements.resize( 3 * std::min( rows, columns ) );
}
      
bool TridiagonalMatrix::setDimensions( const int rows, const int columns )
{
   this->rows = rows;
   this->columns = columns;
   this->elements.resize( 3 * std::min( rows, columns ) );
   return true;
}
   
Real& TridiagonalMatrix::operator()( const int row, const int column )
{
   return this->elements[ 3 * row + column ];
}
      
const Real& TridiagonalMatrix::operator()( const int row, const int column ) const
{
   return this->elements[ 3 * row + column ];
}

void TridiagonalMatrix::vectorMultiplication( const Vector& in_vector,
                                        Vector& out_vector ) const
{
   assert( in_vector.getSize() == this->columns );
   assert( out_vector.getSize() == this->rows );
   
   out_vector[ 0 ] = ( *this )( 0, 0 ) * in_vector[ 0 ] + ( *this )( 0, 1 ) * in_vector[ 1 ];      
   for( int row = 1; row < std::min( this->rows, this->columns ) - 1; row++ )
   {
      Real result( 0.0 );
      for( int column = row - 1; column < row + 1; column++ )
         result += ( *this )( row, column ) * in_vector[ column ];
      out_vector[ row ]= result;
   }
   const int n = this->getRows();
   out_vector[ n - 1 ] = ( *this )( n - 1, n - 2 ) * in_vector[ n - 2 ] +
                         ( *this )( n - 1, n - 1 ) * in_vector[ n - 1 ];
   if( this->getColumns() >  n )
      out_vector[ n - 1 ] += ( *this )( n - 1, n ) * in_vector[ n ];
 }

TridiagonalMatrix& TridiagonalMatrix::operator=( const TridiagonalMatrix& m )
{
   this->setDimensions( m.getRows(), m.getColumns() );
   this->elements = m.elements;
}