/* 
 * File:   heat-equation-2d.cpp
 * Author: oberhuber
 *
 * Created on March 26, 2019, 10:41 AM
 */

#include <cstdlib>
#include "HeatEquationProblem2D.h"
#include "../ode/Euler.h"
#include "../ode/Merson.h"
#include "../ode/ode-solve.h"
#include "../Vector.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 0.1 );
const double timeStep( 0.0001 );
const double integrationTimeStep( 1.0e-6 );
const int size( 100 );

int main( int argc, char** argv )
{
   HeatEquationProblem2D problem( size, size );
   
   Merson integrator; 
   integrator.setAdaptivity( 1.0e-8 );
    
   double* u = new double[ problem.getDegreesOfFreedom() ];
   //problem.setInitialCondition( u );
   int width, height;
   Vector v;
   v.readPGM("../data/motyl.pgm", width, height);
   u = v.getData();
   problem.writeSolution( 0.0, 0, u );
   
   if( ! solve( initialTime,
            finalTime,
            timeStep,
            integrationTimeStep,
            &problem,
            &integrator,
            u ) )
   {
      delete[] u;
      return EXIT_FAILURE;
   }
   v.writePGM("motyl.pgm", width, height);
   delete[] u;
   return EXIT_SUCCESS;
}

