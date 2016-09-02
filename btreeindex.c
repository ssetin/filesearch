#include "btreeindex.h"



btrNode* btrSearchInNode(btrIndex *idx,btrNode *node,const char *lookfor){
    if(idx==NULL || node==NULL || lookfor==NULL)
        return NULL;
    int fres=1;

    while(fres!=0){
        fres=strcmp(lookfor,node->str);
        if(fres==0)
            return node;
        if(fres>0){
            if(node->bigger!=NULL){
                return btrSearchInNode(idx,node->bigger,lookfor);
            }else{
                return NULL;
            }
        }else{
            if(node->smaller!=NULL){
                return btrSearchInNode(idx,node->smaller,lookfor);
            }
            else{
                return NULL;
            }
        }
    }
    return NULL;
}


bool btrIndexSearch(btrIndex *idx,const char *lookfor){
    if(idx==NULL || lookfor==NULL || idx->root==NULL)
        return false;

    if(!strcmp(idx->root->str,lookfor)){
        return true;
    }

    if(btrSearchInNode(idx,idx->root,lookfor))
        return true;

    return false;
}

void btrFreeIndex(btrIndex *idx){
}

btrNode* btrAddToNode(btrIndex *idx,btrNode *node,btrNode *newnode){
    if(idx==NULL || node==NULL || newnode==NULL)
        return NULL;
    int fres=0;

    while(1){
        fres=strcmp(newnode->str,node->str);
        if(fres==0)
            break;
        if(fres>0){
            if(node->bigger==NULL){
                node->bigger=newnode;
                idx->size++;
                break;
            }
            else{
                btrAddToNode(idx,node->bigger,newnode);
                break;
            }
        }else{
            if(node->smaller==NULL){
                node->smaller=newnode;
                idx->size++;
                break;
            }
            else{
                btrAddToNode(idx,node->smaller,newnode);
                break;
            }
        }
    }
    return node;
}

void btrIndexInsert(btrIndex *idx,char *str){
    if(idx==NULL || str==NULL)
        return;
    btrNode *node=(btrNode*)malloc(sizeof(btrNode));
    if(node==NULL){
        printf("Memory allocation error for %d node",idx->size);
        return;
    }
    node->str=(char*)malloc((strlen(str)+1)*sizeof(char));
    if(node->str==NULL){
        printf("Memory allocation error for string st %d node",idx->size);
        return;
    }
    strcpy(node->str,str);
    node->bigger=NULL;
    node->smaller=NULL;

    if(idx->root==NULL){
        idx->root=node;
        idx->size=1;
        return;
    }
    btrAddToNode(idx,idx->root,node);
}


bool btrLoadIndex(const char* filename,btrIndex *idx){
    if(idx==NULL)
        return false;
    FILE *file;
    char buffer[128];
    int tmplen=0;

    file = fopen(filename,"r");
    if(file == NULL) {
        return false;
    }

    btrFreeIndex(idx);

    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        tmplen=strlen(buffer);
        if (tmplen != 0 && buffer[tmplen-1] == '\n') {
            buffer[tmplen-1] = '\0';
        }
        btrIndexInsert(idx,buffer);
        if(idx->size%500==0)
            printf("\rLoading index...(%d)",idx->size);
    }
    printf("\rLoading index. Done(%d)\n",idx->size);

    fclose(file);
    return true;
}
