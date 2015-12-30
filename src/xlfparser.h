#ifndef XLFPARSER_H
#define XLFPARSER_H
#include "xlfparser-config.h"
#include "xlflayout.h"

Node *xlfparser_parse_file(const char *filename);
Layout *xlfparser_get_layout(Node *layout_xnode);
int xlfparser_region_length(Node *layout_xnode);
Region *xlfparser_get_region(Node *layout_xnode, int index);
char *xlfparser_get_tag(Node *layout_xnode, int index);
Media *xlfparser_get_media(Node *region_xnode, int index);
MediaOption *xlfparser_get_media_option(Node *media_xnode, int index);


#endif /* XLFPARSER_H */
