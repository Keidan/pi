/**
 *******************************************************************************
 * @file pi_log.c
 * @author Keidan
 * @date 03/04/2013
 * @par Project
 * pi
 *
 * @par Copyright
 * Copyright 2011-2013 Keidan, all right reserved
 *
 * This software is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY.
 *
 * Licence summary : 
 *    You can modify and redistribute the sources code and binaries.
 *    You can send me the bug-fix
 *
 * Term of the licence in in the file licence.txt.
 *
 *******************************************************************************
 */
#include <pi/pi_log.h>
#include <syslog.h>
#include <stdarg.h>
#include <stdio.h>


void pi_log_init(const char* ident, int option, int facility) {
  openlog (ident, option, facility);
}

void pi_log_close() {
  closelog();
}

void pi_log(pi_log_prio_et prio, const char* fmt, ...) {
  va_list args;
  char msg[MAX_MSG_SIZE] = {0};
  va_start(args, fmt);
  vsnprintf(msg, MAX_MSG_SIZE, fmt, args);
  va_end(args);
  syslog(prio, "%s", msg);
}
