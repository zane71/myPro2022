
#include <stdio.h>
#include <stdlib.h>

//���
void xiyou()
{
    char jianjie[1000];
    FILE *fp;
    if((fp = fopen("shancaijianjie.txt", "rt")) == NULL){
        printf("��Ǹ�����ܴ�  �����ļ���\n");
        exit -1;
    }
    while((fgets(jianjie, 1000, fp)) != NULL)
        printf("%s\n\n\n", jianjie);
    fclose(fp);
    printf("\t\t\t\t\t    �����������......");
    getchar();
}


