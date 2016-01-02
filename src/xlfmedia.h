#ifndef XLFMEDIA_H
#define XLFMEDIA_H
#include "xlfkeyval.h"

xlfNode *media_new();
int media_append(xlfNode **parent, xlfNode *child);
int media_delete_last(xlfNode **node);
int media_delete_all(xlfNode **node);

void media_add_option(xlfNode **media_node, const char *key, const char *value);

void media_add_raw(xlfNode **media_node, const char *key, const char *value);


#endif /* XLFMEDIA_H */

