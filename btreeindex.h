#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


typedef struct _btrNode{
    char *str;
    struct _btrNode *bigger;
    struct _btrNode *smaller;
} btrNode;

typedef struct _btrIndex{
    btrNode *root;
    int size;
} btrIndex;

btrNode* btrAddToNode(btrIndex *idx,btrNode *node,btrNode *newnode);
btrNode* btrSearchInNode(btrIndex *idx,btrNode *node,const char *lookfor);
void btrIndexInsert(btrIndex *idx,char *str);
bool btrIndexSearch(btrIndex *idx,const char *lookfor);
bool btrLoadIndex(const char* filename,btrIndex *idx);
void btrFreeIndex(btrIndex *idx);
