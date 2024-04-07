aux_source_directory(. SRC_LIST)
aux_source_directory(../database DATABASE_LIST)
add_executable(chatserver ${SRC_LIST} ${DATABASE_LIST})
target_link_libraries(chatserver muduo_net muduo_base pthread mysqlclient)