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
   return sizeX * sizeY;
}

void HeatEquationProblem2D::setParameters()
{

}

void HeatEquationProblem2D::setInitialCondition( double* u )
{
   for (int i = 0; i < sizeX; i++){
      const double x = i * hx;

      for (int j = 0; j < sizeY; j++){
         const double y = j * hy;

         // plane above

         //u[i + sizeX * j] = (x > 0.3 && x < 0.7 && y > 0.3 && y < 0.7) ? 1.0 : 0.0;

         // Random

         u[i + sizeX * j] = rand() % 10 - 4;
      }
   }

}

void HeatEquationProblem2D::getRightHandSide( const double& t, double* u, double* fu )
{
   /***
    * Zero Dirichlet boundary conditions
    */
   for (int i = 0; i < sizeX * sizeY; i++){
      if (i < sizeX || i > sizeX * sizeY - sizeX || i % sizeX == 0 || i % sizeX == sizeX - 1)
      {
         u[i]  = 0;
         fu[i] = 0;
      }
   }
   /***
    * Evaluate the Laplace operator
    */
    for (int i = sizeX; i < sizeX * (sizeY - 1); i++){
      if (i % sizeX != 0 && i % sizeX != sizeX - 1)
      {
         fu[i] = (u[i-1]-2.0*u[i]+u[i+1])/(hx*hx)+(u[i-sizeX]-2.0*u[i]+u[i+sizeX])/(hy*hy);
      }
   }
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
