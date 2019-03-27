/* 
 * File:   Vector.h
 * Author: oberhuber
 *
 * Created on September 30, 2016, 4:30 PM
 */

#pragma once

#include <ostream>

class Vector
{
   public:
   
      Vector();
      
      Vector( const int size );
      
      void setSize( const int size );
      
      int getSize() const;
      
      double* getData();
      
      const double* getData() const;
      
      double& operator[]( const int index );
      
      const double& operator[]( const int index ) const;
      
      Vector& operator -= ( const Vector& b );
      
      void swap( Vector& v );
      
      const double maxNorm() const;
      
      const double l1Norm() const;
      
      const double l2Norm() const;
      
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
      
      bool readPGM( const char* fileName, int& width, int& height );
      
      void writePGM( const char* fileName, const int width, const int height );
      
      ~Vector();
      
   protected:
      
      double* data;
      
      int size;
};

std::ostream& operator << ( std::ostream& str, const Vector& v );

