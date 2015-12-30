#include "xlfparser.h"

#ifdef XLFPARSER_USE_LIBROXML
#include "xlfparser-roxml.h"
#endif

#ifdef XLFPARSER_USE_LIBXML2
#include "xlfparser-xml2.h"
#endif

Node *xlfparser_parse_file(const char *filename) {
    return parse_layout(filename);
}

Layout *xlfparser_get_layout(Node *layout_xnode) {
    return (Layout *) layout_xnode->data;
}

int xlfparser_region_length(Node *layout_xnode) {
    Layout *layout;

    layout = layout_xnode->data;
    return node_length(layout->regions);
}

Region *xlfparser_get_region(Node *region_xnode, int index) {
    Node *_region_xnode = node_get(region_xnode, index);
    return _region_xnode->data;
}

RegionOption *xlfparser_get_region_option(Node *option_xnode, int index) {
    Node *_option_xnode;

    _option_xnode = node_get(option_xnode, index);
    return _option_xnode->data;
}

char *xlfparser_get_tag(Node *layout_xnode, int index) {
    Layout *layout;
    LayoutTag *tag;
    Node *tags_xnode;
    int length;

    layout = layout_xnode->data;
    tags_xnode = layout->tags;
    length = node_length(tags_xnode);

    if(index < 0 || index >= length) {
        return NULL;
    }
    node_at(&tags_xnode, index);
    tag = tags_xnode->data;
    return tag->tag;
}

Media *xlfparser_get_media(Node *media_xnode, int index) {
    Node *_media_xnode;

    _media_xnode = node_get(media_xnode, index);
    return _media_xnode->data;
}

MediaOption *xlfparser_get_media_option(Node *option_xnode, int index) {
    Node *_option_xnode;

    _option_xnode = node_get(option_xnode, index);
    return _option_xnode->data;
}
