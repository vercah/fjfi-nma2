/* 
 * File:   Merson.h
 * Author: oberhuber
 *
 * Created on February 26, 2016, 4:46 PM
 */

#ifndef MERSON_H
#define	MERSON_H

template< typename Problem >
class Merson : public IntegratorBase
{
   public:
      
      Merson( Problem& problem )
      : adaptivity( 1.0e-12 )
      {
         this->k1 = new double[ problem.getDegreesOfFreedom() ];
         this->k2 = new double[ problem.getDegreesOfFreedom() ];
         this->k3 = new double[ problem.getDegreesOfFreedom() ];
         this->k4 = new double[ problem.getDegreesOfFreedom() ];
         this->k5 = new double[ problem.getDegreesOfFreedom() ];
         this->aux = new double[ problem.getDegreesOfFreedom() ];
      }

      void setAdaptivity( const double& adaptivity )
      {
         this->adaptivity = adaptivity;
      }
      
      bool solve( Problem& problem,
                  double* u )
      {
         const int dofs = problem.getDegreesOfFreedom();
         double tau = std::min( this->integrationTimeStep, this->stopTime - this->time );
         long int iteration( 0 );
         while( this->time < this->stopTime )
         {
            /****
             * Compute k1
             */
            problem.getRightHandSide( this->time, u, k1 );
            
            /****
             * Compute k2
             */
            for( int i = 0; i < dofs; i++ )
               aux[ i ] = u[ i ] + tau * ( 1.0 / 3.0 * k1[ i ] );
            problem.getRightHandSide( this->time + 1.0 / 3.0 * tau, aux, k2 );
            
            /****
             * Compute k3
             */
            for( int i = 0; i < dofs; i++ )
               aux[ i ] = u[ i ] + tau * 1.0 / 6.0 * ( k1[ i ] + k2[ i ] );
            problem.getRightHandSide( this->time + 1.0 / 3.0 * tau, aux, k3 );
            
            /****
             * Compute k4
             */
            for( int i = 0; i < dofs; i++ )
               aux[ i ] = u[ i ] + tau * ( 0.125 * k1[ i ] + 0.375 * k3[ i ] );
            problem.getRightHandSide( this->time + 1.0 / 2.0 * tau, aux, k4 );
            
            /****
             * Compute k5
             */
            for( int i = 0; i < dofs; i++ )
               aux[ i ] = u[ i ] + tau * ( 0.5 * k1[ i ] - 1.5 * k3[ i ] + 2.0 * k4[ i ] );
            problem.getRightHandSide( this->time + tau, aux, k5 );
            
            /****
             * Compute error
             */
            double eps( 0.0 );
            for( int i = 0; i < dofs; i++ )
            {
               double err = ( tau / 3.0 * fabs( 0.2 * k1[ i ] + -0.9 * k3[ i ] + 0.8 * k4[ i ] + -0.1 * k5[ i ] ) );
               eps = std::max( eps, err );
            }
            
            /***
             *
             */
            if( this->adaptivity == 0.0 || eps < this->adaptivity )
            {
               for( int i = 0; i < dofs; i++ )
                  u[ i ] += tau / 6.0 * ( k1[ i ] + 4.0 * k4[ i ] + k5[ i ] );
               this->time += tau;
               iteration++;
               if( iteration > 100000 )
               {
                  std::cerr << "The solver has reached the maximum number of iteratoins. " << std::endl;
                  return false;
               }
            }
            if( this->adaptivity )
               tau *= 0.8 * pow( this->adaptivity / eps, 0.2 );
            tau = std::min( tau, this->stopTime - this->time );
            std::cout << "ITER: " << iteration << " \t tau = " << tau << " \t time= " << time << "         \r " << std::flush;
         }
         std::cout << std::endl;
         return true;
      }
      
      ~Merson()
      {
         delete[] k1;
         delete[] k2;
         delete[] k3;
         delete[] k4;
         delete[] k5;
         delete[] aux;
      }
      
   protected:
      
      double *k1, *k2, *k3, *k4, *k5, *aux;
      
      double adaptivity;

};

#endif	/* MERSON_H */

