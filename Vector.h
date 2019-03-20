/* 
 * File:   Vector.h
 * Author: oberhuber
 *
 * Created on September 30, 2016, 4:30 PM
 */

#pragma once

#include <vector>
#include <ostream>
#include "real.h"


class Vector
{
   public:
   
      Vector();
      
      Vector( const int size );
      
      void setSize( const int size );
      
      int getSize() const;
      
      Real& operator[]( const int index );
      
      const Real& operator[]( const int index ) const;
      
      Vector& operator -= ( const Vector& b );
      
      void swap( Vector& v );
      
      const Real maxNorm() const;
      
      const Real l1Norm() const;
      
      const Real l2Norm() const;
      
      void writeGnuplot1D( std::ostream& str,
                           const double& h,
                           const double& origin = 0 ) const;
      
      void writeGnuplot2D( std::ostream& str,
                           const int xSize,
                           const int ySize,
                           const double& h_x,
                           const double& h_y,
                           const double& origin_x = 0,
                           const double& origin_y = 0 ) const;
      
   protected:
      
      std::vector< Real > data;
      
      int size;
};

std::ostream& operator << ( std::ostream& str, const Vector& v );

