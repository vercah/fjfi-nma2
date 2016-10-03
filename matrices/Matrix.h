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
      
      virtual void vectorMultiplication( const Vector& in_vector,
                                         Vector& out_vector ) const = 0;
      
      int getRows() const;
      
      int getColumns() const;
      
      void print( std::ostream& str,
                  const int precision = 8,
                  const std::string zero = "0" );         


   protected:
      
      int rows, columns;   
};

