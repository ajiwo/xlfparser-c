#ifndef XLFPARSERLIBXML2_H
#define XLFPARSERLIBXML2_H

#ifdef XLFPARSER_USE_LIBXML2
#include <libxml/xmlreader.h>
#include "xlflayout.h"
typedef xmlNode node_t;
Node *parse_layout(const char *xlf_file);
#else
void xlfparser_xml2_dummy();

#endif /* XLFPARSER_USE_LIBXML2 */
#endif /* XLFPARSERLIBXML2_H */

