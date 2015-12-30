add_executable(xlfsample example.c)
target_link_libraries(xlfsample LINK_PUBLIC xlfparser ${xlfparser_libs})
set_target_properties(xlfsample PROPERTIES  COMPILE_FLAGS "-Wall -I${CMAKE_SOURCE_DIR}/${xlfparser_src} -I${xlfparser_include_dir}")

install(TARGETS xlfsample DESTINATION bin)

