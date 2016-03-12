#include "xlfparser-data.h"
#include "xlfnode.h"

/**
 * @brief create an new node.
 * @return pointer to the newly created node or NULL if failed
 */
xlfNode *node_new(NodeType type) {
    xlfNode *node;
    static int counter;

    node = malloc(sizeof(xlfNode));

    if(node == NULL) {
        return NULL;
    }

    node->data = NULL;
    node->prev = NULL;
    node->next = NULL;
    node->first = node;
    node->last = node;
    node->_type = type;
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
int node_append(xlfNode **parent, xlfNode *child) {
    xlfNode *iter = NULL;

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
 * @brief move node position to index
 * @param nodes
 * @param index
 */
void node_at(xlfNode **nodes, int index) {
    int i = 0;
    *nodes = (*nodes)->first;
    while((*nodes)->next && i != index) {
        *nodes = (*nodes)->next;
        i++;
    }
}

/**
 * @brief get the length/size of a given node.
 * @param node
 * @return the node length/size
 */
int node_length(xlfNode *node) {
    int length = 0;
    xlfNode *iter = NULL;

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


xlfNode *node_get(xlfNode *node, int index) {
    xlfNode *iter;
    int i = 0;

    i = index > -1 ? i : 0;

    iter = node->first;
    while(iter) {
        if(i == index) {
            return iter;
        }
        iter = iter->next;
        i++;
    }

    return NULL;
}

/**
 * @brief delete the last child of a given node.
 * @param node
 * @return the node length after deletion
 */
int node_delete_last(xlfNode **node) {
    xlfNode *iter = NULL;
    xlfNode *delme = NULL;
    xlfNode *last = NULL;

    /* not a node i know */
    if(!node || !(*node)) {
        return -1;
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

    /* (*node)->last maybe previously freed */
    if((*node)->last) {
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

    }

    return node_length(*node);
}

/**
 * @brief completely delete a node.
 * @param node
 * @return the length of node after deletion.
 */
int node_delete_all(xlfNode **node) {
    while(*node) {
        node_delete_last(node);
    }

    return node_length(*node);
}

char *_xlf_strcpy(const char *src) {
    int len;
    char *dst;

    if(src != NULL)
        len = strlen(src);
    else
        return NULL;

    dst = malloc(len + 1);
    dst[len] = '\0';
    return memcpy(dst, src, len);
}
