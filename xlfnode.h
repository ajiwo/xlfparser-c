#ifndef XLFNODE_H
#define XLFNODE_H
#include "xlfparser-data.h"

Node *node_new();
int node_prepend(Node **nodes, Node *child);
int node_append(Node **nodes, Node *child);

/*
 * move node current position to index
 */
void node_move_to(Node **nodes, int index);

/*
 * get node at position index
 */
Node *node_get(Node **nodes, int index);

/*
 * get current index
 */
int node_index(Node *nodes);


int maybe_valid_node(Node *node);
int node_length(Node *node);

/* map-like node for implementing layout option, region option, media option, media raw,.. */
Node *keyval_new();

/* will be useful for funcs like: layout_add_tag(), region_add_option(), media_add_option(),.. */
void node_add_keyval(Node **keyval_node, char *key, char *value);


/* registry to free (m|c)alloc-ated heap */
void _regunreg_node(Node *node, int reg_unreg);
void register_node(Node *node);
void unregister_nodes();
#endif /* XLFNODE_H */

