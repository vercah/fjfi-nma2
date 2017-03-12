/* 
 * File:   NBodyProblem.h
 * Author: oberhuber
 *
 * Created on March 10, 2017, 2:55 PM
 */

#pragma once

#include<cmath>
#include<iostream>
#include<fstream>

class NBodyProblem
{
   public:
      
      NBodyProblem( int particlesCount, int dimensions = 2 )
      : dimensions( dimensions ), particlesCount( particlesCount ), particles( dimensions * particlesCount ), masses( particlesCount ), g( 9.81 )
      {}
      
      const int getDegreesOfFreedom() { return 2 * dimensions * particlesCount; }
      
      void setParameters()
      {
         
      }
      
      void getRightHandSide( const double& t, const double* _u, double* fu )
      {
         if( dimensions == 2 )
         {
            for( int i = 0; i < this->particlesCount; i++ )
            {
               const double& q_i_x = particles[ 2 * i ];
               const double& q_i_y = particles[ 2 * i + 1 ];
               double F_i( 0.0 );
               for( int j = 0; j < i; j++ )
               {  
                  const double& q_j_x = particles[ 2 * j ];
                  const double& q_j_y = particles[ 2 * j + 1 ];
                  const double q_ij_x = q_i_x - q_j_x;
                  const double q_ij_y = q_i_y - q_j_y;
                  double dist = q_ij_x * q_ij_x + q_ij_y * q_ij_y;
               }
            }
         }
         
         
         
         const double& x = _u[ 0 ];
         const double& y = _u[ 1 ];
         const double& z = _u[ 2 ];
         fu[ 0 ] = sigma * (y - x );
         fu[ 1 ] = rho * x - y - x * z;
         fu[ 2 ] = -beta * z + x * y;
         //std::cout << " t = " << t << " " << fu[ 0 ] << " " << fu[ 1 ] << std::endl;
      }
         
   protected:
      
      int dimensions, particlesCount;
      
      std::vector< double > particles, masses;
      
      double g;
};


