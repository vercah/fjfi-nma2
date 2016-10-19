#include <iomanip>
#include "Matrix.h"

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

void Matrix::print( std::ostream& str,
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
