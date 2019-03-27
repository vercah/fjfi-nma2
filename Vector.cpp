/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include "Vector.h"

Vector::Vector() {};

Vector::Vector( const int size )
{
   this->setSize( size );
};

void Vector::setSize( const int size )
{
   this->data.resize( size );
   this->size = size;
}

int Vector::getSize() const
{
   return this->size;
}

Real& Vector::operator[]( const int index )
{
   return this->data[ index ];
}

const Real& Vector::operator[]( const int index ) const
{
   return this->data[ index ];
}

Vector& Vector::operator -= ( const Vector& b )
{
   for( int i = 0; i < this->size; i++ )
      this->data[ i ] -= b[ i ];
}

void Vector::swap( Vector& v )
{
   this->data.swap( v.data );
}

const Real Vector::maxNorm() const
{
   Real result( 0.0 );
   for( int i = 0; i < this->size; i++ )
      if( result < fabs( this->data[ i ] ) )
         result = fabs( this->data[ i ] );
   return result;
}

const Real Vector::l1Norm() const
{
   Real result( 0.0 );
   for( int i = 0; i < this->size; i++ )
      result += fabs( this->data[ i ] );
   return result;
}

const Real Vector::l2Norm() const
{
   Real result( 0.0 );
   for( int i = 0; i < this->size; i++ )
   {
      const Real aux = fabs( this->data[ i ] );
      result += aux * aux;
   }
   return sqrt( result );
}

void Vector::writeGnuplot1D( std::ostream& str, const double& h, const double& origin ) const
{
   for( int i = 0; i< this->getSize(); i++ )
      str << origin + i * h << " " << this->operator []( i ) << std::endl;
   str<< std::endl;
}

void Vector::writeGnuplot2D( std::ostream& str,
                             const int size_x,
                             const int size_y,
                             const double& h_x,
                             const double& h_y,
                             const double& origin_x,
                             const double& origin_y ) const
{
   for( int j = 0; j < size_x; j++ )
      for( int i = 0; i < size_y; i++ )
         str << origin_x + i * h_x << " "
             << origin_y + j * h_y << " "
             << this->operator[]( j * size_x + i )
             << std::endl;
   str << std::endl;
}

bool Vector::readPGM( const char* fileName, int& width, int& height )
{
   std::fstream file;
   file.open( fileName, std::ios::in );
   
   /***
    * Read header
    */
   std::string magicNumber;
   file >> magicNumber;
   if( magicNumber != "P2" && magicNumber != "P5" )
   {
      std::cerr << "Unsupported format in file " << fileName << ". Only PGM format is supported." << std::endl;
      return false;
   }
   bool binary = ( magicNumber == "P5" );
   
   /****
    * Skip comments and empty lines
    */
   char character;
   file.get(character);
   while ( ! file.eof() and ( character == ' ' || character == '\t' || character == '\r' || character == '\n') )
   {
      file.get(character);
      if ( character == '#' )
         while( ! file.eof() && ( character != '\n' ) )
	    file.get( character );
   }
   file.unget();
 
   /***
    * Read resolution
    */
   int maxColors;
   file >> width >> height >> maxColors;
 
   /****
    * Allocate data
    */
   this->data.resize( width * height );

   /****
    * Read image
    */
   for( int i = 0; i < height; i ++ )
      for( int j = 0; j < width; j ++ )
      {
         int col;
         unsigned char col_aux;
         if( binary )
         {
           file >> col_aux;
           col = (int)col_aux;
         }
         else file >> col;
         this->data[ i * width + j ] = ( double ) col / ( double ) maxColors;
      }
   return true;
}

void Vector::writePGM( const char* fileName, const int width, const int height )
{
   std::fstream file;
   file.open( fileName, std::ios::out );
   
   file << "P5\n";
   file << "# This file was generated at FJFI\n";
   file << width << ' '<< height << '\n' << "255\n";
   
   for( int i = 0; i < height; i ++ )
   {
      for( int j = 0; j < width; j ++ )
      {
         unsigned char color = 255 * data[ i * width + j ];
         file << color;
      }      
      file << '\n';
   }
}

std::ostream& operator << ( std::ostream& str, const Vector& v )
{
   for( int i = 0; i < v.getSize() - 1; i++ )
      str << v[ i ] << ", ";
   str << v[ v.getSize() - 1 ];
   return str;
}

