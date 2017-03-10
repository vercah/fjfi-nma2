/* 
 * File:   SpeciesProblem.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 10:41 AM
 */

#ifndef SPECIESPROBLEM_H
#define SPECIESPROBLEM_H

#include<cmath>
#include<iostream>
#include<fstream>

class SpeciesProblem
{
   public:
      
      SpeciesProblem()
      : a( 1.0 ), b( 1.0 ), c( 1.0 ), d( 1.0 )
      {}
      
      const int getDegreesOfFreedom() { return 2; }
      
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
         
   protected:
      
      double a,b,c,d;
};


#endif /* SPECIESPROBLEM_H */

