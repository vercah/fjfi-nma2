#include "SIRProblem.h"

SIRProblem::SIRProblem()
{
   N = 1.0;
   nat = 1.0;
   m = 1.0;
   b = 1.0;
   c = 1.0;
   f = 1.0;
}

void SIRProblem::setParameters( const double& _N,
                                const double& _nat,
                                const double& _m,
                                const double& _b,
                                const double& _c,
                                const double& _f )
{
    N = _N;
    nat = _nat;
    m = _m;
    b = _b;
    c = _c;
    f = _f;
}

int SIRProblem::getDegreesOfFreedom()
{
   return 3;
}

void SIRProblem::getRightHandSide( const double& t, double* _sir, double* fsir )
{
   const double& s = _sir[ 0 ];
   const double& i = _sir[ 1 ];
   const double& r = _sir[ 2 ];
   fsir[ 0 ] = nat*(1-f)*N - (b*i*s)/N - m*s;
   fsir[ 1 ] = (b*i*s)/N - c*i - m*i;
   fsir[ 2 ] = c*i + nat*f*N - m*r;
}

bool SIRProblem::writeSolution( const double& t, int step, const double* sir )
{
   fstream file;
   if( step == 0 )
   {
      file.open( "sir.txt", fstream::out | fstream::trunc );
      if( !file ) return false;
      file << "t" << " " << "s" << " " << "i" << " " << "r" << endl;
   }
   else
   {
      file.open( "sir.txt", fstream::out | fstream::app );
      if( !file ) return false;
   }
   file << t << " " << sir[ 0 ] << " " << sir[ 1 ] << " " << sir[ 2 ] << endl;
   return true;
}
