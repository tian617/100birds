aux_source_directory(. SRCS)
add_library(server_lib ${SRCS})

add_executable(lockstep Server.cc)
target_link_libraries(lockstep base_lib server_lib)