#include <cstdlib>
#include "SIRProblem.h"
#include "Euler.h"
#include "Merson.h"
#include "ode-solve.h"

using namespace std;

const double initialTime( 0.0 );
const double finalTime( 100.0 );
const double timeStep( 1.0e-2 );

const double integrationTimeStep( 1.0e-4 );

int main( int argc, char** argv )
{
    SIRProblem problem;
    problem.setParameters( 1000.0, 5.0, 5.0, 6.1627, 5.0, 5.0 );
//    N - velikost populace
//    nat - míra porodnosti
//    m - míra úmrtnosti
//    b - riziko nakažení neimunních jedinců
//    c - míra uzdravení se nakažených jedinců
//    f - míra proočkování populace

//    reprodukční číslo r = b/c
//    např. tady je pro covid v Alžírsku r = 1.23254
//      https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7570398/


    Merson integrator;

    double sir[ 3 ] = { 2.0, 1.0, 1.0 };

    if( ! solve( initialTime,
                 finalTime,
                 timeStep,
                 integrationTimeStep,
                 &problem,
                 &integrator,
                 sir ) )
       return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
