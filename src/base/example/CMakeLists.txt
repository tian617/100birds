add_executable(client client.cc)
target_link_libraries(client base_lib)
add_executable(server server.cc)
target_link_libraries(server base_lib)