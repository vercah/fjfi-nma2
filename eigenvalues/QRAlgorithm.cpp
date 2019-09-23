#include <assert.h>
#include <iostream>
#include <cmath>

#include "QRAlgorithm.h"
#include "../matrices/LUDecomposition.h"
#include "../matrices/QRDecomposition.h"
#include "../Vector.h"
#include "../matrices/TriangularOperations.h"
#include "eigenvectors.h"


QRAlgorithm::QRAlgorithm( const DenseMatrix& A )
:  A( A ), max_iterations( 100 ), convergence_residue( 1.0e-8 )
{
}

void QRAlgorithm::setMaxIterations( const int max_iterations )
{
   this->max_iterations = max_iterations;
}

void QRAlgorithm::setConvergenceResidue( const Real& convergence_residue )
{
   this->convergence_residue = convergence_residue;
}

void QRAlgorithm::setQRDecompositionCheck( bool check )
{
   this->checkQRDecomposition = check;
}

bool QRAlgorithm::solve( Vector& spectrum, DenseMatrix& eigenvectors, std::string method, int verbose ) const
{
   int size = A.getRows();
   assert( size == A.getColumns() );

   DenseMatrix A_i( size, size ), R( size, size ), Q( size, size ), Q_global( size, size ), aux( size, size );
   A_i = A;
   Vector spectrum_old( size );
   for( int i = 0; i < size; i++ )
   {
      spectrum_old[ i ] = 0.0;
      for( int j = 0; j < size; j++ )
         Q( i, j ) = ( i == j );
   }

   int iteration( 0 );
   int norm_index( 0 );
   Real residue( this->convergence_residue + 1.0 );

   DenseMatrix check( size, size );
   Vector residues;

   while( iteration < this->max_iterations )
   {
      if( checkQRDecomposition )
         R = A_i;
      QRDecomposition decomposition( A_i );
      bool status( false );
      if( method == "gramm-schmidt ")
         status = decomposition.computeByGrammSchmidt( Q, R );
      else if( method == "householder" )
         status = decomposition.computeByHouseholderTransformations( Q, R );
      else if( method == "givens" )
         status = decomposition.computeByGivensRotations( Q, R );
      else
      {
         std::cerr << "Unknown method for QR decomposition:." << method << std::endl;
         return false;
      }
      if( ! status )
      {
         std::cerr << "QR decomposition computation failed - probably singular matrix." << std::endl;
         return false;
      }
      double max_QR_error( -1 );
      if( checkQRDecomposition )
         decomposition.getError( Q, R, A_i, max_QR_error );

      if( verbose > 1 )
         std::cout << "QR decomposition of A^K is: " << std::endl << A_i << std::endl;
      A_i.matrixMultiplication( R, Q );

      aux.matrixMultiplication( Q_global, Q );
      if( verbose > 1 )
      {
         std::cout << "A^k = " << std::endl << A_i << std::endl;
         //std::cout << "L = " << std::endl << L << std::endl;
      }

      residue = 0.0;
      for( int i = 0; i < size; i++ )
      {
         spectrum[ i ] = A_i( i, i );
         double diff = spectrum_old[ i ] - spectrum[ i ];
         residue += diff * diff;
         spectrum_old[ i ] = spectrum[ i ];
      }
      residue = sqrt( residue );
      /*if( iteration % 10 == 0 )
      {
         Vector errors;
         Q.transpose();
         getEigenvectors( A_i, Q, eigenvectors, true );
         checkEigenvectors( A, eigenvectors, spectrum, errors );
         Q.transpose();
         residue = errors.l2Norm();
      }*/
      std::cout << "RES: " << residue << " QR error " << max_QR_error << std::endl;

      if( residue < this->convergence_residue )
      {
         Q.transpose();
         getEigenvectors( A_i, Q, eigenvectors, true );
         return true;
      }

      iteration++;
   }
   std::cerr << "Method did not converge." << std::endl;
   return false;
}

