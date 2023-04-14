/* 
 * File:   QRAlgorithm.h
 * Author: oberhuber
 *
 * Created on September 21, 2019, 2:52 PM
 */

#pragma once

#include <string>
#include "../matrices/DenseMatrix.h"
#include "../Vector.h"

class QRAlgorithm
{
   public:

      QRAlgorithm( const DenseMatrix& A );

      void setMaxIterations( const int max_iterations );

      void setConvergenceResidue( const Real& convergence_resideu );

      void setQRDecompositionCheck( bool check );

      bool solve( Vector& spectrum, DenseMatrix& eigenvectors, std::string method = "householder", int verbose = 0 ) const;

      bool solveByHessenberg( Vector& spectrum, DenseMatrix& eigenvectors, int verbose = 0 ) const;

   protected:

      const DenseMatrix& A;

      int max_iterations;

      Real convergence_residue;

      bool checkQRDecomposition = false;
};