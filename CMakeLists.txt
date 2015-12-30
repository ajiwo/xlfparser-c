cmake_minimum_required (VERSION 2.8.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


set(xlfparser_src src)
set(xlfparser_example example)
set(xlfparser_test tests)

project(xlfparser)
include(CTest)

set(xlfparser_headers
    xlfnode.h
    xlfkeyval.h
    xlfmedia.h
    xlfregion.h
    xlflayout.h
    xlfparser.h
    xlfparser-config.h
)

set(xlfparser_base_srcs xlfnode.c xlfkeyval.c xlfmedia.c xlfregion.c xlflayout.c xlfparser.c)
set(xlfparser_roxml_srcs ${xlfparser_base_srcs} xlfparser-roxml.c)
set(xlfparser_xml2_srcs ${xlfparser_base_srcs} xlfparser-xml2.c)


macro(m_use_libroxml)
    set(xlfparser_srcs ${xlfparser_roxml_srcs})
    set(xlfparser_include_dir ${LIBROXML_INCLUDE_DIRS})
    set(xlfparser_headers ${xlfparser_headers} xlfparser-roxml.h)
    set(xlfparser_libs ${LIBROXML_LIBRARIES})
    set(XLFPARSER_USE_LIBROXML ON)
endmacro()

macro(m_use_libxml2)
    set(xlfparser_srcs ${xlfparser_xml2_srcs})
    set(xlfparser_include_dir ${LIBXML2_INCLUDE_DIR})
    set(xlfparser_headers ${xlfparser_headers} xlfparser-xml2.h)
    set(xlfparser_libs ${LIBXML2_LIBRARIES})
    set(XLFPARSER_USE_LIBXML2  ON)
endmacro()

set(PREFER_LIBROXML 0 CACHE INTERNAL "Prefer to use libroxml")
set(PREFER_LIBXML2 0 CACHE INTERNAL "Prefer to use libxml2")

find_package(LibROXML REQUIRED)

if(NOT LIBROXML_FOUND)
    message("++ libroxml is NOT FOUND")
    message("++ You can specify custom libroxml directory ")
    message("++ => 'LIBROXML_DIR=/opt/path/to/libroxml cmake ${CMAKE_SOURCE_DIR}'")
    message("++ OR set LIBROXML_DIR environment variable,")
    message("++ OR ignore this message if you prefer libxml2.")
endif()



find_package(LibXml2 2.6.18 REQUIRED)

if(LIBROXML_FOUND AND LIBXML2_FOUND)
    message("++ Both libroxml and libxml2 are found")
    if(PREFER_LIBROXML AND NOT PREFER_LIBXML2)
        message("++ roxml is preferred")
        m_use_libroxml()
    elseif(PREFER_LIBXML2 AND NOT PREFER_LIBROXML)
        message("++ xml2 is preferred ")
        m_use_libxml2()
    else()
        message("++ must set one preferred xml library to use")
        message("++ => 'cmake ${CMAKE_SOURCE_DIR} -DPREFER_LIBROXML' to use libroxml or,")
        message("++ => 'cmake ${CMAKE_SOURCE_DIR} -DPREFER_LIBXML2' to use libxml")
        message("++ now exiting")
        return()
    endif()

elseif(LIBROXML_FOUND)
    m_use_libroxml()
elseif(LIBXML2_FOUND)
    m_use_libxml2()
else()
    message("++ Neither libroxml or libxml2 is found.")
    message("++ Cannot continue, now exiting.. ")
    return()
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/${xlfparser_src}/xlfparser-config.h.in"
    "${PROJECT_SOURCE_DIR}/${xlfparser_src}/xlfparser-config.h"
    @ONLY
)

add_subdirectory("${xlfparser_src}")
add_subdirectory("${xlfparser_example}")
add_subdirectory("${xlfparser_test}")

