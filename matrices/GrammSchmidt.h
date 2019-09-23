/* 
 * File:   GrammSchmidt.h
 * Author: oberhuber
 *
 * Created on September 23, 2019, 5:03 PM
 */

#pragma once

#include "DenseMatrix.h"

class GrammSchmidt
{
   public:
   
      /**
       * Turns matrix A into unitary matrix Q and fill the matrix R to form
       * QR decomposition.
       * 
       * @param A
       * @param R
       * @return 
       */
      bool computeQR( DenseMatrix& Q, DenseMatrix& R );
};
