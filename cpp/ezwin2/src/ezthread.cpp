

#include "ezthread.h"

#ifndef USING_WINDOWS
 #include <unistd.h>
#endif


EZThread::EZThread()
{

#ifndef USING_WINDOWS
   pthread_mutex_init(&th_mutex,NULL);

   th_id = 0;
#else

  th_id = INVALID_HANDLE_VALUE;

  InitializeCriticalSection(&critsect);

#endif // __WIN32__
}

EZThread::~EZThread()
{
#ifndef USING_WINDOWS
   pthread_mutex_destroy(&th_mutex);
#else
  if(th_id != INVALID_HANDLE_VALUE)
  {
     // make sure its killed
     CloseHandle(th_id);
  }
  DeleteCriticalSection(&critsect);
#endif // __WIN32__
}
bool EZThread::isRunning()
{
#ifndef USING_WINDOWS
   return th_id!=0;
#else
  return th_id != INVALID_HANDLE_VALUE;
#endif // __WIN32__
}
bool EZThread::run()
{
#ifndef USING_WINDOWS
   typedef void * (* pthread_func)(void *);

   pthread_create(&th_id,NULL,(pthread_func)thread_task,(void *)this);
   pthread_detach(th_id);
#else
    DWORD th_info;
    // CREATE_SUSPENDED
    th_id = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)thread_task,this,0,&th_info);
#endif // __WIN32__
   return true;
}
bool EZThread::kill()
{
  down();
#ifndef USING_WINDOWS
   if(th_id) pthread_cancel(th_id);
   th_id=0;
#else
  //suspend(); 
  TerminateThread(th_id,0);
  CloseHandle(th_id);
  th_id = INVALID_HANDLE_VALUE;
#endif // __WIN32__
  up();

  return true;
}
/*
int EZThread::getPriority()
{
  return 0;
}
bool EZThread::setPriority(int pri)
{
  return true;
}
bool EZThread::resume()
{
#ifndef __WIN32__
   
#else
   ResumeThread(th_id);
#endif
  return true;
}

bool EZThread::suspend()
{
#ifndef __WIN32__

#else
   SuspendThread(th_id);
#endif
  return true;
}
*/
void EZThread::sleep(unsigned long milli)
{
#ifndef USING_WINDOWS
  usleep(milli);
#else
  Sleep(milli);
#endif  
  return;
}

void *EZThread::thread_task(EZThread *our_class)
{
   if(our_class)
   {
      // allow a cancel to work straight away
#ifndef USING_WINDOWS
      pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
#endif // __WIN32__

      our_class->run_method();

      our_class->down();

#ifndef USING_WINDOWS
        our_class->th_id = 0;
#else
        CloseHandle(our_class->th_id);
        our_class->th_id = INVALID_HANDLE_VALUE;
#endif
      our_class->up();
   }
   return NULL;
}

void EZThread::down()
{
#ifndef USING_WINDOWS
   pthread_mutex_lock(&th_mutex);
#else
  // lock for a critical section
  EnterCriticalSection(&critsect);
#endif // __WIN32__
}
void EZThread::up()
{
#ifndef USING_WINDOWS
   pthread_mutex_unlock(&th_mutex);
#else
  // lock for a critical section
  LeaveCriticalSection(&critsect);
#endif // __WIN32__

}
bool EZThread::trydown()
{
#ifndef USING_WINDOWS
   // currently only coded for UNIX
   if(pthread_mutex_trylock(&th_mutex)==0) return true;
#endif
   return false;
}

void EZThread::run_method()
{
   // the actual runnable method - Implement a new one of these
   return;
}
