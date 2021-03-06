#include "../src/xlfparser.h"
#include "test-config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char **argv) {
    xlfNode *layout_node;
    Layout *layout;
    char *arg;
    int failed = 0;

    int num_region, num_tag;

    if(argc < 2) {
        return 1;
    }

    layout_node = xlfparser_parse_file(XLF_PATH, &num_region, &num_tag);
    if(!layout_node) {
        return 2;
    }

    layout = xlfparser_get_layout(layout_node);
    arg = argv[1];

    if(!strcmp(arg, "dummy")) {
        printf("dummy\n");
    }
    else if(!strcmp(arg, "width")) {
        printf("%d\n", layout->width);
    } else if(!strcmp(arg, "height")) {
        printf("%d\n", layout->height);
    } else if(!strcmp(arg, "bgcolor")) {
        printf("%s\n", layout->bgcolor);
    } else if(!strcmp(arg, "background")) {
        printf("%s\n", layout->background);
    } else if(!strcmp(arg, "numtag")) {
        printf("%d\n", xlfparser_tag_length(layout));
    } else if(!strcmp(arg, "numregion")) {
        printf("%d\n", xlfparser_region_length(layout));
    } else {
        failed = 1;
    }
    xlfparser_delete_layout(layout);

    return failed;
}
