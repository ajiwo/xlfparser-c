#ifndef XLFPARSER_H
#define XLFPARSER_H
#include "xlfparser-config.h"
#ifdef XLFPARSER_USE_LIBROXML
#include "xlfparser-roxml.h"
#endif

#ifdef XLFPARSER_USE_LIBXML2
#include "xlfparser-xml2.h"
#endif

#endif /* XLFPARSER_H */
