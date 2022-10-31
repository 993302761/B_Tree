//
// Created by lyq on 2022/10/24.
//

#include "../B_Tree.h"
#include <tgmath.h>

b_tree *newTree(){
    b_tree *s=(b_tree *) malloc(sizeof (b_tree));
    memset(s,0,sizeof (s));
    return s;
}

treeNode *newNode(){
    treeNode *s=(treeNode *) malloc(sizeof (treeNode));
    memset(s,0,sizeof (s));
    memset(s->ptr,0,sizeof (s->ptr));
    memset(s->keyList,0,sizeof (s->keyList));
    s->parent=NULL;
    return s;
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
    if(root->ptr[M]!=NULL){
        printf("错误-2");
        return;
    }

    if(left!=NULL&&right!=NULL){
        if(root->ptr[i]!=NULL){
            for (int j = M; j >i+1 ; --j) {
                root->ptr[j]=root->ptr[j-1];
            }
        }
        root->ptr[i]=left;
        left->parent=root;
        root->ptr[i+1]=right;
        right->parent=root;
    } else if(left!=NULL){
        if(root->ptr[i]!=NULL){
            for (int j = M; j >i ; --j) {
                root->ptr[j]=root->ptr[j-1];
            }
        }
        root->ptr[i]=left;
        left->parent=root;
    } else if(right!=NULL){
        if(root->ptr[i]!=NULL){
            for (int j = M; j >i ; --j) {
                root->ptr[j]=root->ptr[j-1];
            }
        }
        root->ptr[i+1]=right;
        right->parent=root;
    }

    check(root);
}


void  _delete(treeNode *node,int key,int p){
    int j=node->keyNum;
    int i;
    for ( i = 0; i < j; ++i) {
        if(node->keyList[i]->key==key){
            if(p==1){
                free(node->keyList[i]);
            }
            node->keyList[i]=NULL;
            node->keyNum--;
            break;
        }
    }
    if(i==j){
        printf("删除错误");
        return;
    }
    for (int k = i; k < M-1; ++k) {
        node->keyList[k]=node->keyList[k+1];
    }
}


void check(treeNode *root){
    if(root->keyNum== M){
        //开始执行分裂操作
        treeNode *left=newNode();
        treeNode *right=newNode();

        merge_node(left,root->keyList[0],root->ptr[0],root->ptr[1]);
        merge_node(right,root->keyList[2],root->ptr[2],root->ptr[3]);

        root->keyList[0]=root->keyList[1];
        for (int i = 1; i < M; ++i) {
            root->keyList[i]=NULL;
            root->keyNum--;
        }
        root->ptr[0]=left;
        root->ptr[1]=right;
        left->parent=root;
        right->parent=root;
        for (int i = 2; i <= M; ++i) {
            root->ptr[i]=NULL;
        }
        if(root->parent!=NULL){
            treeNode *parent=root->parent;
            merge_node(parent,root->keyList[0],left,right);
            free(root);
        }

    }else if(root->ptr[M]!=NULL){
        treeNode *p=root->ptr[M];
        for (int i = 0; i < p->keyNum; ++i) {
            merge_node(root->ptr[M-1],p->keyList[i]->key,NULL,NULL);
            _delete(p,p->keyList[i]->key,0);
        }
        root->ptr[M]=NULL;
        free(p);
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
        merge_node(root,s,NULL,NULL);
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
        merge_node(root,s,NULL,NULL);
    }
    return 1;
}



int _free_tree(treeNode *root){
    if(root==NULL){
        return 0;
    }

    for (int i = 0; i < root->keyNum; ++i) {
        free(root->keyList[i]);
        _free_tree(root->ptr[i]);
    }
    free(root);
    return 1;
}

int _delete_ptr(treeNode *root,treeNode *n){
    for (int i = 0; i < M; ++i) {
        if(root->ptr[i]==n){
            root->ptr[i]=NULL;
            for (int j = i; j < M; ++j) {
                root->ptr[j]=root->ptr[j+1];
            }
            break;
        }
    }
}



