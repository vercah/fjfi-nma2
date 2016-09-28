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
#include "DenseMatrix.h"

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
}
   
Real& DenseMatrix::operator()( const int row, const int column )
{
   return this->elements[ row * this->columns + column ];
}
      
const Real& DenseMatrix::operator()( const int row, const int column ) const
{
   return this->elements[ row * this->columns + column ];
}

bool DenseMatrix::readMtxFile( std::istream& str )
{
   std::string line;
   std::stringstream iss( line );
   std::string matrixType;
   
   if( std::getline( str,line ) )
   {
      std::string header1, header2, format, numberType;
      if( std::getline( iss, header1, ' ' ) && 
          std::getline( iss, header2, ' ' ) &&
          std::getline( iss, format, ' ')   &&
          std::getline( iss, numberType, ' ' ) &&
          std::getline( iss, matrixType, '' ) )
      {
         if( header1 != "%%MatrixMarket" ||
             header2 != "matrix" )
         {
            std::cerr << "Wrong MTX file header." << std::endl;
            return false;
         }
         if( format != "coordinate" )
         {
            std::cerr << "Only coordinate MTX file format is allowed." << std::endl;
            return false;
         }
         if( numberType != "real" )
         {
            std::cerr << "Only real numbers are allowed." << std::endl;
            return false;
         }
         if( matrixType != "general" && matrixType != "symmetric" )
         {
            std::cerr << "Only general and symmetric matrices are supported." << std::endl;
            return false;
         }
      }
      else
      {
         std::cerr << "Cannot read the MTX file header." << std::endl;
         return false;                
      }
   }
   bool dimensionsFlag( false );
   while( std::getline( str, line ) )
   {
      if( line[ 0 ] == '%' )
         continue;
      if( ! dimensionsFlag )
      {
         std::string rows, columns;
         if( std::getline( iss, rows, ' ' ) &&
             std::getline( iss, columns, ' ' ) )
         {
            if( ! this->setDimensions( std::stoi( rows ), std::stoi( columns ) ) )
               return false;
            dimensionsFlag = true;
            continue;
         }
         else
         {
            std::cerr << "Cannot read matrix dimensions." << std::endl;
            return false;
         }
      }
      std::string str_row, str_column, str_value;
      if( std::getline( iss, str_row, ' ' ) &&
          std::getline( iss, str_column, ' ' ) &&
          std::getline( iss, str_value ) )
      {
         int row = std::stoi( str_row ) - 1;
         int column = std::stoi( str_column ) - 1;
         Real value = std::stof( str_value );
         ( *this )( row, column, value );
         if( matrixType == "symmetric" && row != column )
            ( *this )( column, row, value );
      }      
   }      
}
      
void DenseMatrix::print( std::ostream& str )
{
   for( int column = 0; column < this->columns; column++ )
   {
      for( int row = 0; row < this->rows; row++ )
         str << ( *this )( row, column ) << " ";
      str << std::endl;
   }
}

