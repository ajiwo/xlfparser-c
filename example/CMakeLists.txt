add_executable(xlfparserapp example.c)
target_link_libraries(xlfxample LINK_PUBLIC xlfparser ${xlfparser_libs}) 
target_include_directories(xlfxample PUBLIC ${CMAKE_SOURCE_DIR}/${xlfparser_src})

install(TARGETS xlfxsample DESTINATION bin)

