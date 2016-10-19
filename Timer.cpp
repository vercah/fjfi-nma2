/* 
 * File:   Timer.cpp
 * Author: oberhuber
 *
 * Created on October 3, 2016, 5:06 PM
 */

#include "Timer.h"

Timer::Timer()
{
   this->reset();
}
   
void Timer::reset()
{
   this->total_time = std::chrono::duration< double >::zero();
}

void Timer::start()
{
   this->start_ = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
   std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
   this->total_time += std::chrono::duration_cast< std::chrono::duration<double> >( end - start_ );
}

double Timer::getTime()
{
   return this->total_time.count();
}
