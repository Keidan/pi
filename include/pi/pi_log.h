/**
 *******************************************************************************
 * @file pi_log.h
 * @author Keidan
 * @date 03/04/2013
 * @par Project
 * bns
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
#ifndef __PI_LOG_H__
  #define __PI_LOG_H__


  #include <libgen.h>
  #include <syslog.h>
  #ifndef MAX_MSG_SIZE
    #define MAX_MSG_SIZE 8192
  #endif

  #define __LOG_FILE__                   basename(__FILE__)
  #define __TMP_LOG__(prio, ...)         pi_log(prio, __VA_ARGS__)

  #define pi_logger(prio, fmt, ...)      __TMP_LOG__(prio, "[%s::%s(%d) -> " fmt, __LOG_FILE__, __func__, __LINE__, ##__VA_ARGS__)


  typedef enum {
    PI_EMERG=LOG_EMERG,          /* system is unusable */
    PI_ALERT=LOG_ALERT,          /* action must be taken immediately */
    PI_CRIT=LOG_CRIT,            /* critical conditions */
    PI_ERR=LOG_ERR,              /* error conditions */
    PI_WARNING=LOG_WARNING,      /* warning conditions */
    PI_NOTICE=LOG_NOTICE,        /* normal but significant condition */
    PI_INFO=LOG_INFO,            /* informational */
    PI_DEBUG=LOG_DEBUG,          /* debug-level messages */
  }pi_log_prio_et;


  /**
   * Fonction permetant l'ouverture des logs syslog.
   * @param ident Identifiant utilise pour les logs.
   * @param option options syslogs.
   * @param facility Facility syslog.
   */
  void pi_log_init(const char* ident, int option, int facility);

  /**
   * Fonction permetant la fermeture des logs syslog.
   */
  void pi_log_close();

  /**
   * Fonction permetant de logger un message.
   * @param prio Prio du log.
   * @param fmt Format/message.
   */
  void pi_log(pi_log_prio_et prio, const char* fmt, ...);

#endif /* __PI_LOG_H__ */
