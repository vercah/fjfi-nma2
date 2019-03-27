/* 
 * File:   NBodyProblem.cpp
 * Author: oberhuber
 *
 * Created on March 10, 2017, 2:55 PM
 */

#include "NBodyProblem.h"

NBodyProblem::NBodyProblem( int _particlesCount, int _dimension )
{
   dimension = _dimension;
   particlesCount = _particlesCount;
   masses = new double[ particlesCount ];
   g = 9.81;
}

int NBodyProblem::getDegreesOfFreedom()
{ 
   return 2 * dimension * particlesCount;
}

void NBodyProblem::setParameters()
{

}

void NBodyProblem::setInitialCondition( double* u )
{
   if( dimension == 2 )
   {
      for( int i = 0; i < this->particlesCount; i++ )
      {
         /****
          * Initial velocity
          */
         u[ 2 * i ] = 0; //( double ) ( rand() % 100 ) / 1000.0 - 0.05;
         u[ 2 * i + 1 ] = 0; // ( double ) ( rand() % 100 ) / 1000.0 - 0.05;
         
         /****
          * Initial position
          */         
         u[ this->particlesCount + 2 * i ] = ( double ) ( rand() % 10000 ) / 100.0 - 50.0;
         u[ this->particlesCount + 2 * i + 1 ] = ( double ) ( rand() % 10000 ) / 100.0 - 50.0;
         
         /****
          * Particle mass
          */         
         this->masses[ i ] = ( double ) ( rand() % 100 ) / 100.0 + 1.0; //10; // * ( i + 1 );
      }
   }
}

void NBodyProblem::getRightHandSide( const double& t, double* _u, double* fu )
{
   const double epsilon = 1.0e-1;
   const int n = this->particlesCount;
   if( dimension == 2 )
   {
      for( int i = 0; i < n; i++ )
      {
         /****
          * Positions
          */         
         fu[ 2 * ( n + i ) ] = _u[ 2 * i ];
         fu[ 2 * ( n + i ) + 1 ] = _u[ 2 * i + 1 ];               
         
         /****
          * Velocities
          */         
         fu[ 2 * i ] = 0.0;
         fu[ 2 * i + 1 ] = 0.0;
         const double& q_i_x = _u[ 2 * ( n + i ) ];
         const double& q_i_y = _u[ 2 * ( n + i ) + 1 ];               
         for( int j = 0; j < n; j++ )
         {  
            if( i == j )
               continue;
            const double& q_j_x = _u[ 2 * ( n + j ) ];
            const double& q_j_y = _u[ 2 * ( n + j ) + 1 ];
            const double q_ij_x = q_i_x - q_j_x;
            const double q_ij_y = q_i_y - q_j_y;
            double dist = sqrt( q_ij_x * q_ij_x + q_ij_y * q_ij_y + epsilon );
            double coeff = this->g * this->masses[ j ] / ( dist * dist * dist );
            fu[ 2 * i ] += coeff * ( q_j_x - q_i_x );
            fu[ 2 * i + 1 ] += coeff * ( q_j_y - q_i_y );
         }
      }
   }
}

bool NBodyProblem::writeSolution( const double& t, int step, const double* u )      
{
   /****
    * Filename with step index
    */   
   std::stringstream str;
   str << "nbody-" << std::setw( 5 ) << std::setfill( '0' ) << step << ".txt";
   
   /****
    * Open file
    */   
   std::fstream file;
   file.open( str.str(), std::fstream::out | std::fstream::trunc );
   if( ! file )
   {
      std::cerr << "Unable to open the file " << str.str() << std::endl;
      return false;
   }
   
   /****
    * Write particles positions
    */   
   const int n = this->particlesCount;
   const int d = this->dimension;
   for( int i = 0; i < n; i++ )
   {
      for( int j = 0; j < d; j++ )
         file << u[ d * ( n +  i ) + j ] << " ";
      for( int j = 0; j < d; j++ )
         file << u[ d * ( n +  i ) + j ] + u[ d * i + j ] << " ";            
      file << std::endl;
   }
}

NBodyProblem::~NBodyProblem()
{
   if( masses )
      delete[] masses;
}
