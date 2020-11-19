#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct node {
    char val;
    int depth;
    struct node * NE;
    struct node * NW;
    struct node * SW;
    struct node * SE;
};

typedef struct node Node;
typedef Node *NodePtr;
char input[100];
int isAssigned = 0;
int treeDepth = 0;

void insertNode(NodePtr *treePtr,char val, int depth) {

    if(*treePtr == NULL){
        *treePtr = malloc(sizeof(Node));

        if(*treePtr != NULL){
            (*treePtr)->val = val;
            (*treePtr)->depth = depth;
            (*treePtr)->NW = NULL;
            (*treePtr)->NE = NULL;
            (*treePtr)->SE = NULL;
            (*treePtr)->SW = NULL;
            if(treeDepth < depth){
                treeDepth = depth;
            }
            isAssigned = 1;
        }
    }
    else{

            if((*treePtr)->val == '+' && (*treePtr)->NW == NULL && !isAssigned){
                insertNode(&((*treePtr)->NW),val,depth+1);
                return;
            }
            else if((*treePtr)->val == '+' && (*treePtr)->NW != NULL){
                if( ((*treePtr)->NW)->val == '+'){
                    insertNode(&((*treePtr)->NW),val,depth+1);
                }
            }

            if((*treePtr)->val == '+' && (*treePtr)->NE == NULL && !isAssigned){
                insertNode(&((*treePtr)->NE),val,depth+1);
                return;
            }
            else if((*treePtr)->val == '+' && (*treePtr)->NE != NULL){
                if( ((*treePtr)->NE)->val == '+'){
                    insertNode(&((*treePtr)->NE),val,depth+1);
                }
            }

            if((*treePtr)->val == '+' && (*treePtr)->SE == NULL && !isAssigned){
                insertNode(&((*treePtr)->SE),val,depth+1);
                return;
            }
            else if((*treePtr)->val == '+' && (*treePtr)->SE != NULL){
                if( ((*treePtr)->SE)->val == '+'){
                    insertNode(&((*treePtr)->SE),val,depth+1);
                }
            }

            if((*treePtr)->val == '+' && (*treePtr)->SW == NULL && !isAssigned){
                insertNode(&((*treePtr)->SW),val,depth+1);

                return;
            }
            else if((*treePtr)->val == '+' && (*treePtr)->SW != NULL){
                if( ((*treePtr)->SW)->val == '+'){
                    insertNode(&((*treePtr)->SW),val,depth+1);

                }
            }
    }
}

void fillArray(NodePtr treePtr, char *x[], int minX , int minY){

    if(treePtr != NULL){
        int k = 1;
        int m = treeDepth - treePtr->depth;
        for(int i = 0; i < m; i++)
            k = k*2;
        if(treePtr->val != '+'){

            if( m == 0){
                x[minX][minY] = treePtr->val;
            }
            else{
                for (int i = minX; i < k + minX; i++)
                    for (int j = minY; j < k + minY; j++)
                        x[i][j] = treePtr->val;
            }

        }
        else{
            fillArray(treePtr->NW,x, minX, minY);
            fillArray(treePtr->NE,x, minX, minY+(k/2));
            fillArray(treePtr->SE,x, minX+(k/2), minY+(k/2));
            fillArray(treePtr->SW,x, minX+(k/2), minY);
        }
    }
}
int main()
{
    scanf("%s", input);
    NodePtr root = NULL;
    insertNode(&root,input[0],0);
      for ( int i = 1; i < strlen(input); i++ ){

        isAssigned = 0;
        insertNode(&root,input[i],0);
    }

    int n = 1;

    for ( int i = 0; i < treeDepth; i++){
        n = n * 2;
    }

    char **array = (char **)malloc(n * sizeof(char *));
    for (int i=0; i < n; i++)
         array[i] = (char *)malloc(n * sizeof(char));

    fillArray(root,array,0,0);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%c",array[i][j]);
        }
        printf("\n");
    }
    return 0;
}
