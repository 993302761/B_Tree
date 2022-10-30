#include <stdio.h>
#include <tgmath.h>
#include "B_Tree.h"


int main() {
    b_tree *s=newTree();
    char *data="123";
    insert(s,30,data);
    insert(s,20,data);
    insert(s,40,data);
    insert(s,50,data);
    insert(s,10,data);
    insert(s,60,data);
    insert(s,0,data);
    insert(s,15,data);
    insert(s,19,data);
//    insert(s,25,data);
//    insert(s,12,data);
    deleteNode(s,15);
    showAll(s->root);
    _free_tree(s->root);

}

