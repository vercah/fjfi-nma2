/* 
 * File:   EllpackMatrix.h
 * Author: oberhuber
 *
 * Created on October 26, 2016, 3:32 PM
 */

#pragma once

#include <vector>
#include <iostream>
#include "../real.h"
#include "Matrix.h"
#include "../Vector.h"

class EllpackMatrix : public Matrix
{
   public:
   
      EllpackMatrix();
            
      EllpackMatrix( const int rows, const int columns );
      
      bool setDimensions( const int rows, const int columns );
      
      bool setRowWidth( const int row_width );
      
      Real& operator()( const int row, const int column );
      
      const Real& operator()( const int row, const int column ) const;
      
      void vectorMultiplication( const Vector& in_vector,
                                 Vector& out_vector ) const;

      void performJacobiIteration( const Vector& b,
                                   const Vector& x,
                                   Vector& aux ) const;
      
      EllpackMatrix& operator=( const EllpackMatrix& m );
      
      EllpackMatrix& operator-=( const EllpackMatrix& m );
      
            
   private:
      
      bool allocate();      
      
      int row_width;
      
      std::vector< int > columns;
      
      std::vector< Real > elements;
};
