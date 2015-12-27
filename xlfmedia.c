#include "xlfmedia.h"

Node *media_new() {
    Node *node = node_new();
    Media *media = malloc(sizeof(Media));
    media->options = NULL;
    media->raws = NULL;
    node->data = (Media *) media;
    node->_type = XLF_NODE_MEDIA;
    return node;
}
/**
 * @see node_append()
 */
int media_append(Node **parent, Node *child) {
    return node_append(parent, child);
}

int media_delete_last(Node **node) {
    Node *last;
    Media *media;

    last = (*node)->last;
    media = last->data;

    keyval_delete_all(&(media->options));
    keyval_delete_all(&(media->raws));

    free(media);
    media = NULL;

    return node_delete_last(node);
}

int media_delete_all(Node **node) {
    while(*node) {
        media_delete_last(node);
    }
    return node_length(*node);
}

void media_add_option(Node **media_node, const char *key, const char *value) {
    Media *media;

    media = (*media_node)->data;
    if(!media->options) {
        media->options = keyval_new(key, value);
    } else {
        keyval_append(&(media->options), key, value);
    }
}

void media_add_raw(Node **media_node, const char *key, const char *value) {
    Media *media;

    media = (*media_node)->data;
    if(!media->raws) {
        media->raws = keyval_new(key, value);
    } else {
        keyval_append(&(media->options), key, value);
    }
}
