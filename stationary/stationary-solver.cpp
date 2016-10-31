/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jacobi-test.cpp
 * Author: oberhuber
 *
 * Created on October 24, 2016, 4:15 PM
 */

#include <fstream>
#include "StationarySolver.h"
#include "../CommandLineParser.h"
#include "../matrices/DenseMatrix.h"
#include "../Timer.h"

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
 
   std::string method;
   if( parser.cmdOptionExists( "--method" ) )
      method = parser.getCmdOption( "--method" );

   Real relaxation( 1.0 );
   if( parser.cmdOptionExists( "--relaxation" ) )
      relaxation = std::stof( parser.getCmdOption( "--relaxation" ) );
   
   std::string matrix_format( "dense" );
   if( parser.cmdOptionExists( "--matrix-format" ) )
      matrix_format = parser.getCmdOption( "--matrix-format" );
   
   int max_iterations( 1000 );
   if( parser.cmdOptionExists( "--max-iterations" ) )
      max_iterations = std::stoi( parser.getCmdOption( "--max-iterations" ) );
   
   Real convergence_residue( 1.0-6 );
   if( parser.cmdOptionExists( "--convergence-residue" ) )
      convergence_residue = std::stof( parser.getCmdOption( "--convergence-residue" ) );

   
   int verbose( 0 );
   if( parser.cmdOptionExists( "--verbose" ) )
      verbose = std::stoi( parser.getCmdOption( "--verbose" ) );

   
   Matrix* matrix( 0 );
   if( matrix_format == "dense" ) 
      matrix = new DenseMatrix;
   if( ! matrix )
   {
      std::cerr << "Unknown matrix format " << matrix_format << "." << std::endl;
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
   Vector x, b;   
   x.setSize( n );
   b.setSize( n );
   for( int i = 0; i < n; i++ )
      x[ i ] = 1.0;

   Timer timer;
   timer.reset();
   timer.start();   
   std::cout << "Multiplying matrix-vector..." << std::endl;
   matrix->vectorMultiplication( x, b );
   timer.stop();
   std::cout << "Multiplication took " << timer.getTime() << " seconds." << std::endl;
   for( int i = 0; i < n; i++ )
      x[ i ] = 0.0;

   std::cout << "Solving linear system by the " << method << " method..." << std::endl;
   StationarySolver solver( *matrix, b );
   timer.reset();
   timer.start();
   solver.solve( x, max_iterations, convergence_residue, method, relaxation, verbose );
   timer.stop();

   if( verbose == 1 )
      std::cerr << "Result is " << x << std::endl;
   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;   
   return EXIT_SUCCESS;
}


