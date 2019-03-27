#include "HyperbolicProblem.h"

HyperbolicProblem::HyperbolicProblem()
{ 
   this->epsilon = 1.0;
}

int HyperbolicProblem::getDegreesOfFreedom()
{ 
   return 2;
}

void HyperbolicProblem::setEpsilon( const double& eps )
{
   this->epsilon = eps;
}

void HyperbolicProblem::getRightHandSide( const double& t, double* _u, double* fu )
{
   const double& u1 = _u[ 0 ];
   const double& u2 = _u[ 1 ];
   fu[ 0 ] = u2;
   fu[ 1 ] = -u1 - this->epsilon * u1 * u1 * u2;
   //std::cout << " t = " << t << " " << fu[ 0 ] << " " << fu[ 1 ] << std::endl;
}

bool HyperbolicProblem::writeSolution( const double& t, int step, const double* u )
{
   fstream file;
   if( step == 0 )
   {
      /****
       * In the first step, we want to rewrite the file
       */
      file.open( "hyperbolic.txt", fstream::out | fstream::trunc );
      if( file ) return false;
   }
   else
   {
      /****
       * In later steps, we just append new time steps
       */
      file.open( "hyperbolic.txt", fstream::out | fstream::app );
      if( ! file ) return false;            
   }
   file << t << " " << u[ 0 ] << " " << u[ 1 ] << endl;
}


