#include "RiccatiProblem.h"

RiccatiProblem::RiccatiProblem()
{
   l1Error = 0.0;
   l2Error = 0.0;
   maxError = 0.0;
}

int RiccatiProblem::getDegreesOfFreedom()
{ 
   return 1; 
}

void RiccatiProblem::getRightHandSide( const double& t, double* _u, double* fu )
{
   const double& u = _u[ 0 ];
   fu[ 0 ] = pow( t, -4.0 ) * exp( t ) + u + 2.0 * exp( -t ) * u * u;
}

double RiccatiProblem::getExactSolution( const double& t ,
                                         const double& c )
{
   const double sqrt_2 = sqrt( 2.0 );
   return exp( t ) * ( 1.0 / ( sqrt_2 * t * t ) * 
                       tan( sqrt_2 * ( c - 1.0 / t ) ) - 1.0 / ( 2.0 * t ) );
}

bool RiccatiProblem::writeExactSolution( const char*  fileName, 
                                         const double& initialTime,
                                         const double& finalTime,
                                         const double& timeStep,
                                         const double& c )
{
   std::fstream file;
   file.open( fileName, std::ios::out );
   double t = initialTime;
   while( t < finalTime )
   {
      file << t << " " << this->getExactSolution( t, c ) << std::endl;
      t = std::min( t + timeStep, finalTime );
   }
}

bool RiccatiProblem::writeSolution( const double& t, int step, const double* _u )
{
   const double& u = _u[ 0 ];
   fstream file;
   if( step == 0 )
   {
      /****
       * In the first step, we want to rewrite the file
       */
      file.open( "riccati.txt", ios::out );
      if( !file ) return false;
   }
   else
   {
      /****
       * In later steps, we just append new time steps
       */
      file.open( "riccati.txt", ios::out | ios::app );
      if( !file ) return false;            
   }
   file << t << " " << u << endl;
   
   /****
    * Evaluate errors of the approximation
    */   	    
   const double diff = fabs( getExactSolution( t ) - u );
   l1Error += diff;
   l2Error += diff * diff;
   maxError = std::max( maxError, diff );
}

double RiccatiProblem::getL1Error( const double timeStep )
{
   return timeStep * l1Error;
}

double RiccatiProblem::getL2Error( const double timeStep )
{
   return sqrt( timeStep * l2Error );
}

double RiccatiProblem::getMaxError()
{
   return maxError;
}


