/* 
 * File:   power-method.cpp
 * Author: oberhuber
 *
 * Created on November 15, 2016, 2:00 PM
 */

#include <fstream>
#include "../stationary/StationarySolver.h"
#include "../CommandLineParser.h"
#include "../matrices/DenseMatrix.h"
#include "../matrices/EllpackMatrix.h"
#include "../Timer.h"
#include "PowerMethod.h"

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
 
   bool smallest( false );
   if( parser.cmdOptionExists( "--eigenvalue" ) )
      if( parser.getCmdOption( "--eigenvalue" ) == "smallest" )
         smallest = true;
   
   Real initial_value( 1.0 );
   if( parser.cmdOptionExists( "--initial-value" ) )
      initial_value = std::stof( parser.getCmdOption( "--initial-value" ) );   
   
   std::string linear_solver( "sor");
   if( parser.cmdOptionExists( "--linear-solver" ) )
      linear_solver = parser.getCmdOption( "--linear-solver" );

   int max_iterations( 1000 );
   if( parser.cmdOptionExists( "--max-iterations" ) )
      max_iterations = std::stoi( parser.getCmdOption( "--max-iterations" ) );
   
   Real convergence_residue( 1.0e-6 );
   if( parser.cmdOptionExists( "--convergence-residue" ) )
      convergence_residue = std::stof( parser.getCmdOption( "--convergence-residue" ) );

   int verbose( 0 );
   if( parser.cmdOptionExists( "--verbose" ) )
      verbose = std::stoi( parser.getCmdOption( "--verbose" ) );

   Matrix* matrix( 0 );
   matrix = new EllpackMatrix;
   
   if( ! matrix )
   {
      std::cerr << "Unable to allocate the matrix." << std::endl;
      return EXIT_FAILURE;
   }
   std::fstream file;
   file.open( file_name.data(), std::ios::in );
   if( ! file )
   {
      std::cerr << "Cannot open file " << file_name << "." << std::endl;
      return EXIT_FAILURE;
   }
   if( ! matrix->readMtxFile( file ) )
      return EXIT_FAILURE;

   if( matrix->getRows() != matrix->getColumns() )
   {
      std::cerr << "Only square matrices are allowed for GEM." << std::endl;
      return EXIT_FAILURE;
   }
   const int n = matrix->getRows();
   std::cout << "Matrix dimensions are " << n << "x" << n << "." << std::endl;
   if( verbose >= 1 )
      std::cout << "Matrix is:" << std::endl << matrix << std::endl;
   Vector x;   
   Real lambda;
   x.setSize( matrix->getColumns() );
   for( int i = 0; i < x.getSize(); i++ )
      x[ i ] = initial_value;


   std::cout << "Finding the eigenvalue by the power method..." << std::endl;
   PowerMethod power_method( *matrix );
   power_method.setMaxIterations( max_iterations );
   power_method.setConvergenceResidue( convergence_residue );
   Timer timer;
   timer.reset();
   timer.start();
   power_method.getEigenvalue( x, lambda, smallest, verbose );
   timer.stop();
   std::cout << "lambda = " << lambda << std::endl;

   
   if( verbose == 1 )
      std::cerr << "Result is " << x << std::endl;
   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;   
   return EXIT_SUCCESS;
}


