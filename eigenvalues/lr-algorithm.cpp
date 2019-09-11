/* 
 * File:   lr-algorithm.cpp
 * Author: oberhuber
 *
 * Created on September 11, 2019, 4:10 PM
 */

#include <fstream>
#include "../CommandLineParser.h"
#include "../matrices/DenseMatrix.h"
#include "../Timer.h"
#include "../Vector.h"
#include "LRAlgorithm.h"

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

   int max_iterations( 1000 );
   if( parser.cmdOptionExists( "--max-iterations" ) )
      max_iterations = std::stoi( parser.getCmdOption( "--max-iterations" ) );

   Real convergence_residue( 1.0e-3 );
   if( parser.cmdOptionExists( "--convergence-residue" ) )
      convergence_residue = std::stof( parser.getCmdOption( "--convergence-residue" ) );

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

   std::cout << "Finding the matrix spectrum by the triangular method..." << std::endl;

   LRAlgorithm triangular_method( matrix );
   triangular_method.setMaxIterations( max_iterations );
   triangular_method.setConvergenceResidue( convergence_residue );
   DenseMatrix eigenvectors( matrix.getRows(), matrix.getColumns() );
   Vector spectrum( matrix.getRows() );
   Timer timer;
   timer.reset();
   timer.start();
   triangular_method.solve( spectrum, eigenvectors, verbose );
   timer.stop();

   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;   
   return EXIT_SUCCESS;
}


