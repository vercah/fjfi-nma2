/* 
 * File:   Matrix.h
 * Author: oberhuber
 *
 * Created on September 30, 2016, 11:57 AM
 */

#pragma once

#include "../Vector.h"
#include "../real.h"

class Matrix
{
   public:
      
      Matrix();
      
      Matrix( const int rows, const int columns );
      
      virtual bool setDimensions( const int rows, const int columns ) = 0;
      
      virtual Real& operator()( const int row, const int column ) = 0;
      
      virtual const Real& operator()( const int row, const int column ) const = 0;
      
      virtual void vectorMultiplication( const Vector& in_vector,
                                         Vector& out_vector ) const = 0;
      
      int getRows() const;
      
      int getColumns() const;
      
      Real maxNorm() const;
      
      void print( std::ostream& str,
                  const int precision = 8,
                  const std::string zero = "0" );
      
      bool readMtxFile( std::istream& file );      

   protected:
      
      int rows, columns;   
};

