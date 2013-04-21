/**
 *******************************************************************************
 * @file pi_utils.h
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
#ifndef __PI_UTILS_H__
  #define __PI_UTILS_H__

  #include <stdio.h>

  #define PI_1KB   0x400
  #define PI_1MB   0x100000
  #define PI_1GB   0x40000000



typedef enum { PI_UNIT_BYTE, PI_UNIT_KBYTES, PI_UNIT_MBYTES, PI_UNIT_GBYTES} pi_unit_et;

  void pi_utils_get_proc_filename(char filename[FILENAME_MAX], int pid, const char* file);

  long pi_utils_get_page_size();
  double pi_utils_get_page_size_in(pi_unit_et unit);
  long pi_utils_get_phy_pages();
  long pi_utils_get_available_phy_pages();
  long pi_utils_get_nprocessors_configured();
  long pi_utils_get_nprocessors_online();
  unsigned long pi_utils_get_phy_memory_size();
  double pi_utils_get_phy_memory_size_in(pi_unit_et unit);

#endif /* __PI_UTILS_H__ */
