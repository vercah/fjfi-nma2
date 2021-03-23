/*
 * File:   TransportEquationProblem1D.cpp
 * Author: oberhuber
 *
 * Created on March 26, 2019, 2:55 PM
 */

#include <cstdlib>
#include <cmath>
#include "TransportEquationProblem1D.h"

TransportEquationProblem1D::TransportEquationProblem1D( int size )
{
   this->size = size;
   this->h = 10.0 / size;
}

int TransportEquationProblem1D::getDegreesOfFreedom()
{
   return this->size;
}

void TransportEquationProblem1D::setAlpha( const double& _alpha )
{
   this->alpha = _alpha;
}

void TransportEquationProblem1D::setLFEpsilon( const double& eps )
{
   this->lfEpsilon = eps;
}

void TransportEquationProblem1D::setTau( const double& tau )
{
   this->tau = tau;
}


void TransportEquationProblem1D::setScheme( Scheme s )
{
   this->scheme = s;
}

void TransportEquationProblem1D::setInitialCondition( double* u )
{
   for( int i = 0; i < size; i++ )
   {
      double x = i * h;
      // Atan function
      //u[ i ] = 0.1 * std::atan( 4.0 * M_PI * ( x - 5.0 ) );
      // Step function
      u[ i ] = ( x > 5.0 ) ? 0.1 : -0.1;
      // Opposite step function
      //u[ i ] = ( x > 5.0 ) ? -0.1 : 0.1;
   }
}

void TransportEquationProblem1D::getRightHandSide( const double& t, double* u, double* fu )
{
   /***
    * Dirichlet boundary conditions
    */
   if( this->alpha < 0 )
      u[ 0 ] = u[ 1 ];
   else
      u[ size - 1 ] =  u[ size - 2 ];
   fu[ 0 ] = 0.0;
   fu[ size -1 ] = 0.0;

   /***
    * Evaluate the Laplace operator
    */
   const double h_sqr = h * h;
   for( int i = 1; i < size - 1; i++ )
   {
      switch( this->scheme )
      {
         case FDM:
            fu[ i ] = -this->alpha * ( u[ i + 1 ] - u[ i - 1 ] ) / ( 2.0 * h );
            break;
         case LaxFriedrichs:
            fu[ i ] = -this->alpha * ( u[ i + 1 ] - u[ i - 1 ] ) / ( 2.0 * h ) + this->lfEpsilon * ( u[ i - 1 ] - 2 * u[ i ] + u[ i + 1 ] ) / ( 2.0 * this->tau );
            break;
         case Upwind:
            if( this->alpha > 0 )
               fu[ i ] = -this->alpha * ( u[ i ] - u[ i - 1 ] ) / h;
            else
               fu[ i ] = -this->alpha * ( u[ i + 1 ] - u[ i ] ) / h;
      }
   }
}

bool TransportEquationProblem1D::writeSolution( const double& t, int step, const double* u )
{
   /****
    * Filename with step index
    */
   std::stringstream str;
   str << "transport-equation-" << std::setw( 5 ) << std::setfill( '0' ) << step << ".txt";

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

TransportEquationProblem1D::~TransportEquationProblem1D()
{
}
