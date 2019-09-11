/* 
 * File:   TriangularOperations.h
 * Author: oberhuber
 *
 * Created on September 11, 2019, 3:06 PM
 */

#pragma once


#include "DenseMatrix.h"

void computeMatrixTimesL( const DenseMatrix& A, const DenseMatrix& LU, DenseMatrix& result );

void computeLTimesMatrix( const DenseMatrix& LU, const DenseMatrix& A, DenseMatrix& result );

void computeRTimesL( const DenseMatrix& LU, DenseMatrix& result );
