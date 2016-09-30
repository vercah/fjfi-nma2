/* 
 * File:   denseMatrix.h
 * Author: oberhuber
 *
 * Created on September 28, 2016, 5:31 PM
 */

#pragma once

#include <vector>
#include <iostream>
#include "../real.h"
#include "Matrix.h"

class DenseMatrix : public Matrix
{
   public:
   
      DenseMatrix();
            
      DenseMatrix( const int rows, const int columns );
      
      bool setDimensions( const int rows, const int columns );
      
      int getRows() const;
      
      int getColumns() const;
   
      Real& operator()( const int row, const int column );
      
      const Real& operator()( const int row, const int column ) const;
      
      void vectorMultiplication( const std::vector< Real >& in_vector,
                                 std::vector< Real >& out_vector ) const;
      
      bool readMtxFile( std::istream& file );
      
      void print( std::ostream& str,
                  const int precision = 8,
                  const std::string zero = "0" );         
      
   private:
      
      int rows, columns;
      
      std::vector< Real > elements;

};

