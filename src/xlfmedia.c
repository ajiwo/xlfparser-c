#include "xlfmedia.h"

xlfNode *media_new() {
    xlfNode *node = node_new();
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
int media_append(xlfNode **parent, xlfNode *child) {
    return node_append(parent, child);
}

int media_delete_last(xlfNode **node) {
    xlfNode *last;
    Media *media;

    if(!node || !(*node)) {
        return -1;
    }

    last = (*node)->last;
    media = last->data;

    keyval_delete_all(&(media->options));
    keyval_delete_all(&(media->raws));
    free(media->id);
    media->id = NULL;
    free(media->type);
    media->type = NULL;
    free(media->render);
    media->render = NULL;
    free(media);
    media = NULL;

    return node_delete_last(node);
}

int media_delete_all(xlfNode **node) {
    while(*node) {
        media_delete_last(node);
    }
    return node_length(*node);
}

void media_add_option(xlfNode **media_node, const char *key, const char *value) {
    Media *media;

    media = (*media_node)->data;
    if(!media->options) {
        media->options = keyval_new(key, value);
    } else {
        keyval_append(&(media->options), key, value);
    }
}

void media_add_raw(xlfNode **media_node, const char *key, const char *value) {
    Media *media;

    media = (*media_node)->data;
    if(!media->raws) {
        media->raws = keyval_new(key, value);
    } else {
        keyval_append(&(media->options), key, value);
    }
}
