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
   
bool TridiagonalMatrix::setElement( const int row, const int column, const Real& value )
{
   if( abs( column - row ) > 1 )
   {
      std::cerr << "Accesing wrong element ( " << row << " column " << column << " ) in tridiagonal matrix. " << std::endl;
      return false;
   }
   this->elements[ 2 * row + column ] = value;
   return true;
}
      
Real TridiagonalMatrix::getElement( const int row, const int column ) const
{
   if( abs( column - row ) > 1 )
      return 0.0;
   return this->elements[ 2 * row + column ];   
}

Real& TridiagonalMatrix::operator()( const int row, const int column )
{
   if( abs( column - row ) > 1 )
   {
      std::cerr << "Accesing wrong element ( " << row << " column " << column << " ) in tridiagonal matrix. " << std::endl;
      throw( 0 );
   }
   return this->elements[ 2 * row + column ];   
}
      
const Real& TridiagonalMatrix::operator()( const int row, const int column ) const
{
   if( abs( column - row ) > 1 )
   {
      std::cerr << "Accesing wrong element ( " << row << " column " << column << " ) in tridiagonal matrix. " << std::endl;
      throw( 0 );
   }   
   return this->elements[ 2 * row + column ];   
}

void TridiagonalMatrix::vectorMultiplication( const Vector& in_vector,
                                              Vector& out_vector ) const
{
   assert( in_vector.getSize() == this->columns );
   assert( out_vector.getSize() == this->rows );
   
   for( int i = 0; i < this->rows; i++ )
   {
      Real sum( 0.0 );
      if( i > 0 )
         sum += in_vector[ i - 1 ] * this->getElement( i, i - 1 );
      sum += in_vector[ i ] * this->getElement( i, i );
      if( i < this->columns - 1 )
         sum += in_vector[ i + 1 ] * this->getElement( i, i + 1 );      
      out_vector[ i ] = sum;
   }
      
}

TridiagonalMatrix& TridiagonalMatrix::operator=( const TridiagonalMatrix& m )
{
   this->setDimensions( m.getRows(), m.getColumns() );
   this->elements = m.elements;
}