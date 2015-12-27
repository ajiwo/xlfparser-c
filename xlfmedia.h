#ifndef XLFMEDIA_H
#define XLFMEDIA_H
#include "xlfkeyval.h"

typedef struct _XlfKeyVal MediaOption;
typedef struct _XlfKeyVal MediaRaw;

typedef struct _XlfMedia {
    char *id;
    char *type;
    int duration;
    char *render;

    Node *options;
    Node *raws;
} Media;

Node *media_new();
int media_append(Node **parent, Node *child);
int media_delete_last(Node **node);
int media_delete_all(Node **node);

void media_add_option(Node **media_node, const char *key, const char *value);

void media_add_raw(Node **media_node, const char *key, const char *value);


#endif /* XLFMEDIA_H */

