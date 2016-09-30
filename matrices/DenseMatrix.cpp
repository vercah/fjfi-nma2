/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
#include "DenseMatrix.h"
#include "../string-split.h"

DenseMatrix::DenseMatrix()
: rows( 0 ), columns( 0 )
{
}
DenseMatrix::DenseMatrix( const int rows, const int columns )
: rows( rows ), columns( columns )
{
   this->elements.resize( rows * columns );
}
      
bool DenseMatrix::setDimensions( const int rows, const int columns )
{
   this->rows = rows;
   this->columns = columns;
   this->elements.resize( rows * columns );
   return true;
}

int DenseMatrix::getRows() const
{
   return this->rows;
}
      
int DenseMatrix::getColumns() const
{
   return this->columns;
}
   
Real& DenseMatrix::operator()( const int row, const int column )
{
   return this->elements[ row * this->columns + column ];
}
      
const Real& DenseMatrix::operator()( const int row, const int column ) const
{
   return this->elements[ row * this->columns + column ];
}

void DenseMatrix::vectorMultiplication( const std::vector< Real >& in_vector,
                                        std::vector< Real >& out_vector ) const
{
   assert( in_vector.size() == this->columns );
   assert( out_vector.size() == this->rows );
   
   for( int row = 0; row < this->rows; row++ )
   {
      Real result( 0.0 );
      for( int column = 0; column < this->columns; column++ )
         result += ( *this )( row, column ) * in_vector[ column ];
      out_vector[ row ]= result;
   }
}

bool DenseMatrix::readMtxFile( std::istream& str )
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
         const int rows = std::stoi( str_rows );
         const int columns = std::stoi( str_columns );
         if( ! this->setDimensions( rows, columns ) )
         {
            std::cerr << "Unable to set dimensions " << rows << " x " << columns << "." << std::endl;
            return false;
         }
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
         ( *this )( row, column ) =  value;
         if( matrixType == "symmetric" && row != column )
            ( *this )( column, row ) = value;
      }
   }
   return true;
}
      
void DenseMatrix::print( std::ostream& str,
                         const int precision,
                         const std::string zero )
{
   for( int column = 0; column < this->columns; column++ )
   {
      for( int row = 0; row < this->rows; row++ )
      {
         const double& value = ( *this )( row, column );
         if( value == 0.0 )
            str << std::setw( precision + 6 ) << zero;
         else str<< std::setprecision( precision ) << std::setw( precision + 6 )  << value;
      }
      str << std::endl;
   }
}

