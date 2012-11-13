/* Copyright (c) 2012, Michael Phan-Ba
 *                     David Goulet <dgoulet@ev0ke.net>
 *                     Jacob Appelbaum
 * Copyright (c) 2012, The Tor Project, Inc. */
/* See LICENSE for licensing information */
/* http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x */

/**
  * \file clock-mach.c
  * \brief Contains clock primitives for Mach
  **/

#include "config.h"

#include <assert.h>

#include "clock.h"

/**
 * Get current real time value and store it into time.
 *
 * @param time where the current time is stored
 * @return clock_gettime syscall return value
 */
int clock_get_real_time_mach(struct tlsdate_time *time)
{
  /* Safety net */
  assert(time);

  clock_serv_t cclock;
  kern_return_t ret;

  ret = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  if (ret) return ret;
  ret = clock_get_time(cclock, &time->mts);
  mach_port_deallocate(mach_task_self(), cclock);

  return ret;
}

/**
 * Set current real time clock using time.
 *
 * @param time where the current time to set is stored
 * @return clock_settime syscall return value
 */
int clock_set_real_time_mach(const struct tlsdate_time *time)
{
  /* Safety net */
  assert(time);

  clock_serv_t cclock;
  kern_return_t ret;

  ret = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  if (ret) return ret;
  ret = clock_set_time(cclock, time->mts);
  mach_port_deallocate(mach_task_self(), cclock);
  return ret;
}

/**
 * Init a tlsdate_time structure.
 *
 * @param sec is the seconds
 * @param nsec is the nanoseconds
 */
void clock_init_time_mach(struct tlsdate_time *time, time_t sec,
                           long nsec)
{
  /* Safety net */
  assert(time);

  time->mts.tv_sec = sec;
  time->mts.tv_nsec = nsec;
}
