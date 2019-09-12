#include <assert.h>
#include <iostream>
#include <cmath>

#include "LRAlgorithm.h"
#include "../gem/LUDecomposition.h"
#include "../Vector.h"
#include "../matrices/TriangularOperations.h"
#include "eigenvectors.h"


LRAlgorithm::LRAlgorithm( const DenseMatrix& A )
:  A( A ), max_iterations( 100 ), convergence_residue( 1.0e-8 )
{
}

void LRAlgorithm::setMaxIterations( const int max_iterations )
{
   this->max_iterations = max_iterations;
}

void LRAlgorithm::setConvergenceResidue( const Real& convergence_residue )
{
   this->convergence_residue = convergence_residue;
}

void LRAlgorithm::setLUDecompositionCheck( bool check )
{
   this->checkLUDecomposition = check;
}

bool LRAlgorithm::solve( Vector& spectrum, DenseMatrix& eigenvectors, int verbose ) const
{
   int size = A.getRows();
   assert( size == A.getColumns() );

   DenseMatrix A_i( size, size ), RL( size, size ), L( size, size ), L_new( size, size );
   A_i = A;
   Vector spectrum_old( size );
   for( int i = 0; i < size; i++ )
   {
      spectrum_old[ i ] = 0.0;
      for( int j = 0; j < size; j++ )
         L( i, j ) = ( i == j );
   }

   int iteration( 0 );
   int norm_index( 0 );
   Real residue( this->convergence_residue + 1.0 );

   DenseMatrix check( size, size );

   while( iteration < this->max_iterations )
   {
      if( checkLUDecomposition )
         RL = A_i;
      LUDecomposition decomposition( A_i );
      if( ! decomposition.computeByDoolitle() )
      {
         std::cerr << "Cannot compute LU decomposition, reaching matrix which is not strongly regular." << std::endl;
         return false;
      }
      double max_LU_error( -1 );
      if( checkLUDecomposition )
         decomposition.getError( RL, max_LU_error );

      if( verbose > 1 )
         std::cout << "LU decomposition of A^K is: " << std::endl << A_i << std::endl;
      computeRTimesL( A_i, RL );
      A_i.swap( RL );
      computeMatrixTimesL( L, A_i, L_new );
      L.swap( L_new );
      if( verbose > 1 )
      {
         std::cout << "A^k = " << std::endl << A_i << std::endl;
         std::cout << "L = " << std::endl << L << std::endl;
      }

      double residue( 0.0 );
      for( int i = 0; i < size; i++ )
      {
         spectrum[ i ] = A_i( i, i );
         double diff = spectrum_old[ i ] - spectrum[ i ];
         residue += diff * diff;
         spectrum_old[ i ] = spectrum[ i ];
      }
      residue = sqrt( residue );
      std::cout << "RES: " << residue << " LU error " << max_LU_error << std::endl;

      if( residue < this->convergence_residue )
      {
         getEigenvectors( A_i, L, eigenvectors, true );
         return true;
      }

      iteration++;
   }
   std::cerr << "Method did not converge." << std::endl;
   return false;
}

