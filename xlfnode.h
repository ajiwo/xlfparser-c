#ifndef XLFNODE_H
#define XLFNODE_H

#include <stdlib.h>
#include "xlfparser-data.h"

/**
 * @brief create an new node.
 * @return pointer to the newly created node or NULL if failed
 */
Node *node_new();

/**
 * @brief append an initialized child node to the end of nodes.
 * @param parent the existing node with at least contains one node
 * @param child node to be appended, created by node_new()
 * @return the new parent length/size after appending the child, or 0 if failed.
 * @see node_new()
 */
int node_append(Node **parent, Node *child);

/**
 * @brief get the length/size of a given node.
 * @param node
 * @return the node length/size
 */
int node_length(Node *node);

/**
 * @brief delete the last child of a given node.
 * @param node
 * @return the node length after deletion
 */
int node_delete_last(Node **node);

/**
 * @brief completely delete a node.
 * @param node
 * @return the length of node after deletion.
 */
int node_delete_all(Node **node);

#endif /* XLFNODE_H */

