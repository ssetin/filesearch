#include "btreeindex.h"

btrIndex sindex;


int main(int argc, char *argv[]){

    char cmd[128];

    if(!btrLoadIndex("voc.txt",&sindex)){
        printf("Error creating index\n");
        return 1;
    }

    while(1){
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1] = '\0';

        if(!strcmp("exit",cmd))
            break;

        if(btrIndexSearch(&sindex,cmd))
            printf("YES\n");
        else
            printf("NO\n");


    }
    btrFreeIndex(&sindex);
    printf("Fin.\n");


    return 0;
}
