#include "xlflayout.h"
#include "xlfparser.h"

#ifdef XLFPARSER_USE_LIBROXML
#include "xlfparser-roxml.h"
#endif

#ifdef XLFPARSER_USE_LIBXML2
#include "xlfparser-xml2.h"
#endif

xlfNode *xlfparser_parse_file(const char *filename) {
    return parse_layout(filename);
}

Layout *xlfparser_get_layout(xlfNode *xlf_node) {
    if(xlf_node == NULL) {
        return NULL;
    }
    return (Layout *) xlf_node->data;
}

int xlfparser_region_length(Layout *layout) {

    if(layout == NULL) {
        return -1;
    }

    return node_length(layout->regions);
}

Region *xlfparser_get_region(Layout *layout, int index) {
    xlfNode *node;

    if(layout == NULL) {
        return NULL;
    }

    node = node_get(layout->regions, index);
    return node ? node->data : NULL;
}

int xlfparser_region_option_length(Region *region) {
    if(region == NULL) {
        return -1;
    }
    return node_length(region->options);
}

RegionOption *xlfparser_get_region_option(Region *region, int index) {
    xlfNode *node;
    if(region == NULL) {
        return NULL;
    }
    node = node_get(region->options, index);
    return node ? node->data : NULL;
}

int xlfparser_tag_length(Layout *layout) {
    if(layout == NULL) {
        return -1;
    }

    return node_length(layout->tags);
}

int xlfparser_media_length(Region *region) {
    if(region == NULL) {
        return -1;
    }
    return node_length(region->media);
}

char *xlfparser_get_tag(Layout *layout, int index) {
    xlfNode *node;

    if(layout == NULL) {
        return NULL;
    }
    node = node_get(layout->tags, index);
    return node ? ((LayoutTag *)(node)->data)->tag : NULL;
}

Media *xlfparser_get_media(Region *region, int index) {
    xlfNode *node;
    if(region == NULL) {
        return NULL;
    }
    node = node_get(region->media, index);
    return node ? node->data : NULL;
}

int xlfparser_media_option_length(Media *media) {
    if(media == NULL) {
        return -1;
    }
    return node_length(media->options);
}

MediaOption *xlfparser_get_media_option(Media *media, int index) {
    xlfNode *node;
    if(media == NULL) {
        return NULL;
    }
    node = node_get(media->options, index);
    return node ? node->data : NULL;
}

int xlfparser_media_raw_length(Media *media) {
    if(media == NULL) {
        return -1;
    }
    return node_length(media->raws);
}

MediaRaw *xlfparser_get_media_raw(Media *media, int index) {
    xlfNode *node;

    if(media == NULL) {
        return NULL;
    }
    node = node_get(media->raws, index);
    return node ? node->data : NULL;
}

int xlfparser_delete_layout(Layout *layout) {
    xlfNode *node;
    if(layout == NULL || layout->_node == NULL) {
        return -1;
    }
    node = layout->_node;
    return layout_delete_all(&node);
}

int xlfparser_node_length(xlfNode *xlf_node) {
    return node_length(xlf_node);
}
