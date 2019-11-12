aux_source_directory(. SRCS)
add_library(server_lib ${SRCS})
target_link_libraries(server_lib base_lib)

add_executable(server main.cc)
target_link_libraries(server server_lib)