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
#include "../Vector.h"

class DenseMatrix : public Matrix
{
   public:
   
      DenseMatrix();
            
      DenseMatrix( const int rows, const int columns );
      
      bool setDimensions( const int rows, const int columns );
      
      Real& operator()( const int row, const int column );
      
      const Real& operator()( const int row, const int column ) const;
      
      void vectorMultiplication( const Vector& in_vector,
                                 Vector& out_vector ) const;

      void performJacobiIteration( const Vector& b,
                                   const Vector& x,
                                   Vector& aux ) const;
      
      DenseMatrix& operator=( const DenseMatrix& m );
      
      DenseMatrix& operator-=( const DenseMatrix& m );
      
            
   private:            
      
      std::vector< Real > elements;
};

