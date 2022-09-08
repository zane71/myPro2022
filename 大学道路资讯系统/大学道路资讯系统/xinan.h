
#include <stdio.h>
#include <stdlib.h>

//简介
void xinan()
{
    char jianjie[1000];
    FILE *fp;
    if((fp = fopen("xinan.txt", "rt")) == NULL){
        printf("抱歉，不能打开简介的文件！\n");
        exit (-1);
    }
    while((fgets(jianjie, 1000, fp)) != NULL)
        printf("%s", jianjie);
    fclose(fp);
    printf("\t\t\t\t\t    按任意键继续......");
    getchar();
    system("cls");
}


