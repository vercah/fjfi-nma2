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
#include <set>
#include "../string-split.h"
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

bool EllpackMatrix::setRowLength( const int row_width )
{
   this->row_width = row_width;
   return this->allocate();
}

bool EllpackMatrix::setElement( const int row, const int column, const Real& value )
{
   int ptr = row * row_width;
   int row_end = ptr + row_width;
   while( ptr < row_end && 
          this->column_indexes[ ptr ] != column &&
          this->column_indexes[ ptr ] != -1 ) ptr++;
   if( ptr == row_end )
      return false;
   if( this->column_indexes[ ptr ] == column )
   {
      this->elements[ ptr ] = value;
      return true;
   }
   /*if( this->column_indexes[ ptr ] != -1 )
   {
      int aux = row_end - 1;
      if( this->column_indexes[ aux ] != -1 )
         return false;
      while( aux > ptr )
      {
         this->column_indexes[ aux ] = this->column_indexes[ aux - 1 ];
         this->elements[ aux ] = this->elements[ aux - 1 ];
      }
   }*/
   this->column_indexes[ ptr ] = column;
   this->elements[ ptr ] = value;
   return true;
}
      
Real EllpackMatrix::getElement( const int row, const int column ) const
{
   int ptr = row * row_width;
   const int row_end = ptr + row_width;
   while( ptr < row_end && 
          this->column_indexes[ ptr ] != column &&
          this->column_indexes[ ptr ] != -1 ) ptr++;
   if( ptr == row_end )
      return 0.0;   
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
      while( ptr < row_end && ( column = this->column_indexes[ ptr ] ) != -1 )
         result += this->elements[ ptr++ ] * in_vector[ column ];
      out_vector[ row ] = result;
   }
}

void EllpackMatrix::performRichardsonIteration( const Vector& b,
                                                const Vector& x,
                                                Vector& aux,
                                                const Real& relaxation ) const
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
      while( ptr < row_end && ( column = this->column_indexes[ ptr ] ) != -1 )
            sum += this->elements[ ptr++ ] * x[ column ];
      aux[ row ]= x[ row ] + relaxation * ( b[ row ] - sum );
   }   
}

void EllpackMatrix::performJacobiIteration( const Vector& b,
                                            const Vector& x,
                                            Vector& aux,
                                            const Real& relaxation ) const
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
      while( ptr < row_end && ( column = this->column_indexes[ ptr ] ) != -1 )
      {
         if( column == row )
            a_ii = this->elements[ ptr ];
         sum += this->elements[ ptr++ ] * x[ column ];
      }
      if( a_ii == 0.0 )
      {
         std::cerr << "a_ii = 0 for i = " << row << ", unable to continue." << std::endl;
         abort();
      }      
      aux[ row ]= x[ row ] + relaxation * ( b[ row ] - sum ) / a_ii;
   }
}

void EllpackMatrix::performSORIteration( const Vector& b,
                                         Vector& x,
                                         const Real& relaxation ) const
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
      while( ptr < row_end && ( column = this->column_indexes[ ptr ] ) != -1 )
      {
         if( column == row )
            a_ii = this->elements[ ptr ];
         sum += this->elements[ ptr++ ] * x[ column ];
      }
      if( a_ii == 0.0 )
      {
         std::cerr << "a_ii = 0 for i = " << row << ", unable to continue." << std::endl;
         abort();
      }
      x[ row ] += relaxation * ( b[ row ] - sum ) / a_ii;
   }   
}

void EllpackMatrix::getResidue( const Vector& x, const Vector& b, Vector& r ) const
{
   
}

EllpackMatrix& EllpackMatrix::operator=( const EllpackMatrix& m )
{
   this->setDimensions( m.getRows(), m.getColumns() );
   this->setRowLength( m.row_width );
   this->elements = m.elements;
   this->column_indexes = m.column_indexes;
}

EllpackMatrix& EllpackMatrix::operator-=( const EllpackMatrix& m )
{
   for( int i = 0; i < this->elements.size(); i++ )
      this->elements[ i ] -= m.elements[ i ];
}

