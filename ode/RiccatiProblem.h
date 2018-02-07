/* 
 * File:   RiccatiProblem.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>
#include "ODEProblem.h"

using namespace std;

class RiccatiProblem : public ODEProblem
{
   public:
      
      int getDegreesOfFreedom() { return 1; }
      
      void getRightHandSide( const double& t, const double* _u, double* fu )
      {
         const double& u = _u[ 0 ];
         fu[ 0 ] = pow( t, -4.0 ) * exp( t ) + u + 2.0 * exp( -t ) * u * u;
         //std::cout << " t = " << t << " " << fu[ 0 ] << " ";
      }
      
      double getExactSolution( const double& t ,
                               const double& c = 1.0 )
      {
         return exp( t ) * ( 1.0 / ( sqrt( 2.0 ) * t * t ) * tan( sqrt( 2.0 ) * ( c - 1.0 / t ) ) - 1.0 / ( 2.0 * t ) );
      }
      
      bool writeExactSolution( const char*  fileName, 
                               const double& initialTime,
                               const double& finalTime,
                               const double& timeStep,
                               const double& c = 1.0 )
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
      
      bool writeSolution( const double& t, int step, const double* u )
      {
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
         file << t << " " << u[ 0 ] << endl;
      }
};

