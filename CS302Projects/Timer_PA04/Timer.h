// Timer.h

#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <stdexcept>
#include <iostream>
#include <sys/time.h>

using namespace std;


class Timer {
  public:
    Timer();
    void start() throw (runtime_error);
    void stop() throw (logic_error);
    double getElapsedTime() const throw (logic_error);

  private:
    struct timeval beginTime;
    struct timeval duration;
    bool timerWasStarted;
};

#endif	// ifndef TIMER_H
