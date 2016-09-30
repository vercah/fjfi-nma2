#include "matrices/DenseMatrix.h"
#include "CommandLineParser.h"
#include <algorithm>
#include <fstream>
#include <cstdlib>

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
   std::cout << "Matrix = " << std::endl;
   matrix.print( std::cout, 6 );
   return EXIT_SUCCESS;
}
