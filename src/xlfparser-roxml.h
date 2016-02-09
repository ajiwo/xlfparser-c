#ifndef XLFPARSER_ROXML_H
#define XLFPARSER_ROXML_H

#include "xlfparser-config.h"

#ifdef XLFPARSER_USE_LIBROXML
#include <roxml.h>
#include "xlflayout.h"

xlfNode *parse_layout(const char *xlf_file, int *nr, int *nt);
#else
void xlfparser_roxml_dummy();
#endif /* XLFPARSER_USE_LIBROXML */
#endif /* XLFPARSER_ROXML_H */

