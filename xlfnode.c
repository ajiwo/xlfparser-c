#include "xlfparser-data.h"
#include "xlfnode.h"

/**
 * @brief create an new node.
 * @return pointer to the newly created node or NULL if failed
 */
Node *node_new() {
    Node *node;
    static int counter;

    node = malloc(sizeof(Node));

    if(node == NULL) {
        return NULL;
    }

    node->data = NULL;
    node->prev = NULL;
    node->next = NULL;
    node->first = node;
    node->last = node;
    node->_type = XLF_NODE_UNKNOWN;
    node->_id = counter++;

    return node;
}

/**
 * @brief append an initialized child node to the end of nodes.
 * @param parent the existing node which at least contains one node
 * @param child node to be appended, created by node_new()
 * @return the new parent length/size after appending the child, or 0 if failed.
 * @see node_new()
 */
int node_append(Node **parent, Node *child) {
    Node *iter = NULL;

    /* not a node i know */
    if(parent == NULL || child == NULL) {
        return 0;
    }

    /* cannot append different type of node */
    if((*parent)->_type != child->_type) {
        return 0;
    }

    (*parent)->last->next = child;

    child->first = (*parent)->first;
    child->last = child;
    child->next = NULL;
    child->prev = (*parent)->last;

    iter = (*parent)->first;
    while(iter) {
        iter->last = child;
        iter = iter->next;
    }

    return node_length(*parent);
}
/**
 * @brief get the length/size of a given node.
 * @param node
 * @return the node length/size
 */
int node_length(Node *node) {
    int length = 0;
    Node *iter = NULL;

    if(node == NULL) {
        return 0;
    }

    iter = node->first;
    while(iter) {
        length++;
        iter = iter->next;
    }

    return length;
}

/**
 * @brief delete the last child of a given node.
 * @param node
 * @return the node length after deletion
 */
int node_delete_last(Node **node) {
    Node *iter = NULL;
    Node *delme = NULL;
    Node *last = NULL;

    /* not a node i know */
    if(node == NULL) {
        return 0;
    }

    /* there's only one node, alone.. */
    if((*node)->first == (*node) && (*node)->last == (*node)) {

        free(*node);
        *node = NULL;
        return 0;
    }

    /* the node to delete is current node index? move index to prev */
    if((*node)->last == *node) {
        *node = (*node)->prev;
    }

    delme = (*node)->last;
    last = delme->prev;

    last->last = last;
    last->next = NULL;

    iter = (*node)->first;
    while(iter && iter != delme) {
        iter->last = last;
        iter = iter->next;
    }

    free(delme);
    delme = NULL;

    return node_length(*node);
}

/**
 * @brief completely delete a node.
 * @param node
 * @return the length of node after deletion.
 */
int node_delete_all(Node **node) {
    while(*node) {
        node_delete_last(node);
    }

    return node_length(*node);
}
