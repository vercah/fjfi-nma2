/* 
 * File:   ThomasAlgorithm.h
 * Author: oberhuber
 *
 * Created on October 17, 2016, 8:01 PM
 */

#pragma once

#include "../matrices/TridiagonalMatrix.h"

class ThomasAlgorithm
{
   public:
      ThomasAlgorithm( TridiagonalMatrix& A,
                       Vector& b );
      
      bool solve( Vector& x, int verbose = 0 );      
      
   protected:
      
      void print( std::ostream& str = std::cout ) const;
      
      TridiagonalMatrix& A;
      
      Vector& b;
   
};

