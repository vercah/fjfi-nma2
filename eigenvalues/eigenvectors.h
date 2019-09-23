/* 
 * File:   eigenvectors.h
 * Author: oberhuber
 *
 * Created on September 12, 2019, 5:21 PM
 */

#include "../matrices/DenseMatrix.h"
#include "../Vector.h"

#pragma once

/**
 * Computes eigenvectors of matrix A given by A = T R T^{-1}.
 * 
 * @param R - upper triangular matrix
 * @param T - transformation matrix
 * @param eigenvectors - matrix having eigenvectors as columns
 * @param lowerTriangularTransformation - is true when the transformation is stored 
 *        only in lower triangular part of T with ones on diagonal
 */
void getEigenvectors( const DenseMatrix& R, const DenseMatrix& T, DenseMatrix& eigenvectors, bool lowerTriangularTransformation = false );

void checkEigenvectors( const DenseMatrix& A, const DenseMatrix& eigenvectors, const Vector& spectrum, Vector& errors );