/* 
 * File:   LorenzProblem.h
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

class LorenzProblem : public ODEProblem
{
   public:
      
      LorenzProblem()
      : sigma( 1.0 ), rho( 1.0 ), beta( 1.0 )
      {}
      
      void setParameters( const double& sigma,
                          const double& rho,
                          const double& beta )
      {
         this->sigma = sigma;
         this->rho = rho;
         this->beta = beta;
      }
      
      int getDegreesOfFreedom() { return 3; }      
      
      void getRightHandSide( const double& t, const double* _u, double* fu )
      {
         const double& x = _u[ 0 ];
         const double& y = _u[ 1 ];
         const double& z = _u[ 2 ];
         fu[ 0 ] = sigma * (y - x );
         fu[ 1 ] = rho * x - y - x * z;
         fu[ 2 ] = -beta * z + x * y;
         //std::cout << " t = " << t << " " << fu[ 0 ] << " " << fu[ 1 ] << std::endl;
      }
      
      bool writeSolution( const double& t, int step, const double* u )
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
         
   protected:
      
      double sigma, rho, beta;
};

