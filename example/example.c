#include "xlfparser.h"

int main(void) {
    Node *layout_xnode = parse_layout("/var/zir/xibo/xlfparser-c/file.xml");

    layout_delete_all(&layout_xnode);
    return 0;
}
