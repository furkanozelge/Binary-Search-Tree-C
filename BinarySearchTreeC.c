#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct Node* root = NULL;
struct Node{
    int key;
    int data;
    struct Node *right, *left;
};
struct Node* newNode(int item){
    struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
    tmp->data = item;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void listNodes(struct Node* root)
{
    if (root != NULL){
        listNodes(root->left);
        printf("%d ", root->data);
        listNodes(root->right);
    }
}
struct Node* nodeInsert(struct Node* root, int data){
    if (root == NULL){
        return newNode(data);
    }
    if (data < root->data){
        root -> left = nodeInsert(root->left, data);
    }
    else if (data > root->data){
        root -> right = nodeInsert(root->right, data);
    }
    else if (data == root->data){
        root->right = nodeInsert(root->right, data);
    }
    return root;
}
void parentFinder(struct Node *Node,int val, int parent)
{
    if (Node == NULL){
        return;
    }
    if (Node -> data == val){
        if (root -> data == val){
            printf("It is a root Node\n");
        }
        else{
            printf("The parent of %d is %d\n",val,parent);
        }
    }
    else{
        parentFinder(Node->left, val, Node->data);
        parentFinder(Node->right, val, Node->data);
    }
}
struct Node *getParent(struct Node *root, int data){
    if (root == NULL){
        return NULL;
    }
    else if (root->data == data){
        getParent(root->right, data);
    }
    else if (root->data > data){
        getParent(root->left, data);
    }
    else if (root->right->data == data || root->left->data == data){
        return root;
    }
    else{
     getParent(root->right, data);
    }
    return root;
}
int main(){
    char command[500];
    int bayrak = 1;
    int j = 0;
    while(bayrak){
        gets(command);
        const char *addTree="CONSTRUCT";
        char *tmp=command;
        int i=0;
        if(strncmp(tmp, addTree, strlen(addTree)) == 0){
            int i=0;
            char *p=command;
            while (*p){
                if (isdigit(*p)){
                    long val = strtol(p, &p, 10);
                    root=nodeInsert(root,val);
                    p=p+1;
                }
                else{
                    p=p+1;
                }
            }
        }
        else if(strstr(tmp, "INSERT")!=NULL)
        {
            while (*tmp){
                if (isdigit(*tmp)){
                    long val = strtol(tmp, &tmp, 10);
                    nodeInsert(root,val);
                    parentFinder(root,val,-1);
                }
                else{
                    tmp=tmp+1;
                }
            }
        }
        else if(strstr(tmp,"EXIT")!=NULL){
            break;
        }
        else if(strstr(tmp,"PARENT")!=NULL){
            while (*tmp){
                if (isdigit(*tmp)){
                    long val = strtol(tmp, &tmp, 10);
                     parentFinder(root,val,-1);
                }
                else{
                    tmp=tmp+1;
                }
            }
        }
        else if(strstr(tmp, "LIST")!=NULL){
            listNodes(root);
            printf("\n");
        }
    }
}
