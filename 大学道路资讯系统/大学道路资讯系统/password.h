
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void password()
{
    int i, count = 0;
    char ZhangHao[9] = "000", zhanghao[9];
    char MiMa[8] = "000", mima[8];

    while(count < 3){
        printf("\t\t\t\t  �ʺţ�");
        scanf("%s", zhanghao);
        printf("\n");
        printf("\t\t\t\t  ���룺");
        scanf("%s", mima);
        count++;
        if(strcmp(MiMa, mima) != 0 || strcmp(ZhangHao, zhanghao) != 0){
	    	if(count == 3){
            	printf("\n\t\t\t\t\t����������ޣ�ϵͳ�ر�\n");
            	exit(-1);
            }
            printf("\n\t\t\t\t\t  �ʺŻ�����������������룡\n\n");
        }
        else {
            getchar();
            printf("\n\t\t\t\t��¼�ɹ�����enter������......\n");
            getchar();
            system("cls");
            break;
        }
    }
}
