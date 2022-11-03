#include <stdio.h>
#include <tgmath.h>
#include "B_Tree.h"


int main() {

    b_tree *s=newTree();
    char *data="123";

    insert(s,30,data);
    insert(s,10,data);
    insert(s,20,data);
    insert(s,50,data);
    insert(s,60,data);
    insert(s,40,data);
    insert(s,90,data);
    insert(s,100,data);
    insert(s,55,data);
    insert(s,65,data);
    insert(s,85,data);
    insert(s,25,data);
    insert(s,66,data);

    deleteNode(s,66);
    showAll(s->root);
    _free_tree(s->root);

}

