#include "xlflayout.h"

xlfNode *layout_new() {
    xlfNode *node;
    Layout *layout;

    layout = malloc(sizeof(Layout));
    layout->regions = NULL;
    layout->tags = NULL;
    layout->background = NULL;
    layout->bgcolor = NULL;

    node = node_new(XLF_NODE_LAYOUT);
    node->data = (Layout *) layout;

    layout->_node = node;
    return node;
}

int layout_delete_last(xlfNode **node) {
    xlfNode *last;
    Layout *layout;

    if(!node || !(*node)) {
        return -1;
    }

    last = (*node)->last;
    layout = last->data;

    tag_delete_all(&(layout->tags));
    region_delete_all(&(layout->regions));

    if(layout->bgcolor) {
        free(layout->bgcolor);
        layout->bgcolor = NULL;
    }

    if(layout->background) {
        free(layout->background);
        layout->background = NULL;
    }
    free(layout);
    layout = NULL;

    return node_delete_last(node);
}

int layout_delete_all(xlfNode **node) {
    while(*node) {
        layout_delete_last(node);
    }

    return node_length(*node);
}

void layout_add_region(xlfNode **layout_node, xlfNode *region_node) {
    Layout *layout;

    layout = (*layout_node)->data;
    if(!layout->regions) {
        layout->regions = region_node;
    } else {
        node_append(&(layout->regions), region_node);
    }
}


void layout_add_tag(xlfNode **layout_node, const char *tagname) {
    Layout *layout;

    layout = (*layout_node)->data;
    if(!layout->tags) {
        layout->tags = tag_new(tagname);
    } else {
        node_append(&(layout->tags), tag_new(tagname));
    }
}

xlfNode *tag_new(const char *tagname) {
    xlfNode *node;
    LayoutTag *tag;

    tag = malloc(sizeof(LayoutTag));
    tag->tag = _xlf_strcpy(tagname);

    node = node_new(XLF_NODE_LAYOUT_TAG);
    node->data = (LayoutTag *) tag;


    return node;
}

int tag_delete_last(xlfNode **node) {
    xlfNode *last;
    LayoutTag *tag;

    if(!node || !(*node)) {
        return -1;
    }

    last = (*node)->last;
    tag = last->data;

    free(tag->tag);
    tag->tag = NULL;

    free(tag);
    tag = NULL;

    return node_delete_last(node);

}

int tag_delete_all(xlfNode **node) {
    while(*node) {
        tag_delete_last(node);
    }

    return node_length(*node);
}
