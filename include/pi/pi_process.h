/**
 *******************************************************************************
 * @file pi_process.h
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
#ifndef __PI_PROCESS_H__
  #define __PI_PROCESS_H__

  #include <stdlib.h>
  #include <linux/list.h>

  #ifndef PI_PID_SEPARATOR
    #define PI_PID_SEPARATOR ","
  #endif /* PI_PID_SEPARATOR */

  struct process_list_s {
      struct list_head list; /*!< Liste des pid. */
      int pid;               /*!< Pid. */
  };

  /**
   * Fonction permetant l'initialisation de la liste.
   * @param li Liste.
   */
  void pi_process_init(struct process_list_s *li);

  /**
   * Fonction permetant l'ajout d'un pid.
   * @param li Liste.
   * @param pid PID.
   * @return retourne -1 en cas d'erreur sinon 0.
   */
  int pi_process_add(struct process_list_s *li, int pid);

  /**
   * Fonction permetant l'ajout d'une liste de pid.
   * @param li Liste.
   * @param pid PID.
   * @return retourne -1 en cas d'erreur sinon 0.
   */
  int pi_process_add_list(struct process_list_s *li, const char* pids);

  /**
   * Fonction permetant le clear de la liste
   * @param li Liste.
   */
  void pi_process_clear(struct process_list_s *li);


  /**
   * Teste si la liste est vide ou non.
   * @param li Liste.
   * @return 0 si elle n'est pas vide sinon 1.
   */
  int pi_process_empty(struct process_list_s *li);

#endif /* __PI_PROCESS_H__ */
