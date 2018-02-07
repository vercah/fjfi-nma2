#include "LorenzProblem.h"

LorenzProblem::LorenzProblem()
{
   sigma = 1.0;
   rho = 1.0;
   beta = 1.0;
}

void LorenzProblem::setParameters( const double& _sigma,
                                   const double& _rho,
                                   const double& _beta )
{
   sigma = _sigma;
   rho = _rho;
   beta = _beta;
}

int LorenzProblem::getDegreesOfFreedom()
{ 
   return 3; 
}

void LorenzProblem::getRightHandSide( const double& t, const double* _u, double* fu )
{
   const double& x = _u[ 0 ];
   const double& y = _u[ 1 ];
   const double& z = _u[ 2 ];
   fu[ 0 ] = sigma * (y - x );
   fu[ 1 ] = rho * x - y - x * z;
   fu[ 2 ] = -beta * z + x * y;
}

bool LorenzProblem::writeSolution( const double& t, int step, const double* u )
{
   fstream file;
   if( step == 0 )
   {
      /****
       * In the first step, we want to rewrite the file
       */
      file.open( "lorenz.txt", ios::out );
      if( !file ) return false;
   }
   else
   {
      /****
       * In later steps, we just append new time steps
       */
      file.open( "lorenz.txt", ios::out | ios::app );
      if( !file ) return false;            
   }
   file << u[ 0 ] << " " << u[ 1 ] << " " << u[ 2 ] << endl;
}
