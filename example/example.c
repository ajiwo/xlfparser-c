#include "xlfparser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char **argv) {
    Layout *layout;
    Region *region;
    Media *media;
    xlfNode *layout_xnode;
    xlfNode *region_xnode;
    xlfNode *media_xnode;

    int i;
    int length;

    if (argc != 2) {
        return(1);
    }

    /* use API { */

    /* the main function, got everything inside layout_xnode which can be iterate thru, see 'iterate way'*/
    layout_xnode = xlfparser_parse_file(argv[1]);

    /* let's try the public API */
    layout = xlfparser_get_layout(layout_xnode);
    printf("layout width: %d, height: %d, bgcolor: '%s' background: '%s'\n",
           layout->width,
           layout->height,
           layout->bgcolor,
           layout->background);
    length = xlfparser_node_length(layout->regions);
    for(i = 0; i < length; i++) {
        region = xlfparser_get_region(layout->regions, i);
        printf("region id: '%s', width: %d, height: %d, left: %d, top: %d\n",
               region->id,
               region->width,
               region->height,
               region->left,
               region->top);
    }
    /* use API  } */

    printf("----\n");

    /* iterate way, only use xlfparser_parse_file from above */
    region_xnode = layout->regions;
    region_xnode = region_xnode->first;
    region = region_xnode->data;
    while(region_xnode) {
        printf("region id: '%s', width: %d, height: %d, left: %d, top: %d\n",
               region->id,
               region->width,
               region->height,
               region->left,
               region->top);

        /* iterate media within this region { */
        media_xnode = region->media;
        media_xnode = media_xnode->first;
        media = media_xnode->data;
        while(media_xnode) {
            printf("  media id: '%s', type: '%s', render: '%s', duration: %d\n",
                   media->id,
                   media->type,
                   media->render,
                   media->duration);
            /*
               // iterate media option
               media_option_xnode = media->options;
               media_option_xnode = media_option_xnode->first;
               media_option = media_option_xnode->data;
               while(media_option_xnode) {
                  .....
               }
            */

            media_xnode = media_xnode->next;
            media = media_xnode ? media_xnode->data : NULL;
        }
        /* iterate media within this region } */

        /*
           // iterate region option
           region_option_xnode = region->options;
           region_option_xnode = region_option_xnode->first;
           region_option = region_option_xnode->data;
           while(region_option_xnode) {
              .....
           }
        */


        region_xnode = region_xnode->next;
        region = region_xnode ? region_xnode->data : NULL;
    }




    return xlfparser_delete_layout(layout_xnode);
}
