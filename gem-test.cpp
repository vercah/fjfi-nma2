#include <fstream>
#include "GEM.h"
#include "CommandLineParser.h"
#include "matrices/DenseMatrix.h"


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
   
   DenseMatrix A;
   A = matrix;
   Vector x, b;   
   x.setSize( n );
   b.setSize( n );
   for( int i = 0; i < n; i++ )
      x[ i ] = 1.0;
   matrix.vectorMultiplication( x, b );
   for( int i = 0; i < n; i++ )
      x[ i ] = 0.0;
   
   GEM gem( A, b );
   gem.solve( x, 2 );   
   std::cout << "The result is [ " << x << " ]." << std::endl;
   
   A = matrix;
   for( int i = 0; i < n; i++ )
      x[ i ] = 1.0;
   matrix.vectorMultiplication( x, b );
   for( int i = 0; i < n; i++ )
      x[ i ] = 0.0;   
   std::cout << "Solving with pivoting ..." << std::endl;
   gem.solveWithPivoting( x, 2 );
   std::cout << "The result is [ " << x << " ]." << std::endl;
   
   return EXIT_SUCCESS;
}
