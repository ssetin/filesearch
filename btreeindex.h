#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>

/*!
    search-tree node with links to his bigger and smaller childrens
*/
typedef struct _btrNode{
    char *str;
    struct _btrNode *bigger;
    struct _btrNode *smaller;
} btrNode;


/*!
    search-tree
*/
typedef struct _btrIndex{
    btrNode *root;
    int size;
} btrIndex;


/*!
    Main functions
*/
void btrIndexInsert(btrIndex *idx,const char *str);
bool btrIndexSearch(btrIndex *idx,const char *lookfor);
bool btrLoadIndex(const char* filename,btrIndex *idx);
void btrFreeIndex(btrIndex *idx);

/*!
    Helper functions
*/
btrNode* btrAddToNode(btrIndex *idx,btrNode *node,btrNode *newnode);
btrNode* btrSearchInNode(btrIndex *idx,btrNode *node,const char *lookfor);
void btrFreeNode(btrIndex *idx,btrNode *node);
