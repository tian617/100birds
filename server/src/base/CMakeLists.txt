aux_source_directory(. SRCS)
add_library(base_lib ${SRCS})
target_link_libraries(base_lib event_core)

