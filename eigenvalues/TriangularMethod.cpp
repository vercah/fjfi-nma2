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
   DenseMatrix eigenvectorsR( size, size );

   while( iteration < this->max_iterations )
   {
      std::cout << "A = " << std::endl;
      A.print();
      std::cout << std::endl;
      computeMatrixTimesL( A, L, AL );
      /*std::cout << "AL = " << std::endl;
      AL.print();
      std::cout << std::endl;*/
      LUDecomposition decomposition( AL );
      decomposition.computeByDoolitle();
      std::cout << "LU of AL = " << std::endl;
      AL.print();
      std::cout << std::endl;

      double res( 0.0 );
      for( int i = 0; i < size; i++ )
      {
         spectrum[ i ] = AL( i, i );
         double diff = spectrum_old[ i ] - spectrum[ i ];
         res += diff * diff;
         spectrum_old[ i ] = spectrum[ i ];
      }
      AL.swap( L );
      
      /***
       * Compute eigenvectors of R
       */
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
      std::cout << "Eigenvectors of R = " << std::endl;
      eigenvectorsR.print();
      computeLTimesMatrix( AL, eigenvectorsR, eigenvectorsA );
      std::cout << "Eigenvectors of A = " << std::endl;
      eigenvectorsA.print();
      
      std::cout << "A times eigenvectors = " << std::endl;
      DenseMatrix check( size, size );
      check.matrixMultiplication( A, eigenvectorsA );
      check.print();
      res = sqrt( res );

      std::cout << spectrum << std::endl;

      iteration++;
   }
   return false;
}

