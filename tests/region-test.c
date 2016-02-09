#include "../src/xlfparser.h"
#include "test-config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char **argv) {
    xlfNode *layout_node;
    Layout *layout;
    Region *region;
    char *arg1;
    int region_index;
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

    arg1 = argv[1];
    region_index = atoi(argv[2]);

    region = xlfparser_get_region(layout, region_index);
    if(!region) {
        return 3;
    }

    if(!strcmp(arg1, "dummy")) {
        printf("dummy\n");
    }
    else if(!strcmp(arg1, "id")) {
        printf("%s\n", region->id);
    } if(!strcmp(arg1, "width")) {
        printf("%d\n", region->width);
    } else if(!strcmp(arg1, "height")) {
        printf("%d\n", region->height);
    } else if(!strcmp(arg1, "left")) {
        printf("%d\n", region->left);
    } else if(!strcmp(arg1, "top")) {
        printf("%d\n", region->top);
    } else if(!strcmp(arg1, "num_media")) {
        printf("%d\n", xlfparser_media_length(region));
    } else {
        failed = 1;
    }
    xlfparser_delete_layout(layout);

    return failed;
}
