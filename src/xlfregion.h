#ifndef XLFREGION_H
#define XLFREGION_H
#include "xlfmedia.h"

xlfNode *region_new();

int region_delete_last(xlfNode **node);
int region_delete_all(xlfNode **node);

void region_add_media(xlfNode **region_node, xlfNode *media_node);
void region_add_option(xlfNode **region_node, const char *key, const char *value);

#endif /* XLFREGION_H */

