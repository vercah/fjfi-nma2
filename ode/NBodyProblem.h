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
      : dimensions( dimensions ), particlesCount( particlesCount ), masses( particlesCount ), g( 9.81 )
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
               const double& q_i_x = _u[ this->partriclesCount + 2 * i ];
               const double& q_i_y = _u[ this->partriclesCount + 2 * i + 1 ];
               fu[ 2 * i ] = 0.0;
               fu[ 2 * i + 1 ] = 0.0;
               for( int j = 0; j < this->particlesCount; j++ )
               {  
                  if( i == j )
                     continue;
                  const double& q_j_x = _u[ this->partriclesCount + 2 * j ];
                  const double& q_j_y = _u[ this->partriclesCount + 2 * j + 1 ];
                  const double q_ij_x = q_i_x - q_j_x;
                  const double q_ij_y = q_i_y - q_j_y;
                  double dist = sqrt( q_ij_x * q_ij_x + q_ij_y * q_ij_y );
                  double coeff = this->g * this->masses[ j ] / ( dist * dist * dist );
                  fu[ 2 * i ] += coeff * ( q_j_x - q_i_x );
                  fu[ 2 * i + 1 ] += coeff * ( q_j_y - q_i_y );
               }
               fu[ this->partriclesCount + 2 * i ] = _u[ 2 * i ];
               fu[ this->partriclesCount + 2 * i + 1 ] = _u[ 2 * i + 1 ];
            }
         }
      }
         
   protected:
      
      int dimensions, particlesCount;
      
      std::vector< double > masses;
      
      double g;
};


