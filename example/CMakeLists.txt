add_executable(xlfsample example.c)
target_link_libraries(xlfsample LINK_PUBLIC xlfparser ${xlfparser_libs})
target_include_directories(xlfsample PUBLIC ${CMAKE_SOURCE_DIR}/${xlfparser_src})

install(TARGETS xlfsample DESTINATION bin)

