#include "JacobiSolver.h"


JacobiSolver::JacobiSolver( Matrix& A,
                            Vector& b )
: A( A ), b( b )
{  
   assert( A.getRows() == b.getSize() &&
           A.getColumns() == b.getSize() );
}

bool JacobiSolver::solve( Vector& x, 
                          const int max_iterations,
                          const Real& convergence_residue,
                          int verbose )
{
   int iteration( 0 );
   Vector aux;
   aux.setSize( x.getSize() );
   while( iteration < max_iterations )
   {
      A.performJacobiIteration( b, x, aux );
      x.swap( aux );
      if( verbose )
         std::cout << "Iteration = " << iteration << " x = " << x << std::endl;
      iteration++;
      if( iteration % 10 == 0 )
      {
         A.vectorMultiplication( x, aux );
         aux -= b;
         residue = aux.l2Norm();
         if( residue < convergence_residue )
            return true;
      }      
   }
   return false;
}


