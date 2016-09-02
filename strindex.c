#include "strindex.h"



void FreestrIndex(strIndex *idx){
    strNode *ptr=idx->first;
    strNode *tmp=NULL;

    while(ptr!=NULL){
        tmp=ptr;
        ptr=ptr->next;
        free(tmp->str);
        free(tmp);

    }
    idx->first=NULL;
    idx->size=0;
}

char* strIndexGet(strIndex *idx,int pos){
    strNode *ptr=idx->first;
    int res=0;

    while(ptr!=NULL && res!=pos){
        ptr=ptr->next;
        res++;
    }
    if(ptr!=NULL)
        return ptr->str;
    else return NULL;
}

void strIndexInsert(strIndex *idx,int pos,char *str){
    if(idx==NULL || str==NULL)
        return;
    int res=0;
    strNode *node=(strNode*)malloc(sizeof(strNode));
    if(node==NULL){
        printf("Memory allocation error for %d node",idx->size);
        return;
    }
    //node->str=(char*)calloc(strlen(str)+1,sizeof(char));
    node->str=(char*)malloc((strlen(str)+1)*sizeof(char));
    if(node->str==NULL){
        printf("Memory allocation error for string st %d node",idx->size);
        return;
    }
    strcpy(node->str,str);
    node->next=NULL;
    node->index=0;

    if(idx->first==NULL){
        idx->first=node;
        idx->size=1;
        return;
    }
    if(pos==0){
        node->next=idx->first;
        idx->first=node;
        idx->size++;
        return;
    }
    if(pos==-1)
        pos=idx->size;

    strNode *ptr=idx->first;    
    while(ptr!=NULL && res!=pos-1){
        ptr=ptr->next;
        res++;
    }
    if(ptr!=NULL){
        node->next=ptr->next;
        ptr->next=node;
        idx->size++;
    }

}


bool LoadIndex(const char* filename,strIndex *idx){
    FILE *file;
    char buffer[128];
    int tmplen=0, k=0, isize=0;

    file = fopen(filename,"r");
    if(file == NULL) {
        return false;
    }

    while(fgets(buffer,sizeof(buffer),file)) {
        isize++;
    }
    fseek(file,0,SEEK_SET);

    FreestrIndex(idx);

    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        tmplen=strlen(buffer);
        if (tmplen != 0 && buffer[tmplen-1] == '\n') {
            buffer[tmplen-1] = '\0';
        }
        k=strIndexbSearch(idx,buffer);
        strIndexInsert(idx,k,buffer);
        if(idx->size%500==0)
            printf("\rLoading index...(%d)",idx->size);
    }
    printf("\rLoading index. Done(%d)\n",idx->size);

    fclose(file);
    return true;
}


void swap(char *str1,char *str2){
    char *tmp;
    tmp=str1;
    str1=str2;
    str2=tmp;
}

int strIndexbSearch(strIndex *idx,const char *lookfor){
    if(idx->size==0 || lookfor==NULL) return -1;

    int begin=0, end=idx->size;
    int middle=idx->size/2, premiddle=0;

    while(middle<idx->size){
        middle=begin+(end-begin)/2;

        if(premiddle==middle){
            if(middle==0)
                return 0;
            if(middle+1<idx->size)
                return middle+1;
            else return -1;
        }
        char *mstr=strIndexGet(idx,middle);

        if(mstr==NULL){
            return -1;
        }else{
            if(strcmp(mstr,lookfor)>0){
                end=middle;
            }else{
                begin=middle;
            }
            premiddle=middle;
        }
    }
    return -1;
}



















