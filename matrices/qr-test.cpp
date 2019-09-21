#include <fstream>
#include "../matrices/QRDecomposition.h"
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
   
   std::string method( "gramm-schmidt" );
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
   if( verbose > 1 )
      std::cout << "Matrix is:" << std::endl << matrix << std::endl;
   const int size = matrix.getRows();
   DenseMatrix A, B, Q( size, size ), R( size, size );
   A = matrix;
   QRDecomposition qr( A );
   Timer timer;
   timer.reset();
   timer.start();
   bool status( true );
   if( method == "gramm-schmidt" )
      status = qr.computeByGrammSchmidt( Q, R, verbose );
   if( method == "householder")
      status = qr.computeByHouseholderTransformations( Q, R, verbose );
   if( method == "givens" )
      status = qr.computeByGivensRotations( Q, R, verbose );
   timer.stop();

   if( ! status )
   {
      std::cerr << "QR decomposition computation failed -the matrix is probably not regular." << std::endl;
      return EXIT_FAILURE;
   }

   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;
   if( verbose > 1 )
      std::cout << "Result is: " << std::endl << Q << std::endl << R << std::endl;
   double orthogonalityError = Q.checkOrthogonality( verbose );
   std::cout << "Error of Q orthogonality is " << orthogonalityError << "." << std::endl;
   B.setDimensions( A.getRows(), A.getColumns() );
   qr.restoreMatrix( Q, R, B );
   if( verbose > 1 )
      std::cout << "Restored matrix is: " << std::endl << B << std::endl;
   B -= matrix;
   std::cout << "Max. norm of the difference is " << B.maxNorm() << "." << std::endl;

   return EXIT_SUCCESS;
}

