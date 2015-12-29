add_library(xlfparser SHARED ${xlfparser_srcs})

if(XLFPARSER_USE_LIBROXML)
    target_compile_definitions(xlfparser PRIVATE -DXLFPARSER_USE_LIBROXML)
elseif(XLFPARSER_USE_LIBXML2)
    target_compile_definitions(xlfparser PRIVATE -DXLFPARSER_USE_LIBXML2)
endif()
target_include_directories(xlfparser PUBLIC ${xlfparser_include_dir})



install(TARGETS xlfparser DESTINATION lib)
install(FILES ${xlfparser_headers} DESTINATION include/xlfparser)