void mergeToFather(b_tree *head,treeNode *parent,treeNode *brother){
    merge_node(parent,brother->keyList[0],NULL,NULL);
    _delete(brother,brother->keyList[0]->key,0);
    _free_tree(brother);
    for (int j = 0; j < M; ++j) {
        parent->ptr[j]=NULL;
    }

    treeNode *pp=parent->parent;
    if(pp==NULL){
        return;
    }
    treeNode *pb=NULL;
    int j;
    for ( j = 0; j < M; ++j) {
        if(pp->ptr[j]==parent){
            break;
        } else if(pp->ptr[j]==NULL){
            printf("错误-10");
        }
    }
    if(pp->ptr[j+1]!=NULL){
        pb=pp->ptr[j+1];
        merge_node(pb,pp->keyList[j],parent,NULL);
        _delete(pp,pp->keyList[j]->key,0);
        _delete_ptr(pp,parent);
    } else if(pp->ptr[j-1]!=NULL){
        pb=pp->ptr[j-1];
        merge_node(pb,pp->keyList[j-1],NULL,parent);
        _delete(pp,pp->keyList[j-1]->key,0);
        _delete_ptr(pp,parent);
    } else{
        printf("错误-11");
    }
    if(pp==head->root&&pp->keyNum==0){
        free(head->root);
        head->root=pb;
    }
}

treeNode *get(b_tree *head,int key){
    if(head==NULL){
        return NULL;
    }
    treeNode *root=head->root;
    int j;
    while (root!=NULL){
        int i=root->keyNum;
        for ( j = 0; j < i; ++j) {
            if(root->keyList[j]->key==key){
                return root;
            } else if(root->keyList[j]->key>key){
                root=root->ptr[j];
                break;
            }
        }
        if(j==i){
            root=root->ptr[i];
        }
    }
    return NULL;
}


