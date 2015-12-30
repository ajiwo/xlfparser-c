add_library(xlfparser SHARED ${xlfparser_srcs})

#if(XLFPARSER_USE_LIBROXML)
#    set_target_properties(xlfparser PROPERTIES  COMPILE_DEFINITIONS XLFPARSER_USE_LIBROXML)
#elseif(XLFPARSER_USE_LIBXML2)
#    set_target_properties(xlfparser PROPERTIES  COMPILE_DEFINITIONS XLFPARSER_USE_LIBXML2)
#endif()
set_target_properties(xlfparser PROPERTIES COMPILE_FLAGS "-ansi -pedantic -I${xlfparser_include_dir}")


install(TARGETS xlfparser DESTINATION lib)
install(FILES ${xlfparser_headers} DESTINATION include/xlfparser)

