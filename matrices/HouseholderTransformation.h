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

      void init( DenseMatrix& matrix, int row, int column );

      void computeTransformationTimesMatrix( const DenseMatrix& A, DenseMatrix& result );

      void computeQR( DenseMatrix& A, DenseMatrix& Q );

   protected:

      int size;

      Vector w;
};