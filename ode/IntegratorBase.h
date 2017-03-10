/* 
 * File:   IntegratorBase.h
 * Author: oberhuber
 *
 * Created on February 25, 2016, 9:13 AM
 */

#ifndef INTEGRATORBASE_H
#define	INTEGRATORBASE_H

class IntegratorBase
{
   public:
      
      IntegratorBase()
         : time( 0.0 ), stopTime( 0.0 )
      {
      }

      void setIntegrationTimeStep( const double& integrationTimeStep )
      {
         this->integrationTimeStep = integrationTimeStep;
      }
         
      void setTime( const double& time )
      {
         this->time = time;
      }
      
      void setStopTime( const double& stopTime )
      {
         this->stopTime = stopTime;
      }
                  
   protected:      
      
      double integrationTimeStep, time, stopTime;
};


#endif	/* INTEGRATORBASE_H */

