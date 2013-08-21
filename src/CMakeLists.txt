
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PI_SRC_DIR}/pi_config.h.in"
  "${PI_SRC_DIR}/pi_config.h"
)


set(bin_src 
  ${PI_SRC_DIR}/pi.c
  ${PI_SRC_DIR}/pi_process.c
)
add_executable(pi ${bin_src})
target_link_libraries(pi tk zlib-minizip)
