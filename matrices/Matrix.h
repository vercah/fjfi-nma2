/* 
 * File:   Matrix.h
 * Author: oberhuber
 *
 * Created on September 30, 2016, 11:57 AM
 */

#pragma once

#include "../Vector.h"
#include "../real.h"

class Matrix
{
   public:
      
      virtual void vectorMultiplication( const Vector& in_vector,
                                         Vector& out_vector ) const = 0;
   
};

