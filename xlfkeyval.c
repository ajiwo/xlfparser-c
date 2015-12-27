#include "xlfkeyval.h"

/**
 * @brief create a new keyval node with initial key and value
 * @param key
 * @param value
 * @return pointer to the newly created node or NULL if failed
 */
Node *keyval_new(const char *key, const char *value) {
    Node *node;
    KeyVal *keyval;

    char *_key, *_val;
    int kl, vl;

    kl = strlen(key);
    vl = strlen(value);

    _key = malloc(kl + 1);
    _key[kl] = '\0';

    _val = malloc(vl + 1);
    _val[vl] = '\0';

    node = node_new();
    keyval = malloc(sizeof(KeyVal));
    keyval->key = memcpy(_key, key, kl);
    keyval->value = memcpy(_val, value, vl);
    node->data = keyval;
    node->_type = XLF_NODE_KEYVAL;
    return node;
}

/**
 * @brief append an initialized child node to the end of nodes.
 * @param parent the existing keyval node which at least contains one node
 * @param key
 * @param value
 * @return the new parent length/size after appending the child, or 0 if failed.
 * @see keyval_new()
 */
int keyval_append(Node **parent, const char *key, const char *value) {
    return node_append(parent, keyval_new(key, value));
}

/**
 * @brief delete the last child of a given keyval node.
 * @param node
 * @return the keyval node length after deletion
 */
int keyval_delete_last(Node **node) {
    Node *last;
    KeyVal *keyval;

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
int keyval_delete_all(Node **node) {
    while(*node) {
        keyval_delete_last(node);
    }
    return node_length(*node);
}
