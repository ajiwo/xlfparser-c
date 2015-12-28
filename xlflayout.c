#include "xlflayout.h"

Node *layout_new() {
    Node *node;
    Layout *layout;

    layout = malloc(sizeof(Layout));
    layout->regions = NULL;
    layout->tags = NULL;

    node = node_new();
    node->data = (Layout *) layout;
    node->_type = XLF_NODE_LAYOUT;

    return node;
}

int layout_delete_last(Node **node) {
    Node *last;
    Layout *layout;

    if(!node || !(*node)) {
        return -1;
    }

    last = (*node)->last;
    layout = last->data;

    tag_delete_all(&(layout->tags));
    region_delete_all(&(layout->regions));

    free(layout->bgcolor);
    layout->bgcolor = NULL;
    free(layout->background);
    layout->background = NULL;
    free(layout);
    layout = NULL;

    return node_delete_last(node);
}

int layout_delete_all(Node **node) {
    while(*node) {
        layout_delete_last(node);
    }

    return node_length(*node);
}

void layout_add_region(Node **layout_node, Node *region_node) {
    Layout *layout;

    layout = (*layout_node)->data;
    if(!layout->regions) {
        layout->regions = region_node;
    } else {
        node_append(&(layout->regions), region_node);
    }
}


void layout_add_tag(Node **layout_node, const char *tagname) {
    Layout *layout;

    layout = (*layout_node)->data;
    if(!layout->tags) {
        layout->tags = tag_new(tagname);
    } else {
        node_append(&(layout->tags), tag_new(tagname));
    }
}

Node *tag_new(const char *tagname) {
    Node *node;
    LayoutTag *tag;

    char *_tagname;
    int len;

    len = strlen(tagname);
    _tagname = malloc(len + 1);
    _tagname[len] = '\0';

    tag = malloc(sizeof(LayoutTag));
    tag->tag = memcpy(_tagname, tagname, len);

    node = node_new();
    node->data = (LayoutTag *) tag;
    node->_type = XLF_NODE_LAYOUT_TAG;

    return node;
}

int tag_delete_last(Node **node) {
    Node *last;
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

int tag_delete_all(Node **node) {
    while(*node) {
        tag_delete_last(node);
    }

    return node_length(*node);
}
