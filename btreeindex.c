#include "btreeindex.h"


/*!
    Search string in current node and his childrens
    \param[in]  idx      search-tree
    \param[in]  node     current node
    \param[in]  lookfor  search string
    \param[out] node where we find it
*/
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


/*!
    Search string in search-tree
    \param[in]  idx      search-tree
    \param[in]  lookfor  search string
    \param[out] node where we find it
*/
bool btrIndexSearch(btrIndex *idx,const char *lookfor){
    if(idx==NULL || lookfor==NULL || idx->root==NULL)
        return false;

    if(btrSearchInNode(idx,idx->root,lookfor))
        return true;

    return false;
}

/*!
    Free memory, allocated for node and his childrens
    \param[in]  idx      search-tree
    \param[in]  node     node
*/
void btrFreeNode(btrIndex *idx,btrNode *node){
    if(idx==NULL || node==NULL)
        return;

    while(1){
        if(node->bigger!=NULL){
            btrFreeNode(idx,node->bigger);
            node->bigger=NULL;
        }
        if(node->smaller!=NULL){
            btrFreeNode(idx,node->smaller);
            node->smaller=NULL;
        }
        if(node->bigger==NULL && node->smaller==NULL){
            idx->size--;
            free(node->str);
            free(node);
            node=NULL;
            break;
        }
    }
}

/*!
    Free memory, allocated for search-tree nodes
    \param[in]  idx      search-tree
*/
void btrFreeIndex(btrIndex *idx){
    if(idx==NULL || idx->root==NULL)    
        return;
    btrFreeNode(idx,idx->root);
    idx->root=NULL;
    idx->size=0;
}

/*!
    Add node to search-tree using node data comparsion
    \param[in]  idx         search-tree
    \param[in]  node        current node of the tree
    \param[in]  newnode     new node with new data
    \param[out] new node inside tree
*/
btrNode* btrAddToNode(btrIndex *idx,btrNode *node,btrNode *newnode){
    if(idx==NULL || node==NULL || newnode==NULL)
        return NULL;
    int fres=0;

    while(1){
        fres=strcmp(newnode->str,node->str);
        if(fres==0){                        
            return node;
        }
        if(fres>0){
            if(node->bigger==NULL){
                node->bigger=newnode;
                idx->size++;
                //avl
                btrBalanceNode(newnode);
                break;
            }
            else{
                return btrAddToNode(idx,node->bigger,newnode);
            }
        }else{
            if(node->smaller==NULL){
                node->smaller=newnode;
                idx->size++;
                //avl
                btrBalanceNode(newnode);
                break;
            }
            else{
                return btrAddToNode(idx,node->smaller,newnode);
            }
        }
    }
    return newnode;
}

/*!
    Add string data to search-tree
    \param[in]  idx        search-tree
    \param[in]  str        string data
*/
void btrIndexInsert(btrIndex *idx,const char *str){
    if(idx==NULL || str==NULL)
        return;
    btrNode *node=(btrNode*)malloc(sizeof(btrNode));
    if(node==NULL){
        printf("Memory allocation error for %d node",idx->size);
        return;
    }
    node->str=(char*)malloc((strlen(str)+1)*sizeof(char));
    if(node->str==NULL){
        printf("Memory allocation error for string at %d node",idx->size);
        return;
    }
    node->str=strcpy(node->str,str);
    node->bigger=NULL;
    node->smaller=NULL;

    if(idx->root==NULL){
        idx->root=node;
        idx->size=1;
        return;
    }
    btrAddToNode(idx,idx->root,node);
}

/*!
    Load and build search-tree from file
    \param[in]  filename    file name
    \param[in]  idx         search-tree
    \param[out] true if success or false
*/
bool btrLoadIndex(const char* filename,btrIndex *idx){
    if(idx==NULL)
        return false;
    FILE *file;
    char buffer[255];
    int tmplen=0;

    file = fopen(filename,"r");
    if(file == NULL) {
        return false;
    }

    btrFreeIndex(idx);

    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        tmplen=strlen(buffer);
        if (tmplen != 0){
            if(buffer[tmplen-2] == '\r' && buffer[tmplen-1]=='\n')
                buffer[tmplen-2] = '\0'; else
            if(buffer[tmplen-1]=='\n'){
                buffer[tmplen-1] = '\0';
            }
            btrIndexInsert(idx,buffer);
        }
        if(idx->size%5000==0){
            printf("\rLoading index...(%d)",idx->size);
        }
    }
    printf("\rLoading index. Done(%d)\n",idx->size);

    fclose(file);
    return true;
}

/*=======================AVL==================================*/
/*!
    Get node height
    \param[in]  node    node
    \param[out] node height
*/
short btrGetNodeHeight(btrNode* node){
    if(node==NULL) return 0;
    return node->height;
}
/*!
    Get difference between smaller and bigger subnodes
    \param[in]  node    node
    \param[out] balance factor
*/
short btrGetNodeBalanceFactor(btrNode* node){
    if(node==NULL) return 0;
    return btrGetNodeHeight(node->bigger)-btrGetNodeHeight(node->smaller);
}
/*!
    Recalculate height for node
    \param[in]  node    node
*/
void btrRecalcNodeHeight(btrNode* node){
    if(node==NULL) return;
    short biggerl=btrGetNodeHeight(node->bigger);
    short smallerl=btrGetNodeHeight(node->smaller);
    node->height=(biggerl>smallerl?biggerl:smallerl)+1;
}
/*!
    Make right rotate for node
    \param[in]  node    node
*/
btrNode* btrRotateRight(btrNode *node){
    btrNode *newnode = node->smaller;
    node->smaller = newnode->bigger;
    newnode->bigger = node;
    btrRecalcNodeHeight(node);
    btrRecalcNodeHeight(newnode);
    return newnode;
}
/*!
    Make left rotate for node
    \param[in]  node    node
*/
btrNode* btrRotateLeft(btrNode *node){
    btrNode *newnode = node->bigger;
    node->bigger = newnode->smaller;
    newnode->smaller = node;
    btrRecalcNodeHeight(node);
    btrRecalcNodeHeight(newnode);
    return newnode;
}
/*!
    Balancing the node
    \param[in]  node    node
    \param[out] balance factor
*/
btrNode* btrBalanceNode(btrNode* node){
    btrRecalcNodeHeight(node);
    if( btrGetNodeBalanceFactor(node)==2){
        if( btrGetNodeBalanceFactor(node->bigger)<0)
            node->bigger = btrRotateRight(node->bigger);
        return btrRotateLeft(node);
    }
    if(btrGetNodeBalanceFactor(node)==-2){
        if( btrGetNodeBalanceFactor(node->smaller)>0)
            node->smaller = btrRotateLeft(node->smaller);
        return btrRotateRight(node);
    }
    return node;
}








