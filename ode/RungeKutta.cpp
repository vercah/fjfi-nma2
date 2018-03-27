#include "RungeKutta.h"

RungeKutta::RungeKutta()
{
   /***
    * Set all pointers to zero by default
    */
   k1 = 0;
   // TODO: add other k-variables here
}

bool RungeKutta::setup( const int degreesOfFreedom )
{
   /****
    * Allocate memory for k-variables
    */
   k1 = new double[ degreesOfFreedom ];
   if( ! k1 )
      return false;
   return true;
}

bool RungeKutta::solve( const double integrationTimeStep,
                   const double stopTime,
                   double* time,
                   ODEProblem* problem,
                   double* u )
{
   const int dofs = problem->getDegreesOfFreedom();         
   double tau = std::min( integrationTimeStep, stopTime - *time );
   while( *time < stopTime )
   {
      /****
       * Evaluate k1 = f( t, u )
       */
     problem->getRightHandSide( *time, u, k1 );
     
     
     /****
      * Update solution u using k-variables
      */
     for( int i = 0; i < dofs; i++ )
        u[ i ] +=  tau * k1[ i ];
      *time += tau;
      tau = std::min( integrationTimeStep, stopTime - *time );
   }
   return true;
}

RungeKutta::~RungeKutta()
{
   /****
    * Free allocated memory
    */
   if( k1 ) delete[] k1;
}
