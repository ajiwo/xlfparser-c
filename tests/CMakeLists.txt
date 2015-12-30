set(XLF_PATH "${PROJECT_SOURCE_DIR}/${xlfparser_example}/file.xml")
configure_file(
    "${PROJECT_SOURCE_DIR}/${xlfparser_test}/test-config.h.in"
    "${PROJECT_SOURCE_DIR}/${xlfparser_test}/test-config.h"
    @ONLY
)


add_executable(layout-test.exe layout-test.c)
target_link_libraries(layout-test.exe LINK_PUBLIC xlfparser ${xlfparser_libs})


add_test(LayoutRunTest layout-test.exe "dummy")
set_tests_properties(LayoutRunTest
    PROPERTIES
    REQUIRED_FILES ${XLF_PATH}
)


#define a macro to simplify adding tests
macro (do_layout_test arg result)
    add_test (LayoutTest_${arg} layout-test.exe ${arg})

    set_tests_properties(LayoutTest_${arg}
        PROPERTIES
        REQUIRED_FILES ${XLF_PATH}
    )

    set_tests_properties(LayoutTest_${arg}
        PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endmacro (do_layout_test)

do_layout_test("width" "1920")
do_layout_test("height" "1080")
do_layout_test("bgcolor" "#ffffff")
do_layout_test("background" "975.jpg")
