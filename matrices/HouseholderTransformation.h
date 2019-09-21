/*
 * File:   HouseholderTransformation.h
 * Author: oberhuber
 *
 * Created on September 12, 2019, 7:26 PM
 */

#pragma once

#include "../matrices/DenseMatrix.h"
#include "../Vector.h"

class HouseholderTransformation
{
   public:

      HouseholderTransformation( int size );

      bool init( DenseMatrix& matrix, int row, int column );

      void applyFromLeft( DenseMatrix& A );

      void applyFromRight( DenseMatrix& A );

      bool computeQR( DenseMatrix& A, DenseMatrix& Q );

   protected:

      int size;

      Vector w;
      
      double x1_sign, x_norm;
};