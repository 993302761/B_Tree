//
// Created by lyq on 2022/10/23.
//

#ifndef B_TREE_B_TREE_H
#define B_TREE_B_TREE_H

#include <malloc.h>
#include <string.h>

/***
 * 非叶子节点至少有m/2棵子树
 * 至少含有（m/2）-1个关键字
 */


#define M 3


typedef struct{
    int key;
    char *data;
}Record;


typedef struct treeNode{
    int keyNum;
    Record *keyList[M];
    struct treeNode *ptr[M+1];
    struct treeNode *parent;
}treeNode;

typedef struct b_tree{
    treeNode *root;
}b_tree;




b_tree *newTree();
void check(treeNode *root);
int insert(b_tree *root,int key,char *data);
int _free_tree(b_tree *root);
int _delete(b_tree *root,int key);
Record *get(b_tree *root,int key);
void showAll(treeNode *root);



#endif //B_TREE_B_TREE_H
