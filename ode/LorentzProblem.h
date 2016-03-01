/* 
 * File:   LorentzProblem.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#ifndef LORENTZPROBLEM_H
#define LORENTZPROBLEM_H

#include<cmath>
#include<iostream>
#include<fstream>

class LorentzProblem
{
   public:
      
      LorentzProblem()
      : sigma( 1.0 ), rho( 1.0 ), beta( 1.0 )
      {}
      
      const int getDegreesOfFreedom() { return 3; }
      
      void setParameters( const double& sigma,
                          const double& rho,
                          const double& beta )
      {
         this->sigma = sigma;
         this->rho = rho;
         this->beta = beta;
      }
      
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
         
   protected:
      
      double sigma, rho, beta;
};


#endif /* LORENTZPROBLEM_H */

