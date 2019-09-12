#include "TriangularMethod.h"
#include "../gem/LUDecomposition.h"
#include "../Vector.h"
#include "../matrices/TriangularOperations.h"
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

bool TriangularMethod::solve( Vector& spectrum, DenseMatrix& eigenvectorsA, int verbose ) const
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

   DenseMatrix check( size, size ), AL_copy( size, size );

   while( iteration < this->max_iterations )
   {
      computeMatrixTimesL( A, L, AL );
      AL_copy = AL;
      LUDecomposition decomposition( AL );
      if( ! decomposition.computeByDoolitle() )
      {
         std::cerr << "Cannot compute LU decomposition, reaching matrix which is not strongly regular." << std::endl;
         return false;
      }
      double max_LU_error( -1 );
      if( checkLUDecomposition )
         decomposition.getError( AL_copy, max_LU_error );

      double residue( 0.0 );
      for( int i = 0; i < size; i++ )
      {
         spectrum[ i ] = AL( i, i );
         double diff = spectrum_old[ i ] - spectrum[ i ];
         //std::cerr << "diff -> " << diff << std::endl;
         residue += diff * diff;
         spectrum_old[ i ] = spectrum[ i ];
      }
      AL.swap( L );
      residue = sqrt( residue );
      std::cout << "RES: " << residue << " LU error " << max_LU_error << std::endl;

      if( residue < this->convergence_residue )
      {
         /***
          * Compute eigenvectors of R
          */
         DenseMatrix eigenvectorsR( size, size );
         for( int j = size - 1; j >= 0; j-- )
            for( int i = size - 1; i >= 0; i-- )
            {
               if( j < i )
                  eigenvectorsR( i, j ) = 0.0;
               if( j == i )
                  eigenvectorsR( i, j ) = 1.0;
               if( j > i )
               {
                  /***
                   * First case of eigenvalue of higher multiplicity
                   */
                  if( fabs( ( AL( i, i ) - spectrum[ j ] ) ) < 1.0e-8 )
                     eigenvectorsR( i, j ) = 0.0;
                  else
                  {
                     double aux( 0.0 );
                     for( int k = j; k > i; k-- )
                        aux += eigenvectorsR( k, j ) * AL( i, k );
                     eigenvectorsR( i, j ) = -aux / ( AL( i, i ) - spectrum[ j ] );
                  }
               }
            }

         /***
          * Transform to eigenvectors of A by multiplying with L
          */
         computeLTimesMatrix( AL, eigenvectorsR, eigenvectorsA );

         return true;
      }

      iteration++;
   }
   std::cerr << "Method did not converge." << std::endl;
   return false;
}

