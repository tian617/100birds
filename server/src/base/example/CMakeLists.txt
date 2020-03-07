add_executable(client client.cc)
target_link_libraries(client base_lib)
add_executable(serverTest server.cc)
target_link_libraries(serverTest base_lib)