
#include <stdio.h>

int denglu()
{
    int choice;
//    printf("\t\t\ ·········\n");
    printf("\t\t\t\t\t\t   <1>管理员登陆   \n");
    printf("\t\t\t\t\t\t                    \n\n");

    printf("\t\t\t\t\t\t                   \n");
    printf("\t\t\t\t\t\t   <2>用户登陆      \n");
    printf("\t\t\t\t\t\t                    \n\n");

    printf("\t\t\t\t\t\t                   \n");
    printf("\t\t\t\t\t\t   <0>退出程序     \n");
    printf("\t\t\t\t\t\t                    \n\n\n\n");

    printf("\t\t\t\t             请选择您的登陆模式：");
    scanf("%d", &choice);
    
    return choice;
}
