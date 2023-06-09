/* 
 * File:   LRAlgorithm.h
 * Author: oberhuber
 *
 * Created on September 11, 2019, 2:52 PM
 */

#pragma once

#include "../matrices/DenseMatrix.h"
#include "../Vector.h"

class LRAlgorithm
{
   public:

      LRAlgorithm( const DenseMatrix& A );

      void setMaxIterations( const int max_iterations );

      void setConvergenceResidue( const Real& convergence_resideu );

      void setLUDecompositionCheck( bool check );

      bool solve( Vector& spectrum, DenseMatrix& eigenvectors, int verbose = 0 ) const;

   protected:

      const DenseMatrix& A;

      int max_iterations;

      Real convergence_residue;

      bool checkLUDecomposition = false;
};