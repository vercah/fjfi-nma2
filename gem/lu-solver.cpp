#include <fstream>
#include "LUDecomposition.h"
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
   
   int verbose( 0 );
   if( parser.cmdOptionExists( "--verbose" ) )
      verbose = std::stoi( parser.getCmdOption( "--verbose" ) );
   
   std::string method( "gem" );
   if( parser.cmdOptionExists( "--method" ) )
      method = parser.getCmdOption( "--method" );
   
   
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
   DenseMatrix A, B;
   A = matrix;
      Vector x, b;   
   x.setSize( n );
   b.setSize( n );
   for( int i = 0; i < n; i++ )
      x[ i ] = 1.0;

   Timer timer;
   timer.reset();
   timer.start();   
   std::cout << "Multiplying matrix-vector..." << std::endl;
   matrix.vectorMultiplication( x, b );
   timer.stop();
   std::cout << "Multiplication took " << timer.getTime() << " seconds." << std::endl;

   std::cout << "Computing the LU decomposition..." << std::endl;
   LUDecomposition lu( A );   
   
   timer.reset();
   timer.start();
   if( method == "gem" )
      lu.computeByGEM( verbose );
   else
      lu.computeByCrout( verbose );
   timer.stop();

   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;
   
   std::cout << "Solving the system ... " << std::endl;
   timer.reset();
   timer.start();
   lu.solve( b, verbose );
   timer.stop();
   
   //std::cout << "Result is: " << std::endl << b << std::endl;
   std::cout << "Solution took " << timer.getTime() << " seconds." << std::endl;
   return EXIT_SUCCESS;
}

