#ifndef XLFLAYOUT_H
#define XLFLAYOUT_H
#include "xlfregion.h"

xlfNode *layout_new();
int layout_delete_last(xlfNode **node);
int layout_delete_all(xlfNode **node);

void layout_add_region(xlfNode **layout_node, xlfNode *region_node);
void layout_add_tag(xlfNode **layout_node, const char *tagname);

xlfNode *tag_new(const char *tagname);
int tag_delete_last(xlfNode **node);
int tag_delete_all(xlfNode **node);
#endif /* XLFLAYOUT_H */

