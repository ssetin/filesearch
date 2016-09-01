#include "strindex.h"



void FreestrIndex(strIndex *idx){
    strNode *ptr=idx->first;

    while(ptr!=NULL){
        free(ptr->str);
        free(ptr);
        ptr=ptr->next;
    }
    /*for(int k=0;k<i->size;k++)
        free(i->strings[k]);
    free(i->strings);*/
}

char* strIndexGet(strIndex *idx,int pos){
    strNode *ptr=idx->first;
    int res=0;

    while((ptr=ptr->next)!=NULL && res!=pos){
        res++;
        //printf("found %s\n",ptr->str);
    }
    if(ptr!=NULL)
        return ptr->str;
    else return NULL;
}

void strIndexInsert(strIndex *idx,int pos,char *str){
    if(idx==NULL)
        return;
    int res=0;
    strNode *node=(strNode*)malloc(sizeof(strNode));
    node->str=(char*)malloc(sizeof(char)*strlen(str));
    strcpy(node->str,str);
    //printf("len %d, name %s\n",sizeof(char)*strlen(str),str);
    node->next=NULL;
    node->index=0;

    if(idx->first==NULL){
        idx->first=node;
        idx->size=1;
        return;
    }
    if(pos==0 || pos==-1){
        node->next=idx->first;
        idx->first=node;
        idx->size++;
        return;
    }

    strNode *ptr=idx->first;
    while((ptr=ptr->next)!=NULL && res<pos){
        res++;
       // printf("next %d\n",res);
    }
    if(ptr!=NULL){
        //printf("%d element\n",res);
        ptr->next=node;
        ptr->index=pos+1;
        idx->size++;
    }

}


bool LoadIndex(const char* filename,strIndex *idx){
    FILE *file;
    char str[128];
    int tmplen=0, k=-1;

    file = fopen(filename,"r");
    if(file == NULL) {
        return false;
    }

    idx->size=0;

    while(fgets(str,sizeof(str),file) && idx->size<1000) {
        tmplen=strlen(str);
        if (tmplen != 0 && str[tmplen-1] == '\n') {
            str[tmplen-1] = '\0';
        }
        k=strIndexbSearch(idx,str);
        //if(k>1)
        //    printf("found bigger at k=%d\n",k);
        strIndexInsert(idx,k,str);
    }
    printf("%d strings loaded\n",idx->size);

    fclose(file);
    return true;
}


void swap(char *str1,char *str2){
    char *tmp;
    tmp=str1;
    str1=str2;
    str2=tmp;
}

int strIndexbSearch(strIndex *idx,char *lookfor){
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
            printf("%s and %s\n",mstr,lookfor);
            if(strncmp(mstr,lookfor,2)>0){
                end=middle;
            }else{
                begin=middle;
            }
            premiddle=middle;
        }
    }
    return -1;
}



















