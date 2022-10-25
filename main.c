#include <stdio.h>
#include "B_Tree.h"


int main() {
    b_tree *s=newTree();
    char *data="123";
    insert(s,3,data);
    insert(s,2,data);
    insert(s,4,data);
    insert(s,5,data);
    insert(s,1,data);
    insert(s,6,data);

    insert(s,0,data);

    showAll(s->root);
//    _free_tree(s);
}

