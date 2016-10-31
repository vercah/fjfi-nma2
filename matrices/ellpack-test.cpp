/* 
 * File:   ellpack-test.cpp
 * Author: oberhuber
 *
 * Created on October 31, 2016, 2:36 PM
 */

#include <cstdlib>

#include <fstream>
#include "../CommandLineParser.h"
#include "../matrices/DenseMatrix.h"
#include "../matrices/EllpackMatrix.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
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
   
   DenseMatrix dense_matrix;
   std::fstream file;
   file.open( file_name.data(), std::ios::in );
   if( ! file )
   {
      std::cerr << "Cannot open file " << file_name << "." << std::endl;
      return EXIT_FAILURE;
   }
   if( ! dense_matrix.readMtxFile( file ) )
      return EXIT_FAILURE;
   file.close();

   EllpackMatrix ellpack_matrix;
   file.open( file_name.data(), std::ios::in );
   if( ! file )
   {
      std::cerr << "Cannot open file " << file_name << "." << std::endl;
      return EXIT_FAILURE;
   }
   if( ! ellpack_matrix.readMtxFile( file ) )
      return EXIT_FAILURE;

   //dense_matrix.print( std::cout );
   //std::cout << "#####################" << std::endl;
   //ellpack_matrix.print( std::cout );
   
   if( dense_matrix.getRows() != ellpack_matrix.getRows() )
   {
      std::cerr << "Rows count is different: " << dense_matrix.getRows() << " and " << ellpack_matrix.getRows() << std::endl;
      return EXIT_FAILURE;
   }
   
   if( dense_matrix.getColumns() != ellpack_matrix.getColumns() )
   {
      std::cerr << "Columns count is different: " << dense_matrix.getColumns() << " and " << ellpack_matrix.getColumns() << std::endl;
      return EXIT_FAILURE;
   }

   for( int i = 0; i < dense_matrix.getRows(); i++ )
      for( int j = 0; j < dense_matrix.getColumns(); j++ )
         if( dense_matrix( i, j ) != ellpack_matrix.getElement( i, j ) )
         {
            std::cerr << "Matrices differ at ( " << i << ", " << j << "): " << dense_matrix( i, j ) << " and " << ellpack_matrix.getElement( i, j ) << "." << std::endl;
            return EXIT_FAILURE;
         }
   
   return 0;
}

