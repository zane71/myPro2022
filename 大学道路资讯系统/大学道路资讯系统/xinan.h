
#include <stdio.h>
#include <stdlib.h>

//���
void xinan()
{
    char jianjie[1000];
    FILE *fp;
    if((fp = fopen("xinan.txt", "rt")) == NULL){
        printf("��Ǹ�����ܴ򿪼����ļ���\n");
        exit (-1);
    }
    while((fgets(jianjie, 1000, fp)) != NULL)
        printf("%s", jianjie);
    fclose(fp);
    printf("\t\t\t\t\t    �����������......");
    getchar();
    system("cls");
}


