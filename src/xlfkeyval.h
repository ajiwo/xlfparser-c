#ifndef XLFKEYVAL_H
#define XLFKEYVAL_H

#include "xlfnode.h"


/**
 * @brief create a new key:value node
 * @return pointer to the newly created node or NULL if failed
 */
xlfNode *keyval_new(const char *key, const char *value);

/**
 * @brief append an initialized child node to the end of nodes.
 * @param parent the existing keyval node which at least contains one node
 * @param key
 * @param value
 * @return the new parent length/size after appending the child, or 0 if failed.
 * @see keyval_new()
 */
int keyval_append(xlfNode **parent, const char *key, const char *value);

/**
 * @brief delete the last child of a given keyval node.
 * @param node
 * @return the keyval node length after deletion
 */
int keyval_delete_last(xlfNode **node);

/**
 * @brief completely delete a keyval node.
 * @param node
 * @return the length of node after deletion.
 */
int keyval_delete_all(xlfNode **node);
#endif /* XLFKEYVAL_H */
