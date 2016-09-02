#include "strindex.h"

strIndex sindex;


int main(int argc, char *argv[]){

    char cmd[128];

    //printf("%d\n\n",strcmp("fuller","abba"));

    /*strIndexInsert(&sindex,0,"1");
    strIndexInsert(&sindex,1,"2");
    strIndexInsert(&sindex,1,"1.5");
    strIndexInsert(&sindex,2,"1.7");
    strIndexInsert(&sindex,-1,"3");
    strIndexInsert(&sindex,0,"0");
    strIndexInsert(&sindex,5,"2.1");
    strIndexInsert(&sindex,-1,"5");*/

    if(!LoadIndex("voc.txt",&sindex)){
        printf("Error creating index\n");
        return 1;
    }

    for(int k=0;k<sindex.size;k++){
        printf("%d. %s\n",k+1,strIndexGet(&sindex,k));
    }

    while(1){
        fgets(cmd, sizeof(cmd), stdin);
        if(!strcmp("exit",cmd))
            break;
        if(!strcmp("",cmd))
            break;


    }
    FreestrIndex(&sindex);
    printf("Fin.\n");


    return 0;
}
