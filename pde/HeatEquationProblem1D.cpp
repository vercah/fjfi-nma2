/*
 * File:   HeatEquationProblem1D.cpp
 * Author: oberhuber
 *
 * Created on March 26, 2019, 2:55 PM
 */

#include <cstdlib>
#include "HeatEquationProblem1D.h"

HeatEquationProblem1D::HeatEquationProblem1D( int size )
{
   this->size = size;
   this->h = 1.0 / ( size - 1 );
}

int HeatEquationProblem1D::getDegreesOfFreedom()
{
   return this->size;
}

void HeatEquationProblem1D::setParameters()
{

}

void HeatEquationProblem1D::setInitialCondition( double* u )
{
   for( int i = 0; i < size; i++ )
   {
      double x = i * h;
      // Step function
      u[ i ] = ( x > 0.4 && x < 0.6 ) ? 1.0 : 0.0;

      // Noise salt-pepper
      //u[ i ] = rand() % 20 - 10;

      // Step function with Gaussian noise
      /*u[ i ] = 0.0;
      for( int j = 0; j < 12; j++ )
         u[ i ] += 1.0 / 100.0 * ( double ) ( rand() % 20 - 10 );
      u[ i ] /= 12.0;
      u[ i ] += ( double ) ( ( x > 0.4 && x < 0.6 ) ? 1.0 : 0.0 );*/
   }
}

void HeatEquationProblem1D::getRightHandSide( const double& t, double* u, double* fu )
{
   /***
    * Zero Dirichlet boundary conditions
    */
   u[ 0 ] = 0.0;
   u[ size - 1 ] = 0.0;
   fu[ 0 ] = 0.0;
   fu[ size -1 ] = 0.0;

   /***
    * Evaluate the Laplace operator
    */
   const double h_sqr = h * h;
   for( int i = 1; i < size - 1; i++ )
      fu[ i ] = ( u[ i - 1 ] - 2.0 * u[ i ] + u[ i + 1 ] ) / h_sqr;
}

bool HeatEquationProblem1D::writeSolution( const double& t, int step, const double* u )
{
   /****
    * Filename with step index
    */
   std::stringstream str;
   str << "heat-equation-" << std::setw( 5 ) << std::setfill( '0' ) << step << ".txt";

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

HeatEquationProblem1D::~HeatEquationProblem1D()
{
}
