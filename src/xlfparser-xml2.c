#include "xlfparser-xml2.h"
#ifdef XLFPARSER_USE_LIBXML2
int is_element_name(node_t *node, const char *name) {
    return node->type == XML_ELEMENT_NODE && xmlStrEqual(node->name, (const xmlChar *) name);
}

char *get_attr_content(node_t *node, const char *name) {
    xmlChar *xml_value;
    char *value;

    xml_value = xmlGetProp(node, (const xmlChar*) name);
    value = _xlf_strcpy((const char *)xml_value);
    xmlFree(xml_value);
    return value;
}

int get_int_attr_content(node_t *node, const char *name) {
    char *attr_value;
    int value;

    attr_value = get_attr_content(node, name);
    value = atoi(attr_value);
    free(attr_value);
    attr_value = NULL;
    return value;
}

void parse_region_option(node_t *option_rnode, xlfNode *region_xnode) {
    node_t *option_child;

    xmlChar *val;

    option_child = option_rnode->children;
    while(option_child) {
        if(option_child->type != XML_ELEMENT_NODE) {
            option_child = option_child->next;
            continue;
        }

        val = xmlNodeGetContent(option_child);

        region_add_option(&region_xnode, (const char *)option_child->name, (const char *)val);

        xmlFree(val);

        option_child = option_child->next;
    }
}

void parse_media_option(node_t *option_rnode, xlfNode *media_xnode) {
    node_t *option_child;
    xmlChar *val;

    option_child = option_rnode->children;
    while(option_child) {
        if(option_child->type != XML_ELEMENT_NODE) {
            option_child = option_child->next;
            continue;
        }
        val = xmlNodeGetContent(option_child);

        media_add_option(&media_xnode, (const char *) option_child->name, (const char *) val);

        xmlFree(val);

        option_child = option_child->next;
    }
}

void parse_media_raw(node_t *raw_rnode, xlfNode *media_xnode) {
    node_t *raw_child;
    char *key;
    xmlChar *val;

    raw_child = raw_rnode->children;
    while(raw_child) {
        if(raw_child->type != XML_ELEMENT_NODE) {
            raw_child = raw_child->next;
            continue;
        }
        key = _xlf_strcpy((const char*)  raw_child->name);
        val = xmlNodeGetContent(raw_child);

        media_add_raw(&media_xnode, (const char *) key, (const char *) val);

        free(key);
        xmlFree(val);

        raw_child = raw_child->next;
    }
}

void parse_media(node_t *media_rnode, xlfNode *region_xnode) {
    xlfNode *media_xnode;
    Media *media;
    node_t *media_child;

    media_xnode = media_new();
    media = media_xnode->data;

    media->id = get_attr_content(media_rnode, "id");
    media->type = get_attr_content(media_rnode, "type");
    media->render = get_attr_content(media_rnode, "render");
    media->duration = get_int_attr_content(media_rnode, "duration");

    media_child = media_rnode->children;
    while(media_child) {
        if(is_element_name(media_child, "options")) {
            parse_media_option(media_child, media_xnode);
        } else if(is_element_name(media_child, "raw")) {
            parse_media_raw(media_child, media_xnode);
        }
        media_child = media_child->next;
    }
    region_add_media(&region_xnode, media_xnode);
}


void parse_regions(node_t *layout_rnode, xlfNode *layout_xnode) {
    xlfNode *region_xnode;
    node_t *region_child;
    Region *region;

    region_xnode = region_new();
    region = region_xnode->data;

    region->width = get_int_attr_content(layout_rnode, "width");
    region->height = get_int_attr_content(layout_rnode, "height");
    region->left = get_int_attr_content(layout_rnode, "left");
    region->top = get_int_attr_content(layout_rnode, "top");
    region->id = get_attr_content(layout_rnode, "id");

    region_child = layout_rnode->children;
    while(region_child) {
        if(is_element_name(region_child, "options")) {
            parse_region_option(region_child, region_xnode);
        } else if (is_element_name(region_child, "media")) {
            parse_media(region_child, region_xnode);
        }
        region_child = region_child->next;
    }

    layout_add_region(&layout_xnode, region_xnode);

}

void parse_tags(node_t *layout_rnode, xlfNode *layout_xnode) {
    xmlChar *tag_name;
    node_t *tag_rnode;


    tag_rnode = layout_rnode->children;
    while(tag_rnode) {
        if(is_element_name(tag_rnode, "tag")) {
            tag_name = xmlNodeGetContent(tag_rnode);
            layout_add_tag(&layout_xnode, (const char *) tag_name);
            xmlFree(tag_name);
        }
        tag_rnode = tag_rnode->next;
    }
}

xlfNode *parse_layout(const char *xlf_file) {
    xmlDoc *doc;
    node_t *node, *child;
    xlfNode *layout_xnode;
    Layout *layout;

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    doc = xmlReadFile(xlf_file, NULL, 0);
    if(!doc) {
        fprintf(stderr, "ERROR: document parsing failed\n");
        return NULL;
    }
    node = xmlDocGetRootElement(doc);
    if(!node) {
        fprintf(stderr, "ERROR: empty document\n");
        xmlFreeDoc(doc);
        return NULL;
    }
    if(!is_element_name(node, "layout")) {
        fprintf(stderr, "ERROR: not a XLF file\n");
    }

    layout_xnode = layout_new();
    layout = layout_xnode->data;
    layout->width = get_int_attr_content(node, "width");
    layout->height = get_int_attr_content(node, "height");
    layout->background = get_attr_content(node, "background");
    layout->bgcolor = get_attr_content(node, "bgcolor");

    child = node->children;
    while(child) {
        if(is_element_name(child, "region")) {
            parse_regions(child, layout_xnode);
        } else if(is_element_name(child, "tags")) {
            parse_tags(child, layout_xnode);
        }
        child = child->next;
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return layout_xnode;
}

#else
void xlfparser_xml2_dummy() {}

#endif /* XLFPARSER_USE_LIBXML2 */
