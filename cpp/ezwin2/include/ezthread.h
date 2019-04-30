

/***********************************************************
 * EZWIN2
 *
 * Name:      ezthread.h
 * version:   0.1
 * date:      3 March 2002
 * author:	  John Donoghue <john.donoghue@ieee.org>
 * copyright: (c) John Donoghue, 2001-2002
 *
 * NOTE: ezthread has appeared in a number of GPL projects
 * under my permission :)
 ***********************************************************/

/***********************************************************
 * This software is free, and may be distributed or modified
 * as specified under the terms of the Lesser General Public 
 * License as published by the Free Software Foundation.
 ***********************************************************/

#ifndef ezthread_h
#define ezthread_h

#ifndef USING_WINDOWS
  #ifdef __WIN32__
    #define USING_WINDOWS
  #else
    #ifdef  WIN32
      #define USING_WINDOWS 
    #endif
  #endif
#endif

#ifndef USING_WINDOWS
  #include <pthread.h>
  #define DLL_EXP
#else
  #include <ezwin.h>
#endif

/**
 * @short simple thread implementation with mutex
 * @author John Donoghue <donoghue@chariot.net.au>
 * @copyright 2000
 * @version 0.3
 *
 * Provides a basic c++ implementation of the pthread
 * functionality for creating a multithreaded clients in
 * both in windows and in UNIX.
 *
 */
class DLL_EXP EZThread
{
   private:
#ifndef USING_WINDOWS
      pthread_mutex_t th_mutex;
      pthread_t th_id;
#else
      CRITICAL_SECTION critsect; // the mutex for the crital section
      HANDLE th_id;
#endif //USING_WINDOWS

      bool done;
   public:
      EZThread();
      virtual ~EZThread();

      bool run();
      bool kill();

      bool isRunning();
   protected:
      void down();
      void up();
      bool trydown();

      virtual void run_method();

      void sleep(unsigned long millisec);
   private:
      static void *thread_task(EZThread *our_class);
};

#endif // ezthread_h
