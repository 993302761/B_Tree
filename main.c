#include <stdio.h>

/***
 * 非叶子节点至少有m/2棵子树
 * 至少含有（m/2）-1个关键字
 */

#define M 3

typedef struct{
    int key;
    char *data;
}Record;

typedef struct B_treeNode{
    int keyNum;
    Record *keyList[M-1];
    struct B_treeNode *ptr[M];
    int leaf;                        //是否为叶子节点  0否  1是
    struct B_treeNode *parent;
}B_treeNode;


typedef struct {
    B_treeNode *root;
}B_Tree;



int main() {

    B_Tree s;

}

