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

Layout *xlfparser_get_layout(Node *xlf_node) {
    return (Layout *) xlf_node->data;
}

int xlfparser_region_length(Node *xlf_node) {
    Layout *layout;

    if(xlf_node->_type == XLF_NODE_REGION) {
        return node_length(xlf_node);
    }
    if(xlf_node->_type == XLF_NODE_LAYOUT) {
        layout = xlf_node->data;
        return node_length(layout->regions);
    }

    return -1;
}

Region *xlfparser_get_region(Node *xlf_node, int index) {
    Layout *layout;
    Node *region_node;
    /* TODO: implement this technique to other similar function */
    if(xlf_node->_type == XLF_NODE_REGION) {
        region_node = node_get(xlf_node, index);
    } else if(xlf_node->_type == XLF_NODE_LAYOUT) {
        layout = xlf_node->data;
        region_node = node_get(layout->regions, index);
    } else {
        region_node = NULL;
    }
    return region_node ? region_node->data : NULL;
}

int xlfparser_region_option_length(Node *xlf_node) {
    Region *region;

    if(xlf_node->_type == XLF_NODE_KEYVAL) {
        return node_length(xlf_node);
    }
    if(xlf_node->_type == XLF_NODE_REGION) {
        region = xlf_node->data;
        return node_length(region->options);
    }

    return -1;
}

RegionOption *xlfparser_get_region_option(Node *xlf_node, int index) {
    Region *region;
    Node *option_list;
    Node *option_node;
    /* TODO: implement this technique to other similar function */
    if(xlf_node->_type == XLF_NODE_REGION) {
        region = xlf_node->data;
        option_list = region->options;
        option_node = node_get(option_list, index);
    } else if(xlf_node->_type == XLF_NODE_KEYVAL) {
        option_node = node_get(xlf_node, index);
    } else {
        option_node = NULL;
    }
    return option_node ? option_node->data : NULL;
}

int xlfparser_tag_length(Node *xlf_node) {
    Layout *layout;

    if(xlf_node->_type == XLF_NODE_LAYOUT_TAG) {
        return node_length(xlf_node);
    } else if(xlf_node->_type == XLF_NODE_LAYOUT) {
        layout = xlf_node->data;
        return node_length(layout->tags);
    } else {
        return -1;
    }
}

int xlfparser_media_length(Node *xlf_node) {
    Region *region;

    if(xlf_node->_type == XLF_NODE_MEDIA) {
        return node_length(xlf_node);
    } else if(xlf_node->_type == XLF_NODE_REGION) {
        region = xlf_node->data;
        return node_length(region->media);
    } else {
        return -1;
    }
}

char *xlfparser_get_tag(Node *xlf_node, int index) {
    Layout *layout;
    Node *tag_node;

    if(xlf_node->_type == XLF_NODE_LAYOUT_TAG) {
        tag_node = node_get(xlf_node, index);
    } else if(xlf_node->_type == XLF_NODE_LAYOUT) {
        layout = xlf_node->data;
        tag_node = node_get(layout->tags, index);
    } else {
        tag_node = NULL;
    }
    return tag_node ? ((LayoutTag *)(tag_node)->data)->tag : NULL;
}

Media *xlfparser_get_media(Node *xlf_node, int index) {
    Region *region;
    Node *media_node;

    if(xlf_node->_type == XLF_NODE_MEDIA) {
        media_node = node_get(xlf_node, index);
    } else if(xlf_node->_type == XLF_NODE_REGION) {
        region = xlf_node->data;
        media_node = region->media;
    } else {
        media_node = NULL;
    }

    return media_node ? media_node->data : NULL;
}

int xlfparser_media_option_length(Node *xlf_node) {
    Media *media;

    if(xlf_node->_type == XLF_NODE_KEYVAL) {
        return node_length(xlf_node);
    }
    if(xlf_node->_type == XLF_NODE_MEDIA) {
        media = xlf_node->data;
        return node_length(media->options);
    }

    return -1;
}


MediaOption *xlfparser_get_media_option(Node *xlf_node, int index) {
    Media *media;
    Node *option_node;
    /* TODO: implement this technique to other similar function */
    if(xlf_node->_type == XLF_NODE_MEDIA) {
        media = xlf_node->data;
        option_node = node_get(media->options, index);
    } else if(xlf_node->_type == XLF_NODE_KEYVAL) {
        option_node = node_get(xlf_node, index);
    } else {
        option_node = NULL;
    }
    return option_node ? option_node->data : NULL;
}

int xlfparser_delete_layout(Node *xlf_node) {

    if(xlf_node == NULL || xlf_node->_type != XLF_NODE_LAYOUT) {
        return -1;
    }
    return layout_delete_all(&xlf_node);
}
