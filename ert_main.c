/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'Arachne'.
 *
 * Model version                  : 1.754
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Fri Sep 21 17:28:13 2018
 *
 * Target selection: ert_linux.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

/* Multirate - Multitasking case main file */
#define _BSD_SOURCE                                              /* For usleep() */
#define _POSIX_C_SOURCE                200112L                   /* For clock_gettime() & clock_nanosleep() */
#include <stdio.h>                     /* This ert_main.c example uses printf/fflush */
#include <pthread.h>                   /* Thread library header file */
#include <sched.h>                     /* OS scheduler header file */
#include <semaphore.h>                 /* Semaphores library header file */
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>                  /* For mlockall() */
#include <signal.h>
#include "Arachne.h"                   /* Model's header file */
#include "rtwtypes.h"                  /* MathWorks types */
#include "rtmodel.h"
#ifndef TRUE
#define TRUE                           true
#define FALSE                          false
#endif

/*==================*
 * Required defines *
 *==================*/
#ifndef MODEL
#define MODEL                          Arachne
#else

/* create generic macros that work with any model */
# define EXPAND_CONCAT(name1,name2)    name1 ## name2
# define CONCAT(name1,name2)           EXPAND_CONCAT(name1,name2)
# define MODEL_INITIALIZE              CONCAT(MODEL,_initialize)
# define MODEL_STEP                    CONCAT(MODEL,_step)
# define MODEL_TERMINATE               CONCAT(MODEL,_terminate)
# define RT_MDL                        CONCAT(MODEL,_M)
#endif

/* Error checking */
#define STRINGIZE(num)                 #num
#define POS(line)                      __FILE__ ":" STRINGIZE(line)
#define CHECK0(expr)                   do { int __err = (expr); if (__err) { fprintf(stderr, "Error: %s returned '%s' at " POS(__LINE__) "\n", #expr, strerror(__err)); exit(1); } } while (0);
#define CHECKE(expr)                   do { if ((expr) == -1) { perror(#expr " at " POS(__LINE__)); exit(1); } } while (0);

/**
 * Maximal priority used by base rate thread.
 */
#define MAX_PRIO                       (sched_get_priority_min(SCHED_FIFO) + 2)

/**
 * Thread handle of the base rate thread.
 * Fundamental sample time = 5.0E-5s
 */
pthread_t base_rate_thread;

/**
 * Thread handles of and semaphores for sub rate threads. The array
 * is indexed by TID, i.e. the first one or two elements are unused.
 */
struct sub_rate {
  pthread_t thread;
  sem_t sem;
} sub_rate[2];

/**
 * Flag if the simulation has been terminated.
 */
int simulationFinished = 0;

/**
 * This is the thread function of the base rate loop.
 * Fundamental sample time = 5.0E-5s
 */
void * base_rate(void *param_unused)
{
  struct timespec now, next;
  struct timespec period = { 0U, 50000U };/* 5.0E-5 seconds */

  boolean_T eventFlags[2] = { 0 };     /* Model has 2 rates */

  int_T taskCounter[2] = { 0, 0 };

  int_T OverrunFlags[2];
  int step_sem_value;
  int_T i;
  (void)param_unused;
  clock_gettime(CLOCK_MONOTONIC, &next);
  pfuncStub[0](0);

  /* Main loop, running until all the threads are terminated */
  while (rtmGetErrorStatus(Arachne_M) == NULL && !rtmGetStopRequested(Arachne_M))
  {
    /* Check subrate overrun, set rates that need to run this time step*/

    /* Trigger sub-rate threads */

    /* Execute base rate step */
    pfuncStub[1](0);
    pfuncStub[2](Arachne_step);
    pfuncStub[3](0);
    do {
      next.tv_sec += period.tv_sec;
      next.tv_nsec += period.tv_nsec;
      if (next.tv_nsec >= 1000000000) {
        next.tv_sec++;
        next.tv_nsec -= 1000000000;
      }

      clock_gettime(CLOCK_MONOTONIC, &now);
      if (now.tv_sec > next.tv_sec ||
          (now.tv_sec == next.tv_sec && now.tv_nsec > next.tv_nsec)) {
        uint32_T usec = (now.tv_sec - next.tv_sec) * 1000000 + (now.tv_nsec -
          next.tv_nsec)/1000;

        //	  fprintf(stderr, "Base rate (5.0E-5s) overrun by %d us\n", usec);
        next = now;
        continue;
      }
    } while (0);

    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, NULL);
  }

  simulationFinished = 1;

  /* Final step */
  for (i = 2; i < 2; i++) {
    sem_post(&sub_rate[i].sem);
    sem_post(&sub_rate[i].sem);
  }

  return NULL;
}

/**
 * Signal handler for ABORT during simulation
 */
void abort_signal_handler(int sig)
{
  fprintf(stderr, "Simulation aborted by pressing CTRL+C\n");

  //  rtmSetStopRequested(Arachne_M, 1);
}

/**
 * This is the main function of the model.
 * Multirate - Multitasking case main file
 */
int_T main(int_T argc, const char_T *argv[])
{
  const char_T *errStatus;
  int_T i;
  pthread_attr_t attr;
  struct sched_param sched_param;
  (void)(argc);
  (void *)(argv);
  CHECKE(mlockall(MCL_CURRENT | MCL_FUTURE));
  interface_bind_func(0);

  /* Initialize model */
  Arachne_initialize();
  simulationFinished = 0;

  /* Prepare task attributes */
  CHECK0(pthread_attr_init(&attr));
  CHECK0(pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED));
  CHECK0(pthread_attr_setschedpolicy(&attr, SCHED_FIFO));

  /* Starting the base rate thread */
  sched_param.sched_priority = MAX_PRIO;
  CHECK0(pthread_attr_setschedparam(&attr, &sched_param));
  CHECK0(pthread_create(&base_rate_thread, NULL, base_rate, NULL));
  CHECK0(pthread_attr_destroy(&attr));

  /* Wait for threads to finish */
  pthread_join(base_rate_thread, NULL);
  funcFinish(0);

  /* Terminate model */
  //Arachne_terminate();
  errStatus = rtmGetErrorStatus(Arachne_M);
  if (errStatus != NULL && strcmp(errStatus, "Simulation finished")) {
    if (!strcmp(errStatus, "Overrun")) {
      printf("ISR overrun - sampling rate too fast\n");
    }

    return(1);
  }

  return 0;
}

/* Local Variables: */
/* compile-command: "make -f Arachne.mk" */
/* End: */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