bool EllpackMatrix::readMtxFile( std::istream& str )
{
   std::string line;
   std::string matrixType;
   std::vector< std::string > parsedLine;
   
   if( std::getline( str,line ) )
   {
      string_split( line, ' ', parsedLine );
      if( parsedLine.size() != 5 )
      {
         std::cerr << "Cannot read the MTX file header." << std::endl;
         return false;                
      }
      
      if( parsedLine[ 0 ] != "%%MatrixMarket" ||
          parsedLine[ 1 ] != "matrix" )
      {
         std::cerr << "Wrong MTX file header." << std::endl;
         return false;
      }
      if( parsedLine[ 2 ] != "coordinate" )
      {
         std::cerr << "Only coordinate MTX file format is allowed." << std::endl;
         return false;
      }
      if( parsedLine[ 3 ] != "real" )
      {
         std::cerr << "Only real numbers are allowed." << std::endl;
         return false;
      }
      matrixType = parsedLine[ 4 ];
      if( matrixType != "general" && matrixType != "symmetric" )
      {
         std::cerr << "Only general and symmetric matrices are supported." << std::endl;
         return false;
      }
   }
   bool dimensionsFlag( false );
   long int lineNumber( 1 );
   typedef std::pair< int, int > Coordinates;
   std::vector< int > row_lengths;
   
   std::set< std::pair< Coordinates, Real > > matrix_elements;
   int matrix_rows, matrix_columns;
   while( std::getline( str, line ) )
   {
      lineNumber++;
      if( line[ 0 ] == '%' )
         continue;
      
      string_split( line, ' ', parsedLine );         
      if( ! dimensionsFlag )
      {
         if( parsedLine.size() < 3 )
         {
            std::cerr << "Cannot read matrix dimensions." << std::endl;
            return false;
         }            
         const std::string& str_rows = parsedLine[ 0 ];
         const std::string& str_columns = parsedLine[ 1 ];
         matrix_rows = std::stoi( str_rows );
         matrix_columns = std::stoi( str_columns );
         row_lengths.resize( matrix_rows, 0 );
         dimensionsFlag = true;
      }
      else
      {
         if( parsedLine.size() < 3 )
         {
            std::cerr << "Error at line " << lineNumber << "." << std::endl;
            return false;
         }
         const std::string& str_row = parsedLine[ 0 ];
         const std::string& str_column = parsedLine[ 1 ];
         const std::string& str_value = parsedLine[ 2 ];

         int row = std::stoi( str_row ) - 1;
         int column = std::stoi( str_column ) - 1;
         Real value = std::stod( str_value );
         row_lengths[ row ]++;
         matrix_elements.insert( std::pair< Coordinates, Real >( Coordinates( row, column ), value) );
         if( matrixType == "symmetric" && row != column )
            row_lengths[ column ]++;
      }
   }
   int max_row_length( 0 );
   for( int i = 0; i < matrix_rows; i++ )
      max_row_length = std::max( max_row_length, row_lengths[ i ] );
   this->row_width = max_row_length;
   if( ! this->setDimensions( matrix_rows, matrix_columns ) )
   {
      std::cerr << "Unable to set dimensions " << rows << " x " << columns << "." << std::endl;
      return false;
   }
   typename std::set< std::pair< Coordinates, Real > >::iterator it = matrix_elements.begin();
   while( it != matrix_elements.end() )
   {
      //std::cerr << "setting " << it->first.first << " , " << it->first.second << " = " << it->second << std::endl;
      //this->printRow( it->first.first );
      if( ! this->setElement( it->first.first, it->first.second, it->second ) )
      {
         std::cerr << "Unable to set matrix element." << std::endl;
         return false;
      }
      //this->printRow( it->first.first );
      if( matrixType == "symmetric" && it->first.first != it->first.second )
      {
         //std::cerr << "setting " << it->first.second << " , " << it->first.first << " = " << it->second << std::endl;
         //this->printRow( it->first.second );
         if( ! this->setElement( it->first.second, it->first.first, it->second ) )
         {
            std::cerr << "Unable to set matrix element." << std::endl;
            return false;
         }            
         //this->printRow( it->first.second );
      }
      it++;
   }
   return true;
}

bool EllpackMatrix::allocate()
{
   this->elements.resize( this->rows * row_width );
   this->column_indexes.resize( this->rows * row_width );
   for( int i = 0; i < this->column_indexes.size(); i++ )
      this->column_indexes[ i ] = -1;
   return true;
}

void EllpackMatrix::printRow( const int row )
{
   int i = row * this->row_width;
   const int row_end = i + this->row_width;
   while( i < row_end )
   {
      std::cout << i << ":" << this->column_indexes[ i ] << "->" << this->elements[ i ] << " ";
      i++;
   }
   std::cout << std::endl;
}
