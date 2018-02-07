/* 
 * File:   SpeciesProblem.h
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

class SpeciesProblem : public ODEProblem
{
   public:
      
      SpeciesProblem()
      {
         a = 1.0;
         b = 1.0;
         c = 1.0;
         d = 1.0;
      }
      
      int getDegreesOfFreedom() { return 2; }
      
      void setParameters( const double& a,
                          const double& b,
                          const double& c,
                          const double& d )
      {
         this->a = a;
         this->b = b;
         this->c = c;
         this->d = d;
      }
      
      void getRightHandSide( const double& t, const double* _u, double* fu )
      {
         const double& u1 = _u[ 0 ];
         const double& u2 = _u[ 1 ];
         fu[ 0 ] = u1 - a * u1 * u1 - c * u1 * u2;
         fu[ 1 ] = u2 - b * u2 * u2 + d * u1 * u2;
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
            file.open( "species.txt", ios::out );
            if( ! file ) return false;
         }
         else
         {
            /****
             * In later steps, we just append new time steps
             */
            file.open( "species.txt", ios::out | ios::app );
            if( ! file ) return false;            
         }
         file << t << " " << u[ 0 ] << " " << u[ 1 ] << endl;
      }
      
   protected:
      
      double a,b,c,d;
};