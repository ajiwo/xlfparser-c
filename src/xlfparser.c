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
    return (Layout *) xlf_node->data;
}

int xlfparser_region_length(xlfNode *xlf_node) {
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

Region *xlfparser_get_region(xlfNode *xlf_node, int index) {
    Layout *layout = NULL;
    xlfNode *region_node = NULL;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_REGION) {
            region_node = node_get(xlf_node, index);
        } else if(xlf_node->_type == XLF_NODE_LAYOUT) {
            layout = xlf_node->data;
            region_node = node_get(layout->regions, index);
        } else {
            region_node = NULL;
        }
    }

    return region_node ? region_node->data : NULL;
}

int xlfparser_region_option_length(xlfNode *xlf_node) {
    Region *region;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_REGION_OPTION) {
            return node_length(xlf_node);
        }
        if(xlf_node->_type == XLF_NODE_REGION) {
            region = xlf_node->data;
            return node_length(region->options);
        }
    }

    return -1;
}

RegionOption *xlfparser_get_region_option(xlfNode *xlf_node, int index) {
    Region *region;
    xlfNode *option_list;
    xlfNode *option_node = NULL;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_REGION) {
            region = xlf_node->data;
            option_list = region->options;
            option_node = node_get(option_list, index);
        } else if(xlf_node->_type == XLF_NODE_REGION_OPTION) {
            option_node = node_get(xlf_node, index);
        } else {
            option_node = NULL;
        }
    }
    return option_node ? option_node->data : NULL;
}

int xlfparser_tag_length(xlfNode *xlf_node) {
    Layout *layout;

    if(xlf_node == NULL) {
        return -1;
    }
    if(xlf_node->_type == XLF_NODE_LAYOUT_TAG) {
        return node_length(xlf_node);
    } else if(xlf_node->_type == XLF_NODE_LAYOUT) {
        layout = xlf_node->data;
        return node_length(layout->tags);
    } else {
        return -1;
    }
}

int xlfparser_media_length(xlfNode *xlf_node) {
    Region *region;

    if(xlf_node == NULL) {
        return -1;
    }

    if(xlf_node->_type == XLF_NODE_MEDIA) {
        return node_length(xlf_node);
    } else if(xlf_node->_type == XLF_NODE_REGION) {
        region = xlf_node->data;
        return node_length(region->media);
    } else {
        return -1;
    }
}

char *xlfparser_get_tag(xlfNode *xlf_node, int index) {
    Layout *layout;
    xlfNode *tag_node = NULL;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_LAYOUT_TAG) {
            tag_node = node_get(xlf_node, index);
        } else if(xlf_node->_type == XLF_NODE_LAYOUT) {
            layout = xlf_node->data;
            tag_node = node_get(layout->tags, index);
        } else {
            tag_node = NULL;
        }
    }
    return tag_node ? ((LayoutTag *)(tag_node)->data)->tag : NULL;
}

Media *xlfparser_get_media(xlfNode *xlf_node, int index) {
    Region *region;
    xlfNode *media_node = NULL;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_MEDIA) {
            media_node = node_get(xlf_node, index);
        } else if(xlf_node->_type == XLF_NODE_REGION) {
            region = xlf_node->data;
            media_node = region->media;
        } else {
            media_node = NULL;
        }
    }

    return media_node ? media_node->data : NULL;
}

int xlfparser_media_option_length(xlfNode *xlf_node) {
    Media *media;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_MEDIA_OPTION) {
            return node_length(xlf_node);
        }
        if(xlf_node->_type == XLF_NODE_MEDIA) {
            media = xlf_node->data;
            return node_length(media->options);
        }
    }

    return -1;
}

MediaOption *xlfparser_get_media_option(xlfNode *xlf_node, int index) {
    Media *media;
    xlfNode *option_node = NULL;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_MEDIA) {
            media = xlf_node->data;
            option_node = node_get(media->options, index);
        } else if(xlf_node->_type == XLF_NODE_MEDIA_OPTION) {
            option_node = node_get(xlf_node, index);
        } else {
            option_node = NULL;
        }
    }
    return option_node ? option_node->data : NULL;
}

int xlfparser_media_raw_length(xlfNode *xlf_node) {
    Media *media;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_MEDIA_RAW) {
            return node_length(xlf_node);
        }
        if(xlf_node->_type == XLF_NODE_MEDIA) {
            media = xlf_node->data;
            return node_length(media->raws);
        }
    }

    return -1;
}

MediaRaw *xlfparser_get_media_raw(xlfNode *xlf_node, int index) {
    Media *media;
    xlfNode *option_node = NULL;

    if(xlf_node) {
        if(xlf_node->_type == XLF_NODE_MEDIA) {
            media = xlf_node->data;
            option_node = node_get(media->raws, index);
        } else if(xlf_node->_type == XLF_NODE_MEDIA_RAW) {
            option_node = node_get(xlf_node, index);
        } else {
            option_node = NULL;
        }

    }
    return option_node ? option_node->data : NULL;
}

int xlfparser_delete_layout(xlfNode *xlf_node) {

    if(xlf_node == NULL || xlf_node->_type != XLF_NODE_LAYOUT) {
        return -1;
    }
    return layout_delete_all(&xlf_node);
}

int xlfparser_node_length(xlfNode *xlf_node) {
    return node_length(xlf_node);
}
