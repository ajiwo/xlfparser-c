add_library(xlfparser SHARED ${xlfparser_srcs})

#if(XLFPARSER_USE_LIBROXML)
#    set_target_properties(xlfparser PROPERTIES  COMPILE_DEFINITIONS XLFPARSER_USE_LIBROXML)
#elseif(XLFPARSER_USE_LIBXML2)
#    set_target_properties(xlfparser PROPERTIES  COMPILE_DEFINITIONS XLFPARSER_USE_LIBXML2)
#endif()
set_target_properties(xlfparser PROPERTIES COMPILE_FLAGS "-Wall -ansi -pedantic -I${xlfparser_include_dir}")


install(
    TARGETS xlfparser
    DESTINATION lib
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
)
install(
    FILES ${xlfparser_install_headers}
    DESTINATION include/xlfparser
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
)

