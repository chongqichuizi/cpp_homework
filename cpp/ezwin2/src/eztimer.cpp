#include <eztimer.h>
#include <ezwindow.h>
#include <windows.h>

EZTimer::EZTimer(EZWindow *win,bool oneshot)
{
  _timerid = 0;
  _win = win;
  _oneshot = oneshot;
}
EZTimer::~EZTimer()
{
  stop();
}

bool EZTimer::start(unsigned int timeval)
{
  _timerid = SetTimer(_win->getHandle(),1,timeval,0);

  return _timerid != 0;
}

void EZTimer::stop()
{
  if(_timerid) KillTimer(_win->getHandle(),_timerid);

  _timerid = 0;
}



