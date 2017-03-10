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
      
      virtual bool setElement( const int row, const int column, const Real& value ) = 0;
      
      virtual Real getElement( const int row, const int column ) const = 0;
      
      virtual void vectorMultiplication( const Vector& in_vector,
                                         Vector& out_vector ) const = 0;
      
      virtual void performRichardsonIteration( const Vector& b,
                                               const Vector& x,
                                               Vector& aux,
                                               const Real& relaxation = 1.0 ) const = 0;
      
      virtual void performJacobiIteration( const Vector& b,
                                           const Vector& x,
                                           Vector& aux,
                                           const Real& relaxation = 1.0 ) const = 0;
      
      virtual void performSORIteration( const Vector& b,
                                        Vector& x,
                                        const Real& relaxation = 1.0 ) const = 0;
      
      
      virtual void getResidue( const Vector& x, const Vector& b, Vector& r ) const = 0;
      
      void getEigenvalueResidue( const Vector& eigenvector,
                                 const Real& eigenvalue,
                                 Vector& residue ) const;      

      int getRows() const;
      
      int getColumns() const;
      
      Real maxNorm() const;      
      
      void print( std::ostream& str,
                  const int precision = 8,
                  const std::string zero = "0" ) const;
      
      virtual bool readMtxFile( std::istream& file );

   protected:
      
      int rows, columns;   
};

std::ostream& operator << ( std::ostream& str, const Matrix& m );
