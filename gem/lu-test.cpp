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
   LUDecomposition lu( A );   
   Timer timer;
   timer.reset();
   timer.start();
   if( method == "gem" )
      lu.computeByGEM( verbose );
   else
      lu.computeByCrout( verbose );
   timer.stop();

   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;
   if( verbose >= 1 )
      std::cout << "Result is: " << std::endl << A << std::endl;
   B.setDimensions( A.getRows(), A.getColumns() );
   lu.restoreMatrix( B );
   if( verbose >= 1 )
      std::cout << "Restored matrix is: " << std::endl << B << std::endl;
   B -= matrix;
   std::cout << "Max. norm of the difference is " << B.maxNorm() << "." << std::endl;
   
   return EXIT_SUCCESS;
}

