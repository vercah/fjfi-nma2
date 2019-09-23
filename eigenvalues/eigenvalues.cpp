/*
 * File:   eigenvalues.cpp
 * Author: oberhuber
 *
 * Created on September 11, 2019, 4:10 PM
 */

#include <fstream>
#include "../CommandLineParser.h"
#include "../matrices/DenseMatrix.h"
#include "../matrices/HouseholderTransformation.h"
#include "../Timer.h"
#include "../Vector.h"
#include "eigenvectors.h"
#include "TriangularMethod.h"
#include "LRAlgorithm.h"
#include "QRAlgorithm.h"

int main( int argc, char* argv[] )
{
   CommandLineParser parser( argc, argv );

   std::string file_name;
   if( parser.cmdOptionExists( "-i" ) )
      file_name = parser.getCmdOption( "-i" );
   else
      if( parser.cmdOptionExists( "--input-file" ) )
         file_name = parser.getCmdOption( "--input-file" );
      else
      {
         std::cerr << "No input file was given, use -i or --input-file." << std::endl;
      }

   std::string method( "triangular" );
   if( parser.cmdOptionExists( "-m" ) )
      method = parser.getCmdOption( "-m" );
   else
      if( parser.cmdOptionExists( "--method" ) )
         method = parser.getCmdOption( "--method" );

   int max_iterations( 1000 );
   if( parser.cmdOptionExists( "--max-iterations" ) )
      max_iterations = std::stoi( parser.getCmdOption( "--max-iterations" ) );

   Real convergence_residue( 1.0e-3 );
   if( parser.cmdOptionExists( "--convergence-residue" ) )
      convergence_residue = std::stof( parser.getCmdOption( "--convergence-residue" ) );

   bool withDecompositionError( true );
   if( parser.cmdOptionExists( "--with-decomposition-error" ) )
      if( parser.getCmdOption( "--with-decomposition-error" ) == "yes" )
         withDecompositionError = true;
      else withDecompositionError = false;

   bool showSpectrum( true );
   if( parser.cmdOptionExists( "--show-spectrum" ) )
      if( parser.getCmdOption( "--show-spectrum" ) == "yes" )
         showSpectrum = true;
      else showSpectrum = false;

   bool showEigenvectors( false );
   if( parser.cmdOptionExists( "--show-eigenvectors" ) )
      if( parser.getCmdOption( "--show-eigenvectors" ) == "yes" )
         showEigenvectors = true;
      else showEigenvectors = false;

   int verbose( 0 );
   if( parser.cmdOptionExists( "--verbose" ) )
      verbose = std::stoi( parser.getCmdOption( "--verbose" ) );

   DenseMatrix matrix;

   std::fstream file;
   file.open( file_name.data(), std::ios::in );
   if( ! file )
   {
      std::cerr << "Cannot open file " << file_name << "." << std::endl;
      return EXIT_FAILURE;
   }
   if( ! matrix.readMtxFile( file ) )
      return EXIT_FAILURE;

   if( matrix.getRows() != matrix.getColumns() )
   {
      std::cerr << "Only square matrices are allowed for GEM." << std::endl;
      return EXIT_FAILURE;
   }
   const int n = matrix.getRows();
   std::cout << "Matrix dimensions are " << n << "x" << n << "." << std::endl;
   if( verbose >= 1 )
      std::cout << "Matrix is:" << std::endl << matrix << std::endl;

   std::cout << "Finding complete matrix spectrum..." << std::endl;

   DenseMatrix eigenvectors( matrix.getRows(), matrix.getColumns() );
   Vector spectrum( matrix.getRows() );
   Timer timer;
   timer.reset();
   timer.start();

   if( method == "triangular" )
   {
      TriangularMethod triangular_method( matrix );
      triangular_method.setMaxIterations( max_iterations );
      triangular_method.setConvergenceResidue( convergence_residue );
      triangular_method.setLUDecompositionCheck( withDecompositionError );
      triangular_method.solve( spectrum, eigenvectors, verbose );
   }
   if( method == "lr" )
   {
      LRAlgorithm lr( matrix );
      lr.setMaxIterations( max_iterations );
      lr.setConvergenceResidue( convergence_residue );
      lr.setLUDecompositionCheck( withDecompositionError );
      lr.solve( spectrum, eigenvectors, verbose );
   }
   if( method == "qr" )
   {
      QRAlgorithm qr( matrix );
      qr.setMaxIterations( max_iterations );
      qr.setConvergenceResidue( convergence_residue );
      qr.setQRDecompositionCheck( withDecompositionError );
      qr.solve( spectrum, eigenvectors, "householder", verbose );
   }
   if( method == "qr-hessenberg" )
   {
      DenseMatrix H( n, n ), Q( n, n );
      H = matrix;
      if( verbose )
         std::cout << "Converting matrix to Hessenberg form ..." << std::endl;
      HouseholderTransformation householder( n );
      householder.computeHessenbergForm( H, Q );
      std::cout << " H = " << std::endl << H << std::endl;
      double max_error;
      householder.checkHessenbergForm( H, Q, matrix, max_error );
      std::cout << "Hessenberg form error is " << max_error << std::endl;
      return 0;
      /*QRAlgorithm qr( H );
      qr.setMaxIterations( max_iterations );
      qr.setConvergenceResidue( convergence_residue );
      qr.setQRDecompositionCheck( withDecompositionError );
      qr.solve( spectrum, eigenvectors, "householder", verbose );
       */
   }   
   timer.stop();

   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;
   if( showSpectrum )
      std::cout << "Spectrum is: " << spectrum << std::endl;
   if( showEigenvectors )
      std::cout << "Eigenvectors are: " << std::endl << eigenvectors << std::endl;
   Vector errors;
   checkEigenvectors( matrix, eigenvectors, spectrum, errors );
   std::cout << "Eigenvector residues are: " << errors << std::endl;
   return EXIT_SUCCESS;
}


