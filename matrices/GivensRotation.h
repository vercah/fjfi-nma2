/*
 * File:   GivensRotation.h
 * Author: oberhuber
 *
 * Created on September 18, 2019, 7:26 PM
 */

#pragma once

#include "../matrices/DenseMatrix.h"
#include "../Vector.h"

/**
 * 
 */
class GivensRotation
{
   public:

      bool init( DenseMatrix& matrix, int row1, int row2 );

      void applyFromLeft( DenseMatrix& A );

      void applyFromRight( DenseMatrix& A );

      bool computeQR( DenseMatrix& A, DenseMatrix& Q );

   protected:

      int size, row1, row2;

      double c, s;
};