//
// Created by lyq on 2022/10/23.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <malloc.h>

/***
 * 非叶子节点至少有m/2棵子树
 * 至少含有（m/2）-1个关键字
 */


#define M 3


typedef struct{
    int key;
    char *data;
}Record;


typedef struct tree_node{
    int keyNum;
    Record *keyList[M-1];
    struct tree_node *ptr[M];
    int leaf;                        //是否为叶子节点  0否  1是
    struct tree_node *parent;
}tree_node;



typedef struct {
    tree_node *root;
}b_tree;



b_tree *newTree();
int insert(int key,char *data);
int free_tree(b_tree *root);
int delete_data(int key);
Record *get(int key);
void showAll(b_tree *root);



#endif //B_TREE_B_TREE_H
