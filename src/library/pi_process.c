/**
 *******************************************************************************
 * @file pi_process.c
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
#include <pi/pi_process.h>
#include <pi/pi_log.h>
#include <pi/stringtoken.h>
#include <pi/string.h>
#include <errno.h>


void pi_process_init(struct process_list_s *li) {
  /* init de la liste */
  INIT_LIST_HEAD(&(li->list));
}

int pi_process_add_list(struct process_list_s *li, const char* pids) {
  stringtoken_t tok = NULL;
  char* item = NULL;
  int pid;
  if(!pids) {
    pi_logger(PI_ERR, "Invalid pids list '%s' !\n", pids);
    return -1;
  }
  tok = stringtoken_init(pids, PI_PID_SEPARATOR);
  while(stringtoken_has_more_tokens(tok)) {
    item = stringtoken_next_token(tok);
    if(!string_isint(item)) {
      stringtoken_release(tok);
      pi_logger(PI_ERR, "Invalid pid value '%s' !\n", item);
      return -1;
    }
    pid = string_parse_int(item, -1);
    if(pid == -1) {
      stringtoken_release(tok);
      pi_logger(PI_ERR, "Invalid pid value '%s' !\n", item);
      return -1;
    }
    if(pi_process_add(li, pid)) {
      stringtoken_release(tok);
      return -1;
    }
  }
  stringtoken_release(tok);
  return 0;
}

int pi_process_add(struct process_list_s *li, int pid) {
  struct process_list_s* node;
  node = (struct process_list_s*)malloc(sizeof(struct process_list_s));
  if(!node) {
    pi_logger(PI_ERR, "malloc: (%d) %s.\n", errno, strerror(errno));
    return -1;
  }
  /* init + ajout de l'element */
  node->pid = pid;
  list_add_tail(&(node->list), &(li->list));
  return 0;
}

void pi_process_clear(struct process_list_s *li) {
  struct process_list_s* iter;
  while(!list_empty(&li->list) ) {
    iter = list_entry(li->list.next, struct process_list_s, list);
    list_del(&iter->list); /*delete de l'item dans la liste */
    free(iter);
  }
}

int pi_process_empty(struct process_list_s *li) {
  if(!li) return 1;
  return list_empty(&li->list);
}
