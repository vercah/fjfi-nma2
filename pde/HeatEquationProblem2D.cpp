/*
 * File:   HeatEquationProblem2D.cpp
 * Author: oberhuber
 *
 * Created on March 26, 2019, 2:55 PM
 */

#include <cstdlib>
#include "HeatEquationProblem2D.h"

HeatEquationProblem2D::HeatEquationProblem2D( int sizeX, int sizeY )
{
   this->sizeX = sizeX;
   this->sizeY = sizeY;
   this->hx = 1.0 / ( sizeX - 1 );
   this->hy = 1.0 / ( sizeY - 1 );
}

int HeatEquationProblem2D::getDegreesOfFreedom()
{
   return -1;  // TODO: Fix with correct DOFs
}

void HeatEquationProblem2D::setParameters()
{

}

void HeatEquationProblem2D::setInitialCondition( double* u )
{
}

void HeatEquationProblem2D::getRightHandSide( const double& t, double* u, double* fu )
{
   /***
    * Zero Dirichlet boundary conditions
    */

   /***
    * Evaluate the Laplace operator
    */
}

bool HeatEquationProblem2D::writeSolution( const double& t, int step, const double* u )
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
   for( int j = 0; j < sizeY; j++ )
   {
      for( int i = 0; i < sizeX; i++ )
      {
         file << i * hx << " " << j * hy << " " << u[ j * sizeX + i ];
         file << std::endl;
      }
      file << std::endl;
   }
   return true;
}

HeatEquationProblem2D::~HeatEquationProblem2D()
{
}
