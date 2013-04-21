#include <pi/pi_utils.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/param.h>

void pi_utils_get_proc_filename(char filename[FILENAME_MAX], int pid, const char* file) {
  snprintf(filename, FILENAME_MAX, "/proc/%d/%s", pid, file);
}

double pi_utils_get_page_size_in(pi_unit_et unit) {
  switch(unit) {
    case PI_UNIT_BYTE:
      return (double)pi_utils_get_page_size();
    case PI_UNIT_KBYTES:
      return (double)pi_utils_get_page_size() / PI_1KB;
    case PI_UNIT_MBYTES:
      return (double)pi_utils_get_page_size() / PI_1MB;
    case PI_UNIT_GBYTES:
      return (double)pi_utils_get_page_size() / PI_1GB;
  }
  return 0.0;
}

long pi_utils_get_page_size() {
  return sysconf(_SC_PAGE_SIZE);
}

long pi_utils_get_phy_pages() {
  return sysconf(_SC_PHYS_PAGES);
}

long pi_utils_get_available_phy_pages() {
  return sysconf(_SC_AVPHYS_PAGES);
}

long pi_utils_get_nprocessors_configured() {
  return sysconf(_SC_NPROCESSORS_CONF);
}

long pi_utils_get_nprocessors_online() {
  return sysconf(_SC_NPROCESSORS_ONLN);
}

unsigned long pi_utils_get_phy_memory_size() {
  return pi_utils_get_phy_pages() * pi_utils_get_page_size();
}

double pi_utils_get_phy_memory_size_in(pi_unit_et unit) {
  switch(unit) {
    case PI_UNIT_BYTE:
      return (double)pi_utils_get_phy_memory_size();
    case PI_UNIT_KBYTES:
      return (double)pi_utils_get_phy_memory_size() / PI_1KB;
    case PI_UNIT_MBYTES:
      return (double)pi_utils_get_phy_memory_size() / PI_1MB;
    case PI_UNIT_GBYTES:
      return (double)pi_utils_get_phy_memory_size() / PI_1GB;
  }
  return 0.0;
}
