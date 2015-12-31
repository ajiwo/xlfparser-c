#ifndef XLFPARSER_H
#define XLFPARSER_H
#include "xlfparser-config.h"
#include "xlflayout.h"

#ifdef	__cplusplus
extern "C" {
#endif


/**
 * @brief load a xlf file and parse it. This is the start entry of the API
 * @param filename path to xlf file
 * @return pointer to the newly created layout node
 */
Node *xlfparser_parse_file(const char *filename);

/**
 * @brief get the parsed Layout struct
 * @param xlf_node the node created previously with xlfparser_parse_file()
 * @return the parsed Layout struct
 */
Layout *xlfparser_get_layout(Node *xlf_node);

/**
 * @brief get the number of tag under given node.
 * @param xlf_node the node created previously with xlfparser_parse_file() or tags of Layout struct (Layout.tags)
 * @return the number of tag, or -1 if xlf_node's type is not XLF_NODE_LAYOUT or XLF_NODE_LAYOUT_TAG
 */
int xlfparser_tag_length(Node *xlf_node);

/**
 * @brief get layout tag at index.
 * @param xlf_node the node created previously with xlfparser_parse_file() or tags of Layout struct (Layout.tags)
 * @param index
 * @return the tag content, or NULL if xlf_node's type is not XLF_NODE_LAYOUT or XLF_NODE_LAYOUT_TAG
 */
char *xlfparser_get_tag(Node *xlf_node, int index);

/**
 * @brief get the number of region under the given node.
 * @param xlf_node the node created previously with xlfparser_parse_file() or regions of Layout struct (Layout.regions)
 * @return the number of regions, or -1 if xlf_node's type is not XLF_NODE_LAYOUT or XLF_NODE_REGION
 */
int xlfparser_region_length(Node *xlf_node);

/**
 * @brief get a region at position index
 * @param xlf_node the node created previously with xlfparser_parse_file() or regions of Layout struct (Layout.regions)
 * @param index
 * @return the Region object, or NULL if xlf_node's type is not XLF_NODE_LAYOUT or XLF_NODE_REGION
 */
Region *xlfparser_get_region(Node *xlf_node, int index);

/**
 * @brief get the number of options under the xlf_node
 * @param xlf_node the node retrieved previously with xlfparser_get_region() or options of Region struct (Region.options)
 * @return the number of region options, or -1 if xlf_node's type is not XLF_NODE_REGION or XLF_NODE_KEYVAL
 */
int xlfparser_region_option_length(Node *xlf_node);

/**
 * @brief get a region option at position index
 * @param xlf_node the node retrieved previously with xlfparser_get_region() or options of Region struct (Region.options)
 * @param index
 * @return the RegionOption object, or NULL if xlf_node's type is not XLF_NODE_REGION or XLF_NODE_KEYVAL
 */
RegionOption *xlfparser_get_region_option(Node *xlf_node, int index);

/**
 * @brief get the number of media under the given xlf_node
 * @param xlf_node the node retrieved previously with xlfparser_get_region() or media of Region struct (Region.media)
 * @return the number of media, or -1 if xlf_node's type is not XLF_NODE_REGION or XLF_NODE_MEDIA
 */
int xlfparser_media_length(Node *xlf_node);

/**
 * @brief get a media at position index
 * @param xlf_node the node retrieved previously with xlfparser_get_region() or media of Region struct (Region.media)
 * @param index
 * @return the Media object, or NULL if xlf_node's type is not XLF_NODE_REGION or XLF_NODE_MEDIA
 */
Media *xlfparser_get_media(Node *xlf_node, int index);

/**
 * @brief get the number of media options under the xlf_node
 * @param xlf_node the node retrieved previously with xlfparser_get_media() or options of Media struct (Media.options)
 * @return the number of region options, or -1 if xlf_node's type is not XLF_NODE_MEDIA or XLF_NODE_KEYVAL
 */
int xlfparser_media_option_length(Node *xlf_node);


/**
 * @brief get a media option at position index
 * @param xlf_node the node retrieved previously with xlfparser_get_media() or options of Media struct (Media.options)
 * @param index
 * @return the MediaOption object, or NULL if xlf_node's type is not XLF_NODE_MEDIA or XLF_NODE_KEYVAL
 */
MediaOption *xlfparser_get_media_option(Node *xlf_node, int index);

/**
 * @brief release/free a layout node
 * @param xlf_node the node created previously with xlfparser_parse_file()
 * @return 0 on success or -1 if the node type is not XLF_NODE_LAYOUT
 */
int xlfparser_delete_layout(Node *xlf_node);

#ifdef	__cplusplus
}
#endif


#endif /* XLFPARSER_H */
