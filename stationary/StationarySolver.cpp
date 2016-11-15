#include "StationarySolver.h"
#include <assert.h>
#include <iostream>

StationarySolver::StationarySolver( Matrix& A,
                                    Vector& b )
: A( A ), b( b )
{  
   assert( A.getRows() == b.getSize() &&
           A.getColumns() == b.getSize() );
}

bool StationarySolver::solve( Vector& x, 
                              const int max_iterations,
                              const Real& convergence_residue,
                              const std::string& method,
                              const Real& relaxation,
                              int verbose )
{
   int iteration( 0 );
   Vector aux;
   aux.setSize( x.getSize() );
   while( iteration < max_iterations )
   {
      if( method == "richardson" )
         A.performRichardsonIteration( b, x, aux, relaxation );
      if( method == "jacobi")
         A.performJacobiIteration( b, x, aux, relaxation );
      if( method == "gauss-seidel")
         A.performSORIteration( b, x, 1.0 );
      if( method == "sor")
         A.performSORIteration( b, x, relaxation );
      
      x.swap( aux );
      if( verbose )
         std::cout << "Iteration = " << iteration << " x = " << x << std::endl;
      iteration++;
      if( iteration % 10 == 0 )
      {
         A.vectorMultiplication( x, aux );
         aux -= b;
         const Real residue = aux.l2Norm();
         std::cout << "ITER. " << iteration << " L2-RES. " << residue << std::endl;
         if( residue <= convergence_residue )
            return true;
      }      
   }
   return false;
}


