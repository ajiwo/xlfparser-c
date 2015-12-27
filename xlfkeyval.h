#ifndef XLFKEYVAL_H
#define XLFKEYVAL_H

#include "xlfnode.h"


typedef struct _XlfKeyVal {
    char *key;
    char *value;
} KeyVal;


/**
 * @brief create a new key:value node
 * @return pointer to the newly created node or NULL if failed
 */
Node *keyval_new();

#endif /* XLFKEYVAL_H */
