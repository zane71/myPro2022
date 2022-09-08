
#include <stdio.h>
#include <stdlib.h>

//简介
void xiyou()
{
    char jianjie[1000];
    FILE *fp;
    if((fp = fopen("shancaijianjie.txt", "rt")) == NULL){
        printf("抱歉，不能打开  简介的文件！\n");
        exit -1;
    }
    while((fgets(jianjie, 1000, fp)) != NULL)
        printf("%s\n\n\n", jianjie);
    fclose(fp);
    printf("\t\t\t\t\t    按任意键继续......");
    getchar();
}


