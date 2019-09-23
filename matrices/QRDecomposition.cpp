#include "QRDecomposition.h"
#include "../matrices/GrammSchmidt.h"
#include "../matrices/HouseholderTransformation.h"
#include "../matrices/GivensRotation.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <math.h>

#include "QRDecomposition.h"

QRDecomposition::QRDecomposition( DenseMatrix& A )
: A( A )
{
}

bool QRDecomposition::computeByGrammSchmidt( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   GrammSchmidt gs;
   Q = A;
   return gs.computeQR( Q, R );
}

bool QRDecomposition::computeByHouseholderTransformations( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   HouseholderTransformation householder( A.getRows() );
   R = A;
   return householder.computeQR( R, Q );
}

bool QRDecomposition::computeByGivensRotations( DenseMatrix& Q, DenseMatrix& R, int verbose )
{
   GivensRotation givens( A.getRows() );
   R = A;
   return givens.computeQR( R, Q );
}


void QRDecomposition::restoreMatrix( DenseMatrix& Q, DenseMatrix& R, DenseMatrix& B )
{
   assert( B.getColumns() == A.getColumns() );
   assert( B.getRows() ==  A.getRows() );

   B.matrixMultiplication( Q, R );
}

void QRDecomposition::getError( DenseMatrix& Q, DenseMatrix& R, DenseMatrix& A, double& max_error )
{
   assert( A.getRows() == A.getColumns() );
   const int size = A.getRows();
   DenseMatrix m( size, size );
   this->restoreMatrix( Q, R, m );
   m -= A;
   max_error = m.maxNorm();
}