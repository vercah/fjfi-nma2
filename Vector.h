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
   
      void setSize( const int size );
      
      int getSize() const;
      
      Real& operator[]( const int index );
      
      const Real& operator[]( const int index ) const;
      
      Vector& operator -= ( const Vector& b );
      
      void swap( Vector& v );
      
      const Real maxNorm() const;
      
      const Real l1Norm() const;
      
      const Real l2Norm() const;
      
      
      
   protected:
      
      std::vector< Real > data;
      
      int size;
};

std::ostream& operator << ( std::ostream& str, const Vector& v );

