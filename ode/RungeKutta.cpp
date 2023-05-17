#include "RungeKutta.h"

RungeKutta::RungeKutta()
{
   /***
    * Set all pointers to zero by default
    */
   k1 = 0;
   k2 = 0;
}

bool RungeKutta::setup( const int degreesOfFreedom )
{
   /****
    * Allocate memory for k-variables
    */
   k1 = new double[ degreesOfFreedom ];
   k2 = new double[ degreesOfFreedom ];
   if( !k1 || !k2 )
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
       * Runge-Kutta method of second order with parameters p1=0, p2=1, alpha2=beta21=0.5
       */
     problem->getRightHandSide( *time, u, k1 );

     double* tmp = new double[dofs];
     for (int i = 0; i < dofs; i++) {
        tmp[i] = u[i] + (0.5)*tau*k1[i];
     }
     problem->getRightHandSide( *time + tau*0.5, tmp, k2 );
     delete[] tmp;

     /****
      * Update solution u using k-variables
      */
     for( int i = 0; i < dofs; i++ )
        u[ i ] +=  tau * k2[ i ];
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
   if( k2 ) delete[] k2;
}
