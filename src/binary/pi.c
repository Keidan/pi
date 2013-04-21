/**
 *******************************************************************************
 * @file pi.c
 * @author Keidan
 * @date 06/04/2013
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
#include "pi_config.h"
#include <getopt.h>
#include <signal.h>
#include <pi/pi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <linux/list.h>
#include <sys/types.h>
#include <unistd.h>

static struct process_list_s list_process;

static const struct option long_options[] = { 
    { "help"   , 0, NULL, 'h' },
    { "process", 1, NULL, 'p' },
    { "self"   , 0, NULL, 's' },
    { NULL     , 0, NULL, 0   } 
};

static void pi_sig_int(sig_t s);
static void pi_cleanup(void);

/**
 * Affichage du 'usage'.
 * @param err Code passe a exit.
 */
void usage(int err) {
  fprintf(stdout, "usage: pi options\n");
  fprintf(stdout, "\t--help, -h: Print this help.\n");
  fprintf(stdout, "\t--process, -p: Process list or single process (eq list without spaces: pid1"PI_PID_SEPARATOR"pid2"PI_PID_SEPARATOR"pidN).\n");
  fprintf(stdout, "\t--self, -s: Current process.\n");
  exit(err);
}


int main(int argc, char** argv) {
  int opt;
  struct process_list_s* iter;
  struct process_stat_s stat;
  fprintf(stdout, "Process Information is a FREE software v%d.%d.\nCopyright 2011-2013 By kei\nLicense GPL.\n", PI_VERSION_MAJOR, PI_VERSION_MINOR);

  /* init de la liste */
  pi_process_init(&list_process);
  /* ouverture d'une session syslog. */
  pi_log_init("pi", LOG_PID|LOG_CONS|LOG_PERROR, LOG_USER);


  /* pour fermer proprement sur le kill */
  atexit(pi_cleanup);
  signal(SIGINT, (__sighandler_t)pi_sig_int);

  while ((opt = getopt_long(argc, argv, "hp:s", long_options, NULL)) != -1) {
    switch (opt) {
      case 'h': usage(0); break;
      case 'p': /* process list */
	if(pi_process_add_list(&list_process, optarg))
	  usage(EXIT_FAILURE);
	break;
      case 's': /* self */
	if(pi_process_add(&list_process, getpid()))
	  usage(EXIT_FAILURE);
	break;
      default: /* '?' */
	pi_logger(PI_ERR, "Unknown option '%c'\n", opt);
	usage(EXIT_FAILURE);
	break;
    }
  }

  /* teste la taille de la liste */
  if(pi_process_empty(&list_process)) {
    pi_logger(PI_ERR, "Invalid process list size!\n");
    usage(EXIT_FAILURE);
  }

  printf("Nb processors configured: %ld\n", pi_utils_get_nprocessors_configured());
  printf("Nb processors online: %ld\n", pi_utils_get_nprocessors_online());
  printf("Page size: %ld bytes, (%lf Kb)\n", 
	 pi_utils_get_page_size(), pi_utils_get_page_size_in(PI_UNIT_KBYTES));
  printf("Physical pages: %ld\n", pi_utils_get_phy_pages());
  printf("Available physical pages: %ld\n", pi_utils_get_available_phy_pages());
  printf("Physical memory size (RAM): %lu bytes, %lf Kb, %lf Mb, %lf Gb\n", 
	 pi_utils_get_phy_memory_size(), pi_utils_get_phy_memory_size_in(PI_UNIT_KBYTES), 
	 pi_utils_get_phy_memory_size_in(PI_UNIT_MBYTES), pi_utils_get_phy_memory_size_in(PI_UNIT_GBYTES));

  /* parse la liste */
  list_for_each_entry(iter, &list_process.list, list) {
    pi_parser_proc_stat(&stat, iter->pid);
    
    printf("Process stat:\n");

    printf("\tPID: %d.\n\tName: %s.\n", stat.pid, stat.name);
    printf("\tState: %c (%s).\n", stat.state.st, stat.state.desc);
    printf("\tPPID: %d.\n\tGroup: %d.\n", stat.ppid, stat.pgrp);
    printf("\tSession: %d.\n", stat.session);
    printf("\tNb TTY: %d. TTY Group: %d.\n", stat.tty_nb, stat.tpgid);
    printf("\tFlags: %lu.\n", stat.flags);
    printf("\tMin page faults: %lu. (childs): %lu.\n", stat.minflt, stat.cminflt);
    printf("\tMax page faults: %lu. (childs): %lu.\n", stat.majflt, stat.cmajflt);
    printf("\tUser time: %llu jiffies. (childs): %llu jiffies.\n", stat.utime, stat.cutime);
    printf("\tKernel time: %llu jiffies. (childs): %llu jiffies.\n", stat.stime, stat.cstime);
    printf("\tPriority: %d.\n\tNiceness: %d.\n", stat.priority, stat.nice);
    printf("\tThreads: %d.\n\tStart time: %llu.\n", stat.nlwp, stat.start_time);
    printf("\tVirtual memory space (in page): %lu.\n\tResident set (in page): %lu.\n", stat.vsize, stat.vm_rss);
    printf("\tResident set limit: %lu.\n\tStart code: %lu.\n", stat.rss_rlim, stat.start_code);
    printf("\tEnd code: %lu.\n\tStart stack: %lu.\n", stat.end_code, stat.start_stack);
    printf("\tKernel stack pointer (esp): %lu.\n\tKernel instruction pointer (eip): %lu.\n", stat.kstk_esp, stat.kstk_eip);
    printf("\tPending signals: %lld.\n\tBlocked signals: %lld.\n", stat.signal, stat.blocked);
    printf("\tIgnored signals: %lld.\n\tCatch signals: %lld.\n", stat.sigignore, stat.sigcatch);
    printf("\tWaits: %lu.\n\tTerminates signals: %lld.\n", stat.wchan, stat.sigpnd);
    printf("\tCPU scheduled: %d.\n\tRT priority: %lu.\n", stat.processor, stat.rtprio);
    printf("\tScheduling policy: %lu.\n\tTime wait for I/O: %lu.\n", stat.sched, stat.twait);
    printf("\tGuest time: %llu jiffies.\n\tGuest time (childs): %llu jiffies.\n", stat.gtime, stat.gctime);
  }
  return 0;
}


static void pi_sig_int(sig_t s) {
  exit(0); /* call atexit */
}

static void pi_cleanup(void) {
  pi_process_clear(&list_process);
  /* fermeture de la session syslog. */
  pi_log_close();
}
