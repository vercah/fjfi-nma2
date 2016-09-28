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

class DenseMatrix
{
   public:
   
      DenseMatrix();
            
      DenseMatrix( const int rows, const int columns );
      
      bool setDimensions( const int rows, const int columns );
   
      Real& operator()( const int row, const int column );
      
      const Real& operator()( const int row, const int column ) const;
      
      bool readMtxFile( std::istream& file );
      
      void print( std::ostream& str );         
      
   private:
      
      int rows, columns;
      
      std::vector< Real > elements;

};

