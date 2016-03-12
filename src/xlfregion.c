#include "xlfregion.h"

xlfNode *region_new() {
    xlfNode *node;
    Region *region;

    region = malloc(sizeof(Region));
    region->media = NULL;
    region->options = NULL;

    node = node_new(XLF_NODE_REGION);
    node->data = (Region *) region;
    region->_node = node;

    return node;
}

int region_delete_last(xlfNode **node) {
    xlfNode *last;
    Region *region;

    if(!node || !(*node)) {
        return -1;
    }

    last = (*node)->last;
    region = last->data;

    keyval_delete_all(&(region->options));
    media_delete_all(&(region->media));

    free(region->id);
    region->id = NULL;
    free(region);
    region = NULL;

    return node_delete_last(node);
}

int region_delete_all(xlfNode **node) {
    while(*node) {
        region_delete_last(node);
    }

    return node_length(*node);
}

void region_add_media(xlfNode **region_node, xlfNode *media_node) {
    Region *region;

    region = (*region_node)->data;
    if(!region->media) {
        region->media = media_node;
    } else {
        node_append(&(region->media), media_node);
    }
}

void region_add_option(xlfNode **region_node, const char *key, const char *value) {
    Region *region;

    region = (*region_node)->data;
    if(!region->options) {
        region->options = keyval_new(key, value, XLF_NODE_REGION_OPTION);
    } else {
        keyval_append(&(region->options), key, value, XLF_NODE_REGION_OPTION);
    }
}
