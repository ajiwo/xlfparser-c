#ifndef XLFMEDIA_H
#define XLFMEDIA_H
#include "xlfkeyval.h"

Node *media_new();
int media_append(Node **parent, Node *child);
int media_delete_last(Node **node);
int media_delete_all(Node **node);

void media_add_option(Node **media_node, const char *key, const char *value);

void media_add_raw(Node **media_node, const char *key, const char *value);


#endif /* XLFMEDIA_H */

