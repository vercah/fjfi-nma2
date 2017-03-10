#include "PowerMethod.h"
#include "../stationary/StationarySolver.h"
#include <iostream>
#include <cmath>

PowerMethod::PowerMethod( const Matrix& A )
:  A( A ), max_iterations( 100 ), convergence_residue( 1.0e-8 )
{
}

void PowerMethod::setMaxIterations( const int max_iterations )
{
   this->max_iterations = max_iterations;
}

void PowerMethod::setConvergenceResidue( const Real& convergence_residue )
{
   this->convergence_residue = convergence_residue;
}

bool PowerMethod::getEigenvalue( Vector& x, Real& lambda, bool smallest, int verbose ) const
{
   int iteration( 0 );
   int norm_index( 0 );
   Real rho, residue( this->convergence_residue + 1.0 );
   Vector y, r;
   y.setSize( x.getSize() );
   r.setSize( x.getSize() );
   while( iteration < this->max_iterations )
   {
      if( smallest )
      {
         StationarySolver solver( A, x );
         solver.setMaxIterations( 10 );
         solver.setConvergenceResidue( 1.0e-6 );
         solver.solve( y, "sor" );
      }
      else
         A.vectorMultiplication( x, y );
      
      int aux( 0 );
      for( int i = 0; i < y.getSize(); i++ )
         if( std::fabs( y[ aux ] ) < std::fabs( y[ i ] ) )
            aux = i;     
      
      if( smallest )
         rho = x[ aux ] / y[ aux ];
      else
         rho = y[ aux ] / x[ aux ];
        
      Real norm_y = y.l2Norm();
      if( norm_y == 0.0 )
      {
         std::cerr << "Zero vector appeared!" << std::endl;
         return false;
      }
      for( int i = 0; i < x.getSize(); i++ )
         x[ i ] = y[ i ] / norm_y;
      if( iteration % 10 == 0 )
      {
         A.getEigenvalueResidue( x, rho, r );
         residue = r.l2Norm();
         std::cout << "ITER. " << iteration << " L2-RES. " << residue << " -> lambda = " << rho << std::endl;
      }
      if( residue < this->convergence_residue )
      {
         lambda = rho;
         return true;
      }
      iteration++;
   }
   return false;
}

