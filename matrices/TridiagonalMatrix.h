/* 
 * File:   TridiagonalMatrix.h
 * Author: oberhuber
 *
 * Created on October 3, 2016, 8:28 AM
 */

#pragma once

#include <vector>
#include <iostream>
#include "../real.h"
#include "Matrix.h"
#include "../Vector.h"

class TridiagonalMatrix : public Matrix
{
   public:
   
      TridiagonalMatrix();
            
      TridiagonalMatrix( const int rows, const int columns );
      
      bool setDimensions( const int rows, const int columns );
      
      Real& operator()( const int row, const int column );
      
      const Real& operator()( const int row, const int column ) const;
      
      void vectorMultiplication( const Vector& in_vector,
                                 Vector& out_vector ) const;
      
      TridiagonalMatrix& operator=( const TridiagonalMatrix& m );
      
      bool readMtxFile( std::istream& file );
      
      void print( std::ostream& str,
                  const int precision = 8,
                  const std::string zero = "0" );         
      
   private:      
      
      std::vector< Real > elements;

};




