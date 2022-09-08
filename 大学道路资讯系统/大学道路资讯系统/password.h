
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void password()
{
    int i, count = 0;
    char ZhangHao[9] = "000", zhanghao[9];
    char MiMa[8] = "000", mima[8];

    while(count < 3){
        printf("\t\t\t\t  帐号：");
        scanf("%s", zhanghao);
        printf("\n");
        printf("\t\t\t\t  密码：");
        scanf("%s", mima);
        count++;
        if(strcmp(MiMa, mima) != 0 || strcmp(ZhangHao, zhanghao) != 0){
	    	if(count == 3){
            	printf("\n\t\t\t\t\t输入次数超限！系统关闭\n");
            	exit(-1);
            }
            printf("\n\t\t\t\t\t  帐号或密码错误，请重新输入！\n\n");
        }
        else {
            getchar();
            printf("\n\t\t\t\t登录成功，按enter键继续......\n");
            getchar();
            system("cls");
            break;
        }
    }
}
