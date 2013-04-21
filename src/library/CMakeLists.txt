
set(lib_src 
  ${PI_SRC_LIB_DIR}/string.c
  ${PI_SRC_LIB_DIR}/stringtoken.c
  ${PI_SRC_LIB_DIR}/pi_log.c
  ${PI_SRC_LIB_DIR}/pi_process.c
  ${PI_SRC_LIB_DIR}/pi_utils.c
  ${PI_SRC_LIB_DIR}/pi_parser.c
)
add_library(lpi SHARED ${lib_src})
