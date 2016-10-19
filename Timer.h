/* 
 * File:   Timer.h
 * Author: oberhuber
 *
 * Created on October 3, 2016, 4:59 PM
 */

#pragma once

#include <chrono>

class Timer
{

   public:
      Timer();

      void reset();

      void start();

      void stop();

      double getTime();   
   
   protected:
    
      std::chrono::high_resolution_clock::time_point start_;
      
      std::chrono::duration< double > total_time;
};

