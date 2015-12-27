#include "xlfkeyval.h"

/**
 * @brief create a new key:value node
 * @return pointer to the newly created node or NULL if failed
 */
Node *keyval_new() {
    Node *node;
    KeyVal *keyval;

    node = node_new();
    keyval = malloc(sizeof(KeyVal));
    node->data = keyval;
    node->_type = XLF_NODE_KEYVAL;
    return node;
}

