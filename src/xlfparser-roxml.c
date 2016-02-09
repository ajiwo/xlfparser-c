#include "xlfparser-roxml.h"
#ifdef XLFPARSER_USE_LIBROXML
int is_node_name(node_t *node, const char *name) {
    int result;
    char *node_name;

    node_name = roxml_get_name(node, NULL, 0);
    result = strcmp(node_name, name) == 0 ? 1 : 0;
    roxml_release(node_name);

    return result;
}

char* get_attr_content(node_t *node, const char *name) {
    char *attr_name;
    char *attr_content;
    char *attr_result;
    node_t *attr;

    attr_name = _xlf_strcpy(name);
    attr = roxml_get_attr(node, attr_name, 0);
    free(attr_name);

    attr_content = roxml_get_content(attr, NULL, 0, NULL);

    attr_result = _xlf_strcpy(attr_content);
    roxml_release(attr_content);

    return attr_result;
}

int get_int_attr_content(node_t *node, const char *name) {
    char *attr_content;
    int attr_result = -1;

    attr_content = get_attr_content(node, name);
    attr_result = atoi(attr_content);
    free(attr_content);
    attr_content = NULL;
    return attr_result;
}

void parse_region_option(node_t *option_rnode, xlfNode *region_xnode) {
    node_t *option_child;

    char *key, *val;

    option_child = roxml_get_chld(option_rnode, NULL, 0);
    while(option_child) {
        key = roxml_get_name(option_child, NULL, 0);
        val = roxml_get_content(option_child, NULL, 0, NULL);

        region_add_option(&region_xnode, key, val);

        roxml_release(key);
        roxml_release(val);

        option_child = roxml_get_next_sibling(option_child);
    }
}

void parse_media_option(node_t *option_rnode, xlfNode *media_xnode) {
    node_t *option_child;
    char *key, *val;

    option_child = roxml_get_chld(option_rnode, NULL, 0);
    while(option_child) {
        key = roxml_get_name(option_child, NULL, 0);
        val = roxml_get_content(option_child, NULL, 0, NULL);

        media_add_option(&media_xnode, key, val);

        roxml_release(key);
        roxml_release(val);

        option_child = roxml_get_next_sibling(option_child);
    }
}

void parse_media_raw(node_t *raw_rnode, xlfNode *media_xnode) {
    node_t *raw_child;
    char *key, *val;

    raw_child = roxml_get_chld(raw_rnode, NULL, 0);
    while(raw_child) {
        key = roxml_get_name(raw_child, NULL, 0);
        val = roxml_get_content(raw_child, NULL, 0, NULL);

        media_add_raw(&media_xnode, key, val);

        roxml_release(key);
        roxml_release(val);

        raw_child = roxml_get_next_sibling(raw_child);
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

    media_child = roxml_get_chld(media_rnode, NULL, 0);
    while(media_child) {
        if(is_node_name(media_child, "options")) {
            parse_media_option(media_child, media_xnode);
        } else if(is_node_name(media_child, "raw")) {
            parse_media_raw(media_child, media_xnode);
        }
        media_child = roxml_get_next_sibling(media_child);
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

    region_child = roxml_get_chld(layout_rnode, NULL, 0);
    while(region_child) {
        if(is_node_name(region_child, "options")) {
            parse_region_option(region_child, region_xnode);
        } else if (is_node_name(region_child, "media")) {
            parse_media(region_child, region_xnode);
        }
        region_child = roxml_get_next_sibling(region_child);
    }

    layout_add_region(&layout_xnode, region_xnode);

}

void parse_tags(node_t *layout_rnode, xlfNode *layout_xnode) {
    char *tag_name;
    node_t *tag_rnode;

    tag_rnode = roxml_get_chld(layout_rnode, "tag", 0);
    while(tag_rnode) {
        if(is_node_name(tag_rnode, "tag")) {
            tag_name = roxml_get_content(tag_rnode, NULL, 0, NULL);
            layout_add_tag(&layout_xnode, tag_name);
            roxml_release(tag_name);
        }
        tag_rnode = roxml_get_next_sibling(tag_rnode);
    }
}

xlfNode *parse_layout(const char *srcfile) {
    char *xlffile;

    node_t *doc_rnode;
    node_t *layout_rnode;
    node_t *child_rnode;

    xlfNode *layout_xnode = layout_new();
    Layout *layout;


    xlffile = _xlf_strcpy(srcfile);
    doc_rnode = roxml_load_doc(xlffile);
    layout_rnode = roxml_get_chld(doc_rnode, "layout", 0);

    layout = layout_xnode->data;
    layout->width = get_int_attr_content(layout_rnode, "width");
    layout->height = get_int_attr_content(layout_rnode, "height");

    layout->bgcolor = get_attr_content(layout_rnode, "bgcolor");
    layout->background = get_attr_content(layout_rnode, "background");


    child_rnode = roxml_get_chld(layout_rnode, NULL, 0);

    while(child_rnode) {
        if(is_node_name(child_rnode, "region")) {
            parse_regions(child_rnode, layout_xnode);
        }
        if(is_node_name(child_rnode, "tags")) {
            parse_tags(child_rnode, layout_xnode);
        }
        child_rnode = roxml_get_next_sibling(child_rnode);
    }

    free(xlffile);
    xlffile = NULL;
    roxml_close(doc_rnode);
    return layout_xnode;
}
#else
void xlfparser_roxml_dummy() {}

#endif /* XLFPARSER_USE_LIBROXML */
