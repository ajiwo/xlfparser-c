#include "xlfkeyval.h"

/**
 * @brief create a new keyval node with initial key and value
 * @param key
 * @param value
 * @return pointer to the newly created node or NULL if failed
 */
xlfNode *keyval_new(const char *key, const char *value, NodeType type) {
    xlfNode *node;
    KeyVal *keyval;

    node = node_new(type);
    keyval = malloc(sizeof(KeyVal));
    keyval->key = _xlf_strcpy(key);
    keyval->value = _xlf_strcpy(value);
    node->data = keyval;
    return node;
}

/**
 * @brief append an initialized child node to the end of nodes.
 * @param parent the existing keyval node which at least contains one node
 * @param key
 * @param value
 * @param type
 * @return the new parent length/size after appending the child, or 0 if failed.
 * @see keyval_new()
 */
int keyval_append(xlfNode **parent, const char *key, const char *value, NodeType type) {
    return node_append(parent, keyval_new(key, value, type));
}

/**
 * @brief delete the last child of a given keyval node.
 * @param node
 * @return the keyval node length after deletion
 */
int keyval_delete_last(xlfNode **node) {
    xlfNode *last;
    KeyVal *keyval;

    if(!node || !(*node)) {
        return -1;
    }

    last = (*node)->last;
    keyval = last->data;

    free(keyval->key);
    keyval->key = NULL;

    free(keyval->value);
    keyval->value = NULL;

    free(keyval);
    keyval = NULL;

    return node_delete_last(node);
}

/**
 * @brief completely delete a keyval node.
 * @param node
 * @return the length of node after deletion.
 */
int keyval_delete_all(xlfNode **node) {
    while(*node) {
        keyval_delete_last(node);
    }
    return node_length(*node);
}
