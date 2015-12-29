#ifndef XLFREGION_H
#define XLFREGION_H
#include "xlfmedia.h"

typedef struct _XlfKeyVal RegionOption;

typedef struct _XlfRegion {
    char *id;
    int width;
    int height;
    int left;
    int top;

    Node *media;
    Node *options;
} Region;

Node *region_new();

int region_delete_last(Node **node);
int region_delete_all(Node **node);

void region_add_media(Node **region_node, Node *media_node);
void region_add_option(Node **region_node, const char *key, const char *value);

#endif /* XLFREGION_H */

