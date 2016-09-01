#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


typedef struct _strNode{
    char *str;
    int index;
    struct _strNode *next;
} strNode;

typedef struct _strIndex{
    strNode *first;
    int size;
} strIndex;


void strIndexInsert(strIndex *idx,int pos,char *str);
char* strIndexGet(strIndex *idx,int pos);
int strIndexbSearch(strIndex *idx,char *lookfor);
int strIndexSearch(strIndex *idx,char *lookfor);
bool LoadIndex(const char* filename,strIndex *idx);
void FreestrIndex(strIndex *idx);


void swap(char *dest,char *src);