int deleteNode(b_tree *head,int key){
    if(head==NULL){
        return 0;
    }
    treeNode *node= get(head,key);
    if(node==NULL){
        printf("找不到此节点\n");
        return 0;
    }

    //判断是否为叶子结点
    if(node->ptr[0]==NULL){
        if(node->keyNum==(int)ceil(M/2.0)-1){
            treeNode *parent=node->parent;
            if(parent==NULL){
                _delete(node,key,1);
                return 1;
            }
            int i;
            for ( i = 0; i < M+1; ++i) {
                if(parent->ptr[i]==NULL){
                    printf("错误-3");
                    return 0;
                } else if(parent->ptr[i]==node){
                    break;
                }
            }
            treeNode *left=NULL;
            treeNode *right=NULL;
            if(i>0){
                left=parent->ptr[i-1];
                if(left->keyNum>(int)ceil(M/2.0)-1){

                    //左侧同级节点的键数超过最小值
                    _delete(node,key,1);
                    merge_node(node,parent->keyList[i-1],NULL,NULL);
                    _delete(parent,parent->keyList[i-1]->key,0);
                    int k=left->keyNum;
                    merge_node(parent,left->keyList[k-1],NULL,NULL);
                    _delete(left,left->keyList[k-1]->key,0);
                    return 1;

                }
            }
            if(i<M){
                right=parent->ptr[i+1];
                if(right!=NULL&&right->keyNum>(int)ceil(M/2.0)-1){
                    //右侧同级节点的键数超过最小值
                    _delete(node,key,1);
                    merge_node(node,parent->keyList[i],NULL,NULL);
                    _delete(parent,parent->keyList[i]->key,0);
                    merge_node(parent,right->keyList[0],NULL,NULL);
                    _delete(right,right->keyList[0]->key,0);
                    return 1;
                }
            }
            if(left!=NULL){

                if(parent->keyNum>(int)ceil(M/2.0)-1){

                    merge_node(left,parent->keyList[i-1],NULL,NULL);
                    _delete(parent,parent->keyList[i-1]->key,0);
                    for (int j = i; j < M+1; ++j) {
                        parent->ptr[j]=parent->ptr[j+1];
                    }
                } else{
                    mergeToFather(head,parent,left);
                    _free_tree(node);
                }

            } else{
                if(parent->keyNum>(int)ceil(M/2.0)-1){

                    merge_node(right,parent->keyList[i],NULL,NULL);
                    _delete(parent,parent->keyList[i]->key,0);
                    for (int j = i; j < M+1; ++j) {
                        parent->ptr[j]=parent->ptr[j+1];
                    }
                } else{
                    mergeToFather(head,parent,right);
                    _free_tree(node);
                }
            }

        } else if(node->keyNum>(int)ceil(M/2.0)-1){
            _delete(node,key,1);
        }else{
            printf("错误-5");
            return 0;
        }
    } else{
        int i;
        for ( i = 0; i < M; ++i) {
            if(node->keyList[i]==NULL){
                printf("错误-3");
                return 0;
            } else if(node->keyList[i]->key==key){
                break;
            }
        }
        if(i==M){
            printf("错误-7");
            return 0;
        }
        treeNode *left=node->ptr[i];
        treeNode *right=node->ptr[i+1];
        if(left==NULL||right==NULL){
            printf("错误-8");
            return 0;
        }

        if(node->keyNum==(int)ceil(M/2.0)-1){
            treeNode *parent=node->parent;
            if(parent==NULL){
                while (left->ptr[0]!=NULL){
                    int p=left->keyNum;
                    left=left->ptr[p];
                    if(left==NULL){
                        printf("错误-9");
                        return 0;
                    }
                }
                int s=left->keyNum;

                int newKey=left->keyList[s-1]->key;
                char *newData=left->keyList[s-1]->data;
                deleteNode(head,newKey);
                treeNode *n=get(head,key);
                for (int j = 0; j < n->keyNum; ++j) {
                    if(n->keyList[i]->key==key){
                        n->keyList[i]->key=newKey;
                        n->keyList[i]->data=newData;
                    }
                }
                return 1;
            }


            //右子节点合并到左子节点
            merge_node(left,right->keyList[0],NULL,NULL);
            _delete(right,right->keyList[0]->key,0);
            free(right);

            treeNode *pBrother=NULL;
            int j;
            for ( j = 0; j < M + 1; ++j) {
                if(parent->ptr[j]==node){
                    break;
                }
            }
            _delete_ptr(parent,node);
            if(j>0&&parent->ptr[j-1]!=NULL){
                pBrother=parent->ptr[j-1];
                merge_node(pBrother,parent->keyList[j-1],NULL,left);
                _delete(parent,parent->keyList[j-1]->key,0);
            } else if(j<M&&parent->ptr[j+1]!=NULL){
                pBrother=parent->ptr[j];
                merge_node(pBrother,parent->keyList[j],left,NULL);
                _delete(parent,parent->keyList[j]->key,0);
            }else{
                printf("错误-12");
                return 0;
            }
            //删除节点
            _delete(node,node->keyList[i]->key,1);
            free(node);
            return 1;
        }else if(node->keyNum>(int)ceil(M/2.0)-1){
            _delete(node,node->keyList[i]->key,1);

            if(left->keyNum>(int)ceil(M/2.0)-1){
                int k=left->keyNum;
                merge_node(node,left->keyList[k-1],NULL,NULL);
                _delete(left,left->keyList[k-1]->key,0);
                return 1;
            }
            if(right->keyNum>(int)ceil(M/2.0)-1){
                merge_node(node,right->keyList[0],NULL,NULL);
                _delete(right,right->keyList[0]->key,0);
                return 1;
            }
            treeNode *rl=right->ptr[0];
            treeNode *rr=right->ptr[1];
            if(rr!=NULL&&rl!=NULL){
                merge_node(rl,rr->keyList[0],NULL,NULL);
                _delete(rr,rr->keyList[0]->key,0);
                free(rr);
            }


            merge_node(left,right->keyList[0],NULL,rl);
            _delete(right,right->keyList[0]->key,0);
            free(right);
            for (int j = i+1; j < M; ++j) {
                node->ptr[j]=node->ptr[j+1];
            }
        } else{
            printf("错误-5");
            return 0;
        }
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
            printf("错误-1");
            return;
        }
        printf("%d ",root->keyList[i]->key);
    }
    printf("}\n");


    for (int i = 0; i < M; ++i) {
        showAll(root->ptr[i]);
    }

}
