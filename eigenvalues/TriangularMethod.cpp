#include "TriangularMethod.h"
#include "../matrices/LUDecomposition.h"
#include "../Vector.h"
#include "../matrices/TriangularOperations.h"
#include "eigenvectors.h"
#include <iostream>
#include <cmath>
#include <assert.h>

TriangularMethod::TriangularMethod( const DenseMatrix& A )
:  A( A ), max_iterations( 100 ), convergence_residue( 1.0e-8 )
{
}

void TriangularMethod::setMaxIterations( const int max_iterations )
{
   this->max_iterations = max_iterations;
}

void TriangularMethod::setConvergenceResidue( const Real& convergence_residue )
{
   this->convergence_residue = convergence_residue;
}

void TriangularMethod::setLUDecompositionCheck( bool check )
{
   this->checkLUDecomposition = check;
}

bool TriangularMethod::solve( Vector& spectrum, DenseMatrix& eigenvectors, int verbose ) const
{
   int size = A.getRows();
   assert( size == A.getColumns() );

   Vector spectrum_old( size );
   for( int i = 0; i < size; i++ )
      spectrum_old[ i ] = 0.0;
   DenseMatrix L( size, size ), AL( size, size );
   for( int i = 0; i < size; i++ )
      for( int j = 0; j < size; j++ )
         if( i == j )
            L( i, j ) = 1.0;
         else
            L( i, j ) = 0.0;

   int iteration( 0 );
   int norm_index( 0 );
   Real residue( this->convergence_residue + 1.0 );

   DenseMatrix check( size, size ), AL_copy;
   if( checkLUDecomposition )
      AL_copy.setDimensions( size, size );

   while( iteration < this->max_iterations )
   {
      computeMatrixTimesL( A, L, AL );
      if( checkLUDecomposition )
         AL_copy = AL;
      if( verbose > 1 )
         std::cout << "AL = " << std::endl << AL << std::endl;
      LUDecomposition decomposition( AL );
      if( ! decomposition.computeByDoolitle() )
      {
         std::cerr << "Cannot compute LU decomposition, reaching matrix which is not strongly regular." << std::endl;
         return false;
      }
      if( verbose > 1 )
         std::cout << " LU decomposition of AL is: " << std::endl << AL << std::endl;
      double max_LU_error( -1 );
      if( checkLUDecomposition )
         decomposition.getError( AL_copy, max_LU_error );

      double residue( 0.0 );
      for( int i = 0; i < size; i++ )
      {
         spectrum[ i ] = AL( i, i );
         double diff = spectrum_old[ i ] - spectrum[ i ];
         residue += diff * diff;
         spectrum_old[ i ] = spectrum[ i ];
      }

      residue = sqrt( residue );
      if( verbose )
         std::cout << "RES: " << residue << " LU error " << max_LU_error << std::endl;
      iteration++;

      if( residue < this->convergence_residue )
      {
         getEigenvectors( AL, AL, eigenvectors, true );
         return true;
      }
      AL.swap( L );
   }
   std::cerr << "Method did not converge." << std::endl;
   return false;
}

