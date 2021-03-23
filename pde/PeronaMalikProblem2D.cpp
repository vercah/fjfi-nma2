/*
 * File:   PeronaMalikProblem2D.cpp
 * Author: oberhuber
 *
 * Created on March 27, 2019, 2:55 PM
 */

#include <cstdlib>
#include "PeronaMalikProblem2D.h"

PeronaMalikProblem2D::PeronaMalikProblem2D( int size )
{
   this->size = size;
   this->h = 1.0 / size;
   this->p = new double[ size ];
}

int PeronaMalikProblem2D::getDegreesOfFreedom()
{
   return this->size;
}

void PeronaMalikProblem2D::setParameters()
{

}

void PeronaMalikProblem2D::setInitialCondition( double* u )
{
   for( int i = 0; i < size; i++ )
   {
      double x = i * h;
      //u[ i ] = ( x > 0.4 && x < 0.6 ) ? 1.0 : 0.0;
      //u[ i ] = rand() % 20 - 10;

      // Step function with noise
      u[ i ] = 0.0;
      for( int j = 0; j < 12; j++ )
         u[ i ] += 1.0 / 100.0 * ( double ) ( rand() % 20 - 10 );
      u[ i ] /= 12.0;
      u[ i ] += ( double ) ( ( x > 0.4 && x < 0.6 ) ? 1.0 : 0.0 );
   }
}

void PeronaMalikProblem2D::getRightHandSide( const double& t, double* u, double* fu )
{
   /***
    * Dirichlet boundary conditions
    */
   //u[ 0 ] = 0.0;
   //u[ size - 1 ] = 0.0;
   fu[ 0 ] = 0.0;
   fu[ size -1 ] = 0.0;

   /***
    * Evaluate the Laplace operator
    */
   const double h_sqr = h * h;
   for( int i = 1; i < size - 1; i++ )
   {
      const double u_x = ( u[ i ] - u[ i -1 ] ) / h;
      p[ i ] = 1.0 / ( 1.0 + fabs( u_x ) / this->K_sqr );
   }
   for( int i = 1; i < size - 1; i++ )
      fu[ i ] = ( p[ i ] * u[ i - 1 ] - ( p[ i ] + p[ i + 1 ] ) * u[ i ] + p[ i + 1 ] * u[ i + 1 ] ) / h_sqr;
}

bool PeronaMalikProblem2D::writeSolution( const double& t, int step, const double* u )
{
   /****
    * Filename with step index
    */
   std::stringstream str;
   str << "perona-malik-" << std::setw( 5 ) << std::setfill( '0' ) << step << ".txt";

   /****
    * Open file
    */
   std::fstream file;
   file.open( str.str(), std::fstream::out | std::fstream::trunc );
   if( ! file )
   {
      std::cerr << "Unable to open the file " << str.str() << std::endl;
      return false;
   }

   /****
    * Write solution
    */
   for( int i = 0; i < size; i++ )
   {
      file << u[ i ] << " ";
      file << std::endl;
   }
   return true;
}

PeronaMalikProblem2D::~PeronaMalikProblem2D()
{
   delete[] p;
}
