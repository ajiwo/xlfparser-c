#ifndef XLFLAYOUT_H
#define XLFLAYOUT_H
#include "xlfregion.h"

Node *layout_new();
int layout_delete_last(Node **node);
int layout_delete_all(Node **node);

void layout_add_region(Node **layout_node, Node *region_node);
void layout_add_tag(Node **layout_node, const char *tagname);

Node *tag_new(const char *tagname);
int tag_delete_last(Node **node);
int tag_delete_all(Node **node);
#endif /* XLFLAYOUT_H */

