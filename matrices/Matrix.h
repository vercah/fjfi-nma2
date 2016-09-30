/* 
 * File:   Matrix.h
 * Author: oberhuber
 *
 * Created on September 30, 2016, 11:57 AM
 */

#pragma once

#include "../real.h"

class Matrix
{
   public:
      
      virtual void vectorMultiplication( const std::vector< Real >& in_vector,
                                         std::vector< Real >& out_vector ) const = 0;
   
};

