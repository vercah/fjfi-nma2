/* 
 * File:   poisson-1d.cpp
 * Author: oberhuber
 *
 * Created on Match 19, 2019, 10:41 AM
 */

#include <fstream>
#include <cmath>
#include <iostream>
using namespace std;
#include "../Vector.h"
#include "../matrices/EllpackMatrix.h"
#include "../matrices/DenseMatrix.h"
#include "../stationary/StationarySolver.h"

const int N = 4;
const double h = 1.0 / ( double ) ( N - 1 );
const double h_sqr = h * h;

double f( const double& x, const double& y )
{
   return 1.0;
   //return 10.0 * x * y;
   //return 10.0 * ( 1.0 - 2.0 * x * x - 2.0 * y * y );
   //return 250.0 * x * x *sin( 10 * M_PI * ( x * x + y * y ) );
}
double g( const double& x, const double& y )
{
   return 10.0;
   //return 10.0 * x * y;
   //return 10.0 * ( 1.0 - 2.0 * x * x - 2.0 * y * y );
   //return 250.0 * x * x *sin( 10 * M_PI * ( x * x + y * y ) );
}

int main( int argc, char* argv[] )
{   
   /***
    * Set-up the linear system
    */
   const int dofs = ( N + 1 ) * ( N + 1 );
   Vector u( dofs ), b( dofs );
   EllpackMatrix A( dofs, dofs );
   A.setRowLength( 5 );

    for( int j = 0; j <= N; j++ ) {
        for( int i = 0; i <= N; i++ ){
            if ((i==0 || i==N) || (j==0 || j==N)){
                b[j*(N+1)+i]=g(j, i);
            }else{
                b[j*(N+1)+i]=f(j, i);
            }
        }
    }

    for(int i = 0; i<dofs;i++) {cout << b[i] << ", ";}

   for( int i = 0; i < dofs; i++ ) {
      for( int j = 0; j < dofs; j++ )
      {
         // Set-up the linear system matrix here.
         // 1s on the diagonal
         if(i<=(N+1) || i>=(N+1)*(N+1)-(N+2) || (i%(N+1)==0 && i>0) || (i+1)%(N+1)==0 && i>0){
            if(j==i){
                A.setElement(i, i, 1);
                //cout << "1 ";
            }else{//cout << "0 ";
            }
         }else if (j==(i-(N+1))||j==i+(N+1)||j==(i-1)||j==(i+1)){
            A.setElement(i, j, -1);
            //cout << "-1";
         }else if (i==j){
            A.setElement(i, j, 4);
            //cout << "4 ";
         }
         else {//cout << "0 ";
         }
      }
      //cout << endl;
   }
   
   /***
    * Solve the linear system
    */
   StationarySolver solver( A, b );
   solver.setConvergenceResidue( 1.0e-4 );
   solver.setMaxIterations( 500 );
   solver.solve( u, "sor", 1.9 );
   
   /****
    * Write the solution to the output file
    */
   std::fstream f;
   f.open( "poisson-2d.txt", std::ios::out );
   u.writeGnuplot2D( f, N + 1, N + 1, h, h, 0, 0 );
}

