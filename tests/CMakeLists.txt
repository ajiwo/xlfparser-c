set(XLF_PATH "${PROJECT_SOURCE_DIR}/${xlfparser_example}/file.xml")
configure_file(
    "${PROJECT_SOURCE_DIR}/${xlfparser_test}/test-config.h.in"
    "${PROJECT_SOURCE_DIR}/${xlfparser_test}/test-config.h"
    @ONLY
)


macro(add_test_exe arg)
    add_executable(${arg}-test.exe ${arg}-test.c)
    target_link_libraries(${arg}-test.exe LINK_PUBLIC xlfparser ${xlfparser_libs})
    set_target_properties(${arg}-test.exe PROPERTIES COMPILE_FLAGS "-Wall -ansi -pedantic")
endmacro(add_test_exe)

add_test_exe(layout)
add_test_exe(region)


#define a macro to simplify adding tests
macro (do_test section arg1 arg2 result)
    add_test (${section}_test_${arg1}${arg2} ${section}-test.exe ${arg1} ${arg2})

    set_tests_properties(${section}_test_${arg1}${arg2}
        PROPERTIES
        REQUIRED_FILES ${XLF_PATH}
    )

    set_tests_properties(${section}_test_${arg1}${arg2}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endmacro (do_test)

# FIXME: what about -1 ? also match
do_test(layout "dummy" 0 "dummy")
do_test(layout "width" 0 "1920")
do_test(layout "height" 0 "1080")
do_test(layout "bgcolor" 0 "#ffffff")
do_test(layout "background" 0 "975.jpg")
do_test(layout "numregion" 0 "2")
do_test(layout "numtag" 0 "1")

do_test(region dummy 0 dummy)
do_test(region id 0 1153205596546b3c1237b90)
do_test(region width 0 1812)
do_test(region height 0 132)
do_test(region left 0 54)
do_test(region top 0 57)
do_test(region num_media 0 1)

do_test(region id 1 2033362323546b3f480f7ea)
do_test(region width 1 1816)
do_test(region height 1 772)
do_test(region left 1 54)
do_test(region top 1 253)
do_test(region num_media 1 3)

