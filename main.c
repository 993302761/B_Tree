#include <stdio.h>
#include <tgmath.h>
#include "B_Tree.h"


int main() {

    b_tree *s=newTree();
    char *data="123";
    for (int i = 0; i < 2; ++i) {
        insert(s,i,data);
    }
    deleteNode(s,1);
    showAll(s->root);
    _free_tree(s->root);

}

