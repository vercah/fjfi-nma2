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
      
      bool setRowLength( const int row_width );
      
      bool setElement( const int row, const int column, const Real& value );
      
      Real getElement( const int row, const int column ) const;
      
      void vectorMultiplication( const Vector& in_vector,
                                 Vector& out_vector ) const;

      void performRichardsonIteration( const Vector& b,
                                       const Vector& x,
                                       Vector& aux,
                                       const Real& relaxation = 1.0 ) const;
      
      void performJacobiIteration( const Vector& b,
                                   const Vector& x,
                                   Vector& aux,
                                   const Real& relaxation = 1.0 ) const;
      
      void performSORIteration( const Vector& b,
                                Vector& x,
                                const Real& relaxation = 1.0 ) const;
      
      void getResidue( const Vector& x, const Vector& b, Vector& r ) const;      
      
      EllpackMatrix& operator=( const EllpackMatrix& m );
      
      EllpackMatrix& operator-=( const EllpackMatrix& m );
            
      bool readMtxFile( std::istream& file );
      
            
   private:
      
      bool allocate();
      
      void printRow( const int row );
      
      int row_width;
      
      std::vector< int > column_indexes;
      
      std::vector< Real > elements;
};
