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

      GivensRotation( int size );

      void init( DenseMatrix& matrix, int row1, int row2, int column );

      void apply( DenseMatrix& A );

      void computeQR( DenseMatrix& A, DenseMatrix& Q );

   protected:

      int size;

      double c, s;
};