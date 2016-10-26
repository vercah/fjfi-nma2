/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Vector.h"
#include <cmath>

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

std::ostream& operator << ( std::ostream& str, const Vector& v )
{
   for( int i = 0; i < v.getSize() - 1; i++ )
      str << v[ i ] << ", ";
   str << v[ v.getSize() - 1 ];
   return str;
}

