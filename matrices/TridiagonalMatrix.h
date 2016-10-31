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
      
      bool setElement( const int row, const int column, const Real& value );
      
      Real getElement( const int row, const int column ) const;

      Real& operator()( const int row, const int column );
      
      const Real& operator()( const int row, const int column ) const;
      
      
      void vectorMultiplication( const Vector& in_vector,
                                 Vector& out_vector ) const;
      
      void performRichardsonIteration( const Vector& b,
                                       const Vector& x,
                                       Vector& aux,
                                       const Real& relaxation = 1.0 ) const{};
      
      void performJacobiIteration( const Vector& b,
                                   const Vector& x,
                                   Vector& aux,
                                   const Real& relaxation = 1.0 ) const{};
      
      void performSORIteration( const Vector& b,
                                Vector& x,
                                const Real& relaxation = 1.0 ) const {};
      
      
      void getResidue( const Vector& x, const Vector& b, Vector& r ) const {};
      
      TridiagonalMatrix& operator=( const TridiagonalMatrix& m );
      
   private:      
      
      std::vector< Real > elements;

};




