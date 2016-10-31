/* 
 * File:   thomas-solver.cpp
 * Author: oberhuber
 *
 * Created on October 20, 2016, 4:25 PM
 */

#include <cstdlib>
#include "../CommandLineParser.h"
#include "../matrices/DenseMatrix.h"
#include "../matrices/TridiagonalMatrix.h"
#include "GEM.h"
#include "../Timer.h"
#include "ThomasAlgorithm.h"

using namespace std;

int main( int argc, char* argv[] )
{
   CommandLineParser parser( argc, argv );
   
   int n( 100 );
   if( parser.cmdOptionExists( "--size" ) )
      n = std::stoi( parser.getCmdOption( "--size" ) );
   
   bool pivoting( false );
   if( parser.cmdOptionExists( "--pivoting" ) )
   {
      std::string pivoting_str = parser.getCmdOption( "--pivoting" );  
      if( pivoting_str == "yes" )
         pivoting = true;
   }
   int verbose( 0 );
   if( parser.cmdOptionExists( "--verbose" ) )
      verbose = std::stoi( parser.getCmdOption( "--verbose" ) );
   
   DenseMatrix dense_matrix( n, n );
      for( int i = 0; i < n; i++ )
         for( int j = 0; j < n; j++ )
            dense_matrix.setElement( i, j, 0.0 );
      
   TridiagonalMatrix tridiagonal_matrix( n, n );
   for( int k = 0; k < n; k++ )
   {
      dense_matrix.setElement( k, k, 2.5 );
      tridiagonal_matrix.setElement( k, k, 2.5 );
      if( k > 1 )
      {
         
         dense_matrix.setElement( k, k - 1, -1 );
         tridiagonal_matrix.setElement( k, k - 1, -1 );
      }
      if( k < n - 1 )
      {
         dense_matrix.setElement( k, k + 1, -1 );
         tridiagonal_matrix.setElement( k, k + 1, -1 );
      }
   }
   
   Vector x, b;   
   x.setSize( n );
   b.setSize( n );
   for( int i = 0; i < n; i++ )
      x[ i ] = 1.0;
   std::cout << "Multiplying matrix-vector..." << std::endl;
   tridiagonal_matrix.vectorMultiplication( x, b );
   for( int i = 0; i < n; i++ )
      x[ i ] = 0.0;
   
   GEM gem( dense_matrix, b );   
   std::cout << "Solving the system using GEM..." << std::endl;
   Timer timer;
   timer.reset();
   timer.start();
   if( pivoting )
      gem.solveWithPivoting( x, verbose );
   else
      gem.solve( x, verbose );
   timer.stop();
   //std::cout << "The result is [ " << x << " ]." << std::endl;
   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;
   
   ThomasAlgorithm thomas( tridiagonal_matrix, b );   
   std::cout << "Solving the system using the Thomas Algorithm..." << std::endl;
   timer.reset();
   timer.start();
   thomas.solve( x, verbose );
   timer.stop();
   //std::cout << "The result is [ " << x << " ]." << std::endl;
   std::cout << "Computation took " << timer.getTime() << " seconds." << std::endl;
   
   
   return 0;
}

