
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CMAKE_SOURCE_DIR}/scripts/pi_config.h.in"
  "${PI_SRC_BIN_DIR}/pi_config.h"
)


set(bin_src ${PI_SRC_BIN_DIR}/pi.c)
add_executable(pi ${bin_src})
target_link_libraries(pi lpi)
