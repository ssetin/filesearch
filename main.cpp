#include <stdio.h>
#include <malloc.h>
#include <string.h>

/*
Вы должны написать следующую программу на языке C:
Вашей программе в качестве аргумента будет передано имя файла, в котором будет находиться множество строк (ASCII символы с кодами от 32 до 127).
Далее Ваша программа должна считывать строки из stdin, пока не придет строка "exit".
После каждой считанной строки Ваша программа должна выводить в stdout строку "YES" или "NO" в зависимости от
того, встречается данная строка в переданном файле или нет. Размер файла со словарем не превосходит 128мб.
Напишите как можно более эффективное решение и будьте готовы объяснить, почему Вы выбрали именно это решение.
В качестве ответа пришлите ссылку на репозиторий с вашей программой и makefile'ом. Программа должна
компилироваться GCC 4.7.2.
*/

struct strIndex{
    char **strings{NULL};
    int size{0};
};

void FreestrIndex(strIndex &i){
    for(int k=0;k<i.size;k++)
        free(i.strings[k]);
    free(i.strings);
}

strIndex index;

bool PrepareIndex(const char* filename){
    FILE *file;
    char str[255];
    int words(0),tmplen(0);

    file = fopen(filename,"r");
    if(file == NULL) {
        return false;
     }

    while(fgets(str,sizeof(str),file)) {
        words++;
    }
    printf("File opened.\n%d strings in there\n",words);

    if(!(index.strings = (char **) malloc(words * sizeof(char*) ))){
        printf("Bad malloc for %d strings\n",words);
        free(index.strings);
        return false;
    }

    index.size=words;

    fseek(file,0,SEEK_SET);
    words=0;
    while(fgets(str,sizeof(str),file)) {
        tmplen=strlen(str);
        str[tmplen-1]='\0';
        if(!(index.strings[words]=(char*) malloc(tmplen * sizeof(char) ))){
            printf("Bad malloc for %d chars in string %d\n",tmplen,words);
            FreestrIndex(index);
            return false;
        }
        strcpy(index.strings[words],str);
        words++;
    }
    printf("%d strings loaded\n",words);
    fclose(file);
    return true;
}



int main(int argc, char *argv[]){

    char cmd[128];


    if(!PrepareIndex("voc.txt")){
        printf("Error creating index");
        return 1;
    }

    printf(index.strings[482515]);

    fgets(cmd, sizeof(cmd), stdin);
    FreestrIndex(index);
    printf("Fin.");


    return 0;
}
