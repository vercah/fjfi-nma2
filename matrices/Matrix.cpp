#include <iomanip>
#include "Matrix.h"
#include "../string-split.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

Matrix::Matrix()
: rows( 0 ), columns( 0 )
{
}

Matrix::Matrix( const int rows, const int columns )
: rows( rows ), columns( columns )
{
}

int Matrix::getRows() const
{
   return this->rows;
}
      
int Matrix::getColumns() const
{
   return this->columns;
}

Real Matrix::maxNorm() const
{
   Real maxRow( 0.0 ), currentRow( 0.0 );
   for( int k = 0; k < this->getRows(); k++ )
   {
      for( int j = 0; j < this->getColumns(); j++ )
         currentRow += std::fabs( this->getElement( k, j ) );
      if( currentRow > maxRow )
         maxRow = currentRow;
   }
   return maxRow;
}

void Matrix::getEigenvalueResidue( const Vector& eigenvector,
                                   const Real& eigenvalue,
                                   Vector& residue ) const
{
   residue.setSize( eigenvector.getSize() );
   this->vectorMultiplication( eigenvector, residue );
   for( int i = 0; i < eigenvector.getSize(); i++ )
      residue[ i ] -= eigenvalue * eigenvector[ i ];
}


void Matrix::print( std::ostream& str,
                    const int precision,
                    const std::string zero ) const
{
   for( int row = 0; row < this->rows; row++ )
   {
      for( int column = 0; column < this->columns; column++ )
      {
         const double& value = this->getElement( row, column );
         if( value == 0.0 )
            str << std::setw( precision + 6 ) << zero;
         else str<< std::setprecision( precision ) << std::setw( precision + 6 )  << value;
      }
      str << std::endl;
   }
}

bool Matrix::readMtxFile( std::istream& str )
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
         this->setElement( row, column,  value );
         if( matrixType == "symmetric" && row != column )
            this->setElement( column, row, value );
      }
   }
   return true;
}

std::ostream& operator << ( std::ostream& str, const Matrix& m )
{
   m.print( str );
   return str;
}


