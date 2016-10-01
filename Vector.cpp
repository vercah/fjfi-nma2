/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Vector.h"

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

std::ostream& operator << ( std::ostream& str, const Vector& v )
{
   for( int i = 0; i < v.getSize() - 1; i++ )
      str << v[ i ] << ", ";
   str << v[ v.getSize() - 1 ];
   return str;
}
