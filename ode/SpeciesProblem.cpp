#include "SpeciesProblem.h"

SpeciesProblem::SpeciesProblem()
{
   a = 1.0;
   b = 1.0;
   c = 1.0;
   d = 1.0;
   e = 1.0;
   f = 1.0;
}

int SpeciesProblem::getDegreesOfFreedom()
{
   return 2;
}

void SpeciesProblem::setParameters( const double& _a,
                                    const double& _b,
                                    const double& _c,
                                    const double& _d,
                                    const double& _e,
                                    const double& _f )
{
   a = _a;
   b = _b;
   c = _c;
   d = _d;
   e = _e;
   f = _f;
}

void SpeciesProblem::getRightHandSide( const double& t, double* _u, double* fu )
{
   const double& u1 = _u[ 0 ];
   const double& u2 = _u[ 1 ];
   fu[ 0 ] =  a * u1 - c * u1 * u2 - e * u1 * u1 ;
   fu[ 1 ] =  b * u2 - d * u1 * u2 - f * u2 * u2 ;
}

bool SpeciesProblem::writeSolution( const double& t, int step, const double* u )
{
   fstream file;
   if( step == 0 )
   {
      /****
       * In the first step, we want to rewrite the file
       */
      file.open( "species.txt", fstream::out | fstream::trunc );
      if( ! file ) return false;
   }
   else
   {
      /****
       * In later steps, we just append new time steps
       */
      file.open( "species.txt", fstream::out | fstream::app );
      if( ! file ) return false;
   }
   file << t << " " << u[ 0 ] << " " << u[ 1 ] << endl;
   return true;
}

