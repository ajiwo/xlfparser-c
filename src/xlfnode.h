#ifndef XLFNODE_H
#define XLFNODE_H

#include <stdlib.h>
#include <string.h>

#include "xlfparser-data.h"

/**
 * @brief create an new node.
 * @return pointer to the newly created node or NULL if failed
 */
xlfNode *node_new();

/**
 * @brief append an initialized child node to the end of nodes.
 * @param parent the existing node which at least contains one node
 * @param child node to be appended, created by node_new()
 * @return the new parent length/size after appending the child, or 0 if failed.
 * @see node_new()
 */
int node_append(xlfNode **parent, xlfNode *child);


/**
 * @brief get the length/size of a given node.
 * @param node
 * @return the node length/size
 */
int node_length(xlfNode *node);

/**
 * @brief get a node from list
 * @param node
 * @param index
 * @return the node at index or NULL if failed.
 */
xlfNode *node_get(xlfNode *node, int index);

/**
 * @brief delete the last child of a given node.
 * @param node
 * @return the node length after deletion
 */
int node_delete_last(xlfNode **node);

/**
 * @brief completely delete a node.
 * @param node
 * @return the length of node after deletion.
 */
int node_delete_all(xlfNode **node);

/**
 * @brief helper for copying string
 * @param src source string
 * @return pointer to the copied string.
 */
char *_xlf_strcpy(const char *src);
#endif /* XLFNODE_H */

