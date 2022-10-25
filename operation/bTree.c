//
// Created by lyq on 2022/10/24.
//

#include "../B_Tree.h"

b_tree *newTree(){
    b_tree *s=(b_tree *) malloc(sizeof (b_tree));
    memset(s,0,sizeof (s));
    return s;
}

treeNode *newNode(){
    treeNode *s=(treeNode *) malloc(sizeof (treeNode));
    memset(s,0,sizeof (s));
    return s;
}



void add_node(treeNode *root,Record *s){
    int i=(root->keyNum)++;
    root->keyList[i]=s;
    for (int j = i-1; j >= 0; --j) {
        if((root->keyList[j]->key)>(root->keyList[i]->key)){
            Record *p=root->keyList[i];
            root->keyList[i]=root->keyList[j];
            root->keyList[j]=p;
            i=j;
        }
    }
    check(root);
}

void merge_node(treeNode *root,Record *s,treeNode *left,treeNode*right){
    int i=(root->keyNum)++;
    root->keyList[i]=s;
    for (int j = i-1; j >= 0; --j) {
        if((root->keyList[j]->key)>(root->keyList[i]->key)){
            Record *p=root->keyList[i];
            root->keyList[i]=root->keyList[j];
            root->keyList[j]=p;
            i=j;
        }
    }
    if(root->ptr[M-1]!=NULL){
        printf("错误");
        return;
    }
    if(root->ptr[i]!=NULL){
        for (int j = M-1; j >i+1 ; --j) {
            root->ptr[j]=root->ptr[j-1];
        }
    }
    root->ptr[i]=left;
    root->ptr[i+1]=right;
}

int separate(treeNode *n,Record *s){
    n->keyNum++;
    n->keyList[0]=s;
}

void check(treeNode *root){
    if(root->keyNum==3){
        //开始执行分裂操作
        treeNode *left=newNode();
        treeNode *right=newNode();
        add_node(left,root->keyList[0]);
        for (int i = 2; i < M; ++i) {
            add_node(right,root->keyList[i]);
        }

        root->keyList[0]=root->keyList[1];
        for (int i = 1; i < M; ++i) {
            root->keyList[i]=NULL;
            root->keyNum--;
        }
        root->ptr[0]=left;
        root->ptr[1]=right;
        left->parent=root;
        right->parent=root;

        if(root->parent!=NULL){
            treeNode *parent=root->parent;
            merge_node(parent,root->keyList[0],left,right);
            free(root);
        }

    }
}

int insert(b_tree *head,int key,char *data){
    if(head==NULL){
        return 0;
    }
    treeNode *root;
    if(head->root==NULL){
        root=(treeNode *) malloc(sizeof (treeNode));
        head->root=root;
    } else{
        root=head->root;
    }
    Record *s=(Record *) malloc(sizeof (Record));
    memset(s,0,sizeof (s));
    s->key=key;
    s->data=data;

    if(root->ptr[0]==NULL){
        //确定是子节点再插入
        add_node(root,s);
    } else{
        while (root->ptr[0]!=NULL) {
            int i;
            int j=root->keyNum;
            for ( i = 0; i < j; ++i) {
                if (key < root->keyList[i]->key) {
                    root = root->ptr[i];
                    break;
                }
            }
            if(i==j){
                root = root->ptr[i];
            }
        }
        add_node(root,s);
    }
}

int _free_tree(b_tree *head){
    if(head==NULL){
        return 0;
    }
    if(head->root==NULL){
        free(head);
        return 1;
    }
    treeNode *root=head->root;

    for (int i = 0; i < root->keyNum; ++i) {
        free(root->keyList[i]);
        _free_tree(root->ptr[i]);
    }
    free(root);
}

int _delete(b_tree *root,int key){
    if(root==NULL){
        return 0;
    }
}

Record *get(b_tree *root,int key){
    if(root==NULL){
        return NULL;
    }
}



void showAll(treeNode *root){
    if(root==NULL){
        return ;
    }

    printf("{ ");
    int j=root->keyNum;
    for (int i = 0; i <j; ++i) {
        if(root->keyList[i]==NULL){
            printf("错误");
            return;
        }
        printf("%d ",root->keyList[i]->key);
    }
    printf("}\n");


    for (int i = 0; i < M; ++i) {
        showAll(root->ptr[i]);
    }

}
