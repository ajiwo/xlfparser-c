#ifndef XLFPARSER_H
#define XLFPARSER_H
#include "xlfparser-config.h"
#include "xlfparser-data.h"

#ifdef	__cplusplus
extern "C" {
#endif

/** FIXME: messy doc */

/**
 * @brief load a xlf file and parse it. This is the start entry of the API
 * @param filename path to xlf file
 * @return pointer to the newly created layout node or NULL if failed
 */
xlfNode *xlfparser_parse_file(const char *filename, int *nr, int *nt);

/**
 * @brief get the parsed Layout struct
 * @param xlf_node the node created previously with xlfparser_parse_file()
 * @return a pointer to the parsed Layout struct or NULL if failed
 */
Layout *xlfparser_get_layout(xlfNode *xlf_node);

/**
 * @brief get the number of tag under given node.
 * @param the layout retrieved previously with xlfparser_get_layout().
 * @return the number of LayoutTag object, or -1 if failed
 */
int xlfparser_tag_length(Layout *layout);

/**
 * @brief get layout tag at index.
 * @param the layout retrieved previously with xlfparser_get_layout().
 * @param index
 * @return the tag content, or NULL if failed.
 */
char *xlfparser_get_tag(Layout *layout, int index);

/**
 * @brief get the number of region under the given node.
 * @param the layout retrieved previously with xlfparser_get_layout().
 * @return the number Region object, or -1 if failed.
 */
int xlfparser_region_length(Layout *layout);

/**
 * @brief get a region at position index
 * @param layout retrieved previously with xlfparser_get_layout().
 * @param index
 * @param no the number of region option.
 * @param nm the number of media inside the region.
 * @return the Region object, or NULL if failed.
 */
Region *xlfparser_get_region(Layout *layout, int index, int *no, int *nm);

/**
 * @brief get the number of options under the xlf_node
 * @param the region retrieved previously with xlfparser_get_region().
 * @return the number of RegionOption object, or -1 if failed.
 */
int xlfparser_region_option_length(Region *region);

/**
 * @brief get a region option at position index
 * @param region the region retrieved previously with xlfparser_get_region().
 * @param index the index of option to fetch, ignored if key is not NULL,
 * @param key the key to search
 * @return the RegionOption object, or NULL if failed.
 */
RegionOption *xlfparser_get_region_option(Region *region, int index, const char *key);

/**
 * @brief get the number of media under the given xlf_node
 * @param the region retrieved previously with xlfparser_get_region().
 * @return the number of Media object, or -1 if failed.
 */
int xlfparser_media_length(Region *region);

/**
 * @brief get a media at position index
 * @param the region retrieved previously with xlfparser_get_region().
 * @param index
 * @return the Media object, or NULL if failed.
 */
Media *xlfparser_get_media(Region *region, int index);

/**
 * @brief get the number of media options under the xlf_node
 * @param the media retrieved previously with xlfparser_get_media().
 * @return the number of MediaOption object, or -1 if failed.
 */
int xlfparser_media_option_length(Media *media);


/**
 * @brief get a media option at position index
 * @param the media retrieved previously with xlfparser_get_media().
 * @param index the index of option to fetch, ignored if key is not NULL,
 * @param key the key to search
 * @return the MediaOption object, or NULL if failed.
 */
MediaOption *xlfparser_get_media_option(Media *media, int index, const char *key);

/**
 * @brief get the number of media raw under the xlf_node
 * @param the media retrieved previously with xlfparser_get_media().
 * @return the number of MediaRaw object, or -1 if failed.
 */
int xlfparser_media_raw_length(Media *media);

/**
 * @brief get a media raw at position index
 * @param the media retrieved previously with xlfparser_get_media().
 * @param index
 * @return the MediaRaw object, or NULL if failed.
 */
MediaRaw *xlfparser_get_media_raw(Media *media, int index);

/**
 * @brief release/free a layout node
 * @param the layout retrieved previously with xlfparser_get_layout().
 * @return 0 on success or -1 if failed.
 */
int xlfparser_delete_layout(Layout *layout);


int xlfparser_node_length(xlfNode *xlf_node);
#ifdef	__cplusplus
}
#endif


#endif /* XLFPARSER_H */
