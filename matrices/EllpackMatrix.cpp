/* 
 * File:   EllpackMatrix.cpp
 * Author: oberhuber
 *
 * Created on October 26, 2016, 3:36 PM
 */

#include <string>
#include <sstream>
#include <iomanip>
#include <assert.h>
#include "EllpackMatrix.h"

EllpackMatrix::EllpackMatrix()
: Matrix( 0 ,0 )
{
}
EllpackMatrix::EllpackMatrix( const int rows, const int columns )
: Matrix( rows, columns ), row_width( 5 )
{
   this->allocate();
}
      
bool EllpackMatrix::setDimensions( const int rows, const int columns )
{
   this->rows = rows;
   this->columns = columns;
   return this->allocate();
}

bool EllpackMatrix::setRowWidth( const int row_width )
{
   this->row_width = row_width;
   return this->allocate();
}

bool EllpackMatrix::setElement( const int row, const int column, const Real& value )
{
   int ptr = row * row_width;
   int row_end = ptr + row_width;
   while( ptr < row_end && 
          this->columns[ ptr ] < column &&
          this->columns[ ptr ] != -1 ) ptr++;
   if( ptr == row_end )
      return false;
   if( this->columns[ ptr ] == column )
   {
      this->elements[ ptr ] = value;
      return false;
   }
   if( this->columns[ ptr ] != -1 )
   {
      int aux = row_end - 1;
      if( this->columns[ aux ] == -1 )
         return false;
      while( aux > ptr )
      {
         this->columns[ aux ] = this->columns[ aux - 1 ];
         this->elements[ aux ] = this->elements[ aux - 1 ];
      }
   }
   this->columns[ ptr ] = column;
   this->elements[ ptr ] = value;
}


Real& EllpackMatrix::operator()( const int row, const int column )
{
   int ptr = row * row_width;
   int row_end = ptr + row_width;
   while( ptr < row_end && 
          this->columns[ ptr ] < column &&
          this->columns[ ptr ] != -1 ) ptr++;
   return this->elements[ ptr ];
}
      
const Real& EllpackMatrix::operator()( const int row, const int column ) const
{
   int ptr = row * row_width;
   const int row_end = ptr + row_width;
   while( ptr < row_end && 
          this->columns[ ptr ] < column &&
          this->columns[ ptr ] != -1 ) ptr++;
   return this->elements[ ptr ];
}

void EllpackMatrix::vectorMultiplication( const Vector& in_vector,
                                        Vector& out_vector ) const
{
   assert( in_vector.getSize() == this->columns );
   assert( out_vector.getSize() == this->rows );
   
   for( int row = 0; row < this->rows; row++ )
   {
      Real result( 0.0 );
      int ptr = row * row_width;
      int column;
      const int row_end = ptr + row_width;
      while( ptr < row_end && ( column = this->columns[ ptr ] ) != -1 )
         result += this->elements[ ptr++ ] * in_vector[ column ];
      out_vector[ row ] = result;
   }
}

void EllpackMatrix::performJacobiIteration( const Vector& b,
                                            const Vector& x,
                                            Vector& aux ) const
{
   assert( x.getSize() == this->columns );
   assert( b.getSize() == this->columns );
   assert( this->columns == this->rows );
   
   for( int row = 0; row < this->rows; row++ )
   {
      Real sum( 0.0 ), a_ii( 0.0 );
      int ptr = row * row_width;
      int column;
      const int row_end = ptr + row_width;
      while( ptr < row_end && ( column = this->columns[ ptr ] ) != -1 )
      {
         if( column == row )
            a_ii = this->elements[ ptr++ ];
         else 
            sum += this->elements[ ptr++ ] * x[ column ];
      }
      if( a_ii == 0.0 )
      {
         std::cerr << "a_ii = 0 for i = " << row << ", unable to continue." << std::endl;
         abort();
      }      
      aux[ row ]= 1.0 / a_ii * ( b[ row ] - sum );
   }
}

EllpackMatrix& EllpackMatrix::operator=( const EllpackMatrix& m )
{
   this->setDimensions( m.getRows(), m.getColumns() );
   this->setRowWidth( m.row_width );
   this->elements = m.elements;
   this->columns = m.columns;
}

EllpackMatrix& EllpackMatrix::operator-=( const EllpackMatrix& m )
{
   for( int i = 0; i < this->elements.size(); i++ )
      this->elements[ i ] -= m.elements[ i ];
}

bool EllpackMatrix::allocate()
{
   this->elements.resize( this->rows * row_width );
   this->columns.resize( this->rows * row_width );
   for( int i = 0; i < this->columns.size(); i++ )
      this->columns[ i ] = -1;
}
