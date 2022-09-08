//校园导航系统
#include "stdio.h"
#include "stdlib.h"
#include "byebye.h"
#include "xinan.h"
#include "denglu.h"
#include "welcom.h"
#include "menu1.h"
#include "menu2.h"
#include "map.h"
#include "password.h"
//#include <unistd.h>
#define Max_num 100
#define INFINITY 32768
//??????????????????????????????????????????????????????????
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

//顶点结构体
typedef struct
{
    int NO;  //地点序号
    char name[50]; //地点名
}Vextype;

//邻接矩阵结构体
typedef struct
{
    int arcs[Max_num + 1][Max_num + 1];  //边集
    Vextype vex[Max_num + 1];   //顶点集
    int vexnum;    //顶点数目
    int arcnum;    //边数目
}AdjMatrix;


//根据地点名确定地点序号
int Locate(AdjMatrix* G, char name[]);
//采用邻接矩阵创建无向网
void Create_AdjMatrix(AdjMatrix* G);
//输出无向网矩阵
void Print_AdjMatrix(AdjMatrix* G);
//深度优先遍历所有景点
void DFSTrave(AdjMatrix G);
void DFS(AdjMatrix G, int i);
//添加新地点
void Add_Place();
//添加新路线
void Add_Route();
//撤销旧路线
void Del_Route();
//撤销旧地点
void Del_Place();
//采用prim算法求最短连通图
void Prim(AdjMatrix* G, int start);
//查询从某个景点出发的最短连通图
void Prim_MiniSpanTree(AdjMatrix* G);
//采用Dijkstra算法求单元点的最短路径
void Dijkstra(AdjMatrix* G, int start, int end, int dist[], int path[][Max_num + 1]);
//查询任意两景点间的最短路径
void Dij_Short_Path();
//查询任意两景点间的所有路径
void All_Path(AdjMatrix* G);
//查询地点信息
void plcae();
//主菜单
void menu(AdjMatrix G);
//menu1菜单的对应功能
void switch1(AdjMatrix G);
//menu2菜单的对应功能
void switch2();
//存储信息
void Store(AdjMatrix* G);
//读取信息
int Read();

void menu(AdjMatrix G)
{
    int choice;
    //system("cls");
    choice = denglu(); //用户输入 0退出  1管理员 2用户
    //管理员登陆
    if (choice == 1) {
        password();    //匹配用户输入的账号、密码 
        menu1();       //管理员菜单界面
        switch1(G);    //管理员功能选择
    }

    //客户登陆
    else if (choice == 2) {
        system("cls");
        menu2();       //用户菜单界面
        switch2();     //用户功能选择
    }
    else if (choice == 0) {
        system("cls");
        byebye();
    }
    else {
        printf("\t\t\t\t\t抱歉，不存在该登陆模式!\n");
        exit(-1);
    }
}
//主程序
int main()
{
    AdjMatrix G;
    Read(&G);
    welcom();
    xinan();
    menu(G);
    
    return 0;
}


//根据地点名确定地点序号
int Locate(AdjMatrix* G, char name[])
{
    
    
    //TODO  更新
    int i;
    for (i = 1; i <= G->vexnum; i++) {
        //图中含有该景点，找到其序号
        if (!strcmp(G->vex[i].name, name))

            return i;
    }

    return -1;
}

//采用邻接矩阵创建无向网
void Create_AdjMatrix(AdjMatrix* G)
{
    int i, j, k, weight;
    char name1[50], name2[50];
    printf("\n\n\n\n\t\t\t********************************    西  南  大  学   ********************************\n\n\n\n");
    printf("\t\t\t创建新地图...\n\n");
    printf("\t\t\t请输入学校中的地点数目和路径数目：");
    scanf("%d %d", &G->vexnum, &G->arcnum);

    //初始化边信息  最多100个边
    for (i = 1; i <= G->vexnum; i++) {
        for (j = 1; j <= G->vexnum; j++) {
            G->arcs[i][j] = INFINITY;
        }
    }
 

    //初始化顶点集合
    for (i = 1; i <= G->vexnum; i++) {
        printf("\t\t\t请输入第%d个地点序号和名字：", i);
        scanf("%d %s", &G->vex[i].NO, G->vex[i].name);
    }
    printf("\n");
    //建立边关系
    for (k = 1; k <= G->arcnum; k++) {
        printf("\t\t\t请输入第%d个相关联的两个地点名字和路径长度：", k);
        scanf("%s %s %d", name1, name2, &weight);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
    }
    printf("\n\t\t\t创建新地图成功！\n\n");
    Store(G);
}

//输出无向网矩阵
/*void Print_AdjMatrix(AdjMatrix *G)
{

    int i, j;
    for(i = 1; i <= G->vexnum; i++)
        printf("%8s", G->vex[i].name);
    printf("\n\n");
    for(i = 1; i <= G->vexnum; i++){
        for(j = 1; j <= G->vexnum; j++){
            if(G->arcs[i][j] == INFINITY)
                printf("       #");
           else
                printf("%8d", G->arcs[i][j]);
        }
        printf("\n");
    }
}
*/
int visited[Max_num + 1];
//深度优先遍历所有景点
//会造成栈溢出  已解决
void DFS(AdjMatrix *G, int i)
{
    printf("%s ", G->vex[i].name);
    visited[i] = 1;
    for (int k = 1; k <= G->vexnum; k++) {
        if (visited[k] == 0 && G->arcs[i][k] < INFINITY)
            DFS(G, k);
    }
}

void DFSTrave(AdjMatrix G)
{
    for (int j = 1; j <= G.vexnum; j++) {
        visited[j] = 0;
    }
    //AdjMatrix Gtemp = G;
 
    for (int j = 1; j <= G.vexnum; j++) {
        if (visited[j] == 0) {
            DFS(&G, j);
        }
    }
}

//添加新地点
void Add_Place(AdjMatrix* G)
{
    char name[50];
    int i, j, m, num;
    printf("\n\n\n\t\t\t\t\t添加新地点...\n");
    printf("\t\t\t\t\t请输入要添加地点的数目：");
    scanf("%d", &num);
    m = G->vexnum;
    G->vexnum += num;

    //初始化新加入的边信息集合
    for (j = 1; j <= num; j++) {
        for (i = 1; i <= G->vexnum; i++) {

            G->arcs[i][m + j] = INFINITY;
            G->arcs[m + j][i] = INFINITY;

        }
    }

    //新加入的顶点信息
    for (i = m + 1; i <= G->vexnum; i++) {
        printf("\t\t\t\t\t请输入第%d个地点序号和名字：", i);
        scanf("%d %s", &G->vex[i].NO, G->vex[i].name);
    }
    Store(G);
    //  Print_AdjMatrix(G);
}

//添加新路线
void Add_Route(AdjMatrix* G)
{

    char name1[50], name2[50];
    char choice = 'y';
    int arcnum = G->arcnum, weight, i, j;

    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t请输入相关联的两个景点名字和路径长度相关联：");
        scanf("%s %s %d", name1, name2, &weight);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = weight;
        G->arcs[j][i] = weight;
        G->arcnum += 1;
        printf("\t\t\t\t\t是否继续添加路线(y || n)：");
        getchar();
        choice = getchar();
    }
    Store(G);
    // Print_AdjMatrix(G);
}

//撤销旧路线
void Del_Route(AdjMatrix* G)
{

    char name1[50], name2[50];
    char choice = 'y';
    int  i, j;

    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t请输入要撤销的两个景点名字:");
        scanf("%s %s", name1, name2);
        i = Locate(G, name1);
        j = Locate(G, name2);
        G->arcs[i][j] = INFINITY;
        G->arcs[j][i] = INFINITY;
        G->arcnum -= 1;
        printf("\t\t\t\t\t是否继续撤销路线(y || n)：");
        getchar();
        choice = getchar();
    }
    Store(G);
    //  Print_AdjMatrix(G);
}

//撤销旧地点
void Del_Place(AdjMatrix* G)
{
    char name[50];
    char choice;
    int  i, j, k;
    printf("\t\t\t\t\t\n\n请输入要撤销的地点名字:");
    scanf("%s", name);
    printf("\t\t\t\t\t是否继续撤销景点：(y || n)：");
    getchar();
    choice = getchar();
    while (choice == 'y' || choice == 'Y') {
        //printf("\t\t\t\t\t\n\n请输入要撤销的地点名字:");
        //scanf("%s", name);
        k = Locate(G, name);
        if (k == -1) {
            printf("没有该地点\n");
            return;
        }

        //printf("%d", k);
        //删除该点 下面点覆盖
        
        //G->vexnum -= 1;
        //边覆盖 
        //if (k == G->vexnum) {
        //    //G->vex[k].name = "false";
        //    G->vex[k].NO = 1000000;
        //}
        for (j = 1; j <= G->vexnum; j++) {
            if (G->arcs[k][j] < INFINITY) {
                G->arcnum -= 1;
                //G->arcs[k][j] = INFINITY;
                //G->arcs[j][k] = INFINITY;
            }
        }
            
        //for (j = 1; j <= G->vexnum; j++) {
        //    if (G->arcs[j][k] < INFINITY) {
        //        G->arcnum -= 1;
        //        //G->arcs[k][j] = INFINITY;
        //        //G->arcs[j][k] = INFINITY;
        //    }
        //}
        for (j = k; j <= G->vexnum; j++) {
            
            G->vex[j] = G->vex[j + 1];
            G->vex[j].NO = j;
        }


        for (i = k; i <= G->vexnum; i++) {
            for (j = 1; j <= G->vexnum; j++) {
                G->arcs[i][j] = G->arcs[i + 1][j];
                //G->arcs[i][j] = INFINITY;
            }
        }
        for (j = k; j <= G->vexnum; j++) {
            for (i = 1; i <= G->vexnum; i++) {
                G->arcs[i][j] = G->arcs[i][j + 1];
            } 
            //G->arcnum -= 1;
        }
        G->vexnum -= 1;
        choice = 'n';
        //       Print_AdjMatrix(G); 
    }
    Store(G);
    //  Print_AdjMatrix(G);
}

//采用prim算法求最短连通图
void Prim(AdjMatrix* G, int start)
{
    struct {
        int adjvex;
        int lowcost;
        int pass;
    }closedge[Max_num + 1];
    int i, e, k, m, min;

    //初始化
    closedge[start].lowcost = 0;
    for (i = 1; i <= G->vexnum; i++) {
        if (i != start) {
            closedge[i].adjvex = start;
            closedge[i].lowcost = G->arcs[start][i];

        }
    }

    //找最小值的边
    for (e = 1; e <= G->vexnum - 1; e++) {

        min = INFINITY;
        for (k = 1; k <= G->vexnum; k++) {
            if (closedge[k].lowcost != 0 && closedge[k].lowcost < min) {
                m = k;
                min = closedge[k].lowcost;
            }
        }
        //防止多余打印
        if (closedge[m].lowcost != 0) {
            printf("\t%s----->%s: 距离为%d\n", G->vex[closedge[m].adjvex].name, G->vex[m].name, closedge[m].lowcost);

        }
        closedge[m].lowcost = 0;

        //加入后，更新closedge数组
        for (i = 1; i <= G->vexnum; i++) {
            if (i != m && G->arcs[m][i] < closedge[i].lowcost) {
                closedge[i].lowcost = G->arcs[m][i];
                closedge[i].adjvex = m;
            }
        }
    }

}

//查询从某个景点出发的最短连通图
void Prim_MiniSpanTree(AdjMatrix* G)
{
    system("cls");
    char name[50], choice = 'y';
    int start;

    printf("\t\t\t\t\t   最佳布网方案...\n\n\n\n");
    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t请输入起点：");
        scanf("%s", name);
        start = Locate(G, name);
        Prim(G, start);
        printf("\t\t\t\t\t是否继续查询(y || n): ");
        getchar();
        choice = getchar();
    }
}

//采用Dijkstra算法求单元点的最短路径
void Dijkstra(AdjMatrix* G, int start, int end, int dist[], int path[][Max_num + 1])
{
    int mindist, i, j, k, t = 1;

    //初始化
    for (i = 1; i <= G->vexnum; i++) {
        dist[i] = G->arcs[start][i];
        //     printf("dst_%d = %d\n",i,dist[i]);
        if (G->arcs[start][i] != INFINITY)
            path[i][1] = start;
    }



    path[start][0] = 1;

    //寻求最短路径
    for (i = 2; i <= G->vexnum; i++) {
        mindist = INFINITY;
        for (j = 1; j <= G->vexnum; j++) {
            if (!path[j][0] && dist[j] < mindist) {
                mindist = dist[j];
                k = j;
            }
        }
        if (mindist == INFINITY)  break;
        path[k][0] = 1;
        //修改加入后的最短路径
        for (j = 1; j <= G->vexnum; j++) {
            if (!path[j][0] && G->arcs[k][j] < INFINITY && G->arcs[k][j] + dist[k] < dist[j]) {
                dist[j] = dist[k] + G->arcs[k][j];

                //记录最短路径
                t = 1;
                while (path[k][t]) {
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
                path[j][t + 1] = 0;
            }
        }
    }
    if (dist[end] == INFINITY) {
        printf("\n\n\t%s----->%s  不存在通路!!!\n", G->vex[start].name, G->vex[end].name);
        return;
    }
    //输出最短路径
    printf("\n\n\t%s----->%s的最短路线：%s ", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    for (j = 2; path[end][j]; j++) {
        printf("——>%s ", G->vex[path[end][j]].name);
    }
    
    printf("——>%s", G->vex[end].name);
    printf("\n\t距离为：%d\n", dist[end]);

}

//查询任意两景点间的最短路径
void Dij_Short_Path(AdjMatrix* G)
{
    system("cls");
    char name[50], choice = 'y';
    int start, end;
    int dist[Max_num + 1];
    printf("\t\t\t\t\t   最短路径...\n\n\n\n");
    while (choice == 'y' || choice == 'Y') {
        int path[Max_num + 1][Max_num + 1] = { 0 };
        printf("\n\t\t\t\t\t请输入起点：");
        scanf("%s", name);
        start = Locate(G, name);
        printf("\t\t\t\t\t请输入终点：");
        scanf("%s", name);
        end = Locate(G, name);
        Dijkstra(G, start, end, dist, path);
        printf("\t\t\t\t\t是否继续查询(y || n)：");
        getchar();
        choice = getchar();
    }
}

//查询任意两景点间的所有路径
int pre[Max_num + 1];  //存放一条路中的各顶点在数组中的下标
boolean pathvisted[Max_num + 1][Max_num + 1];
int flag = 0;



void Path(AdjMatrix* G, int start, int end, int length, int dist)
{
    /*if (length > G->vexnum) {
        return;
    }*/
    if (flag >= Max_num) {
        return;
    }
    int i;
    if (pre[length] == end && length < G->vexnum) {
        printf("%s ", G->vex[pre[1]].name);
        flag++;
        
        for (i = 2; i <= length; i++) {
            printf("——> %s", G->vex[pre[i]].name);
            if (G->arcs[pre[i - 1]][pre[i]] != INFINITY) {
                dist += G->arcs[pre[i - 1]][pre[i]];
            }
        }
        printf("距离为: %d\n", dist);
        dist = 0;
    }
    else {  	// 没有输出完则进入
        i = 1;
        while (i <= G->vexnum) {
            if (!visited[i] && G->arcs[pre[length]][i] < INFINITY) {
                visited[i] = 1;
                pre[length + 1] = i;
                Path(G, i, end, length + 1, dist);
                visited[i] = 0;
            }
            i++;
        }
    }

    
}

void All_Path(AdjMatrix* G)
{
    system("cls");
    flag = 0;
    //boolean false;
    memset(pathvisted, 0, sizeof(pathvisted));
    int i, start, end;
    int flag1 = 0;
    int flag2 = 0;
    char name1[50], name2[50];
    int dist = 0;

    printf("\t\t\t\t\t请输入起点：");
    scanf("%s", name1);
    start = Locate(G, name1);
    //printf("%d",start);
    printf("\t\t\t\t\t请输入终点：");
    scanf("%s", name2);
    end = Locate(G, name2);

    //加个判断 防止死循环
    for (int a = 1; a <= G->vexnum; a++) {
        if (G->arcs[end][a] < INFINITY) {
            flag1 = 1;
            break;
        }
    }
    for (int a = 1; a <= G->vexnum; a++) {
        
        if (G->arcs[start][a] < INFINITY) {
            flag2 = 1;
            break;
        }
    }
    if (flag1 == 0||flag2==0) {
        printf("%s---->%s的所有路径为：\n", G->vex[start].name, G->vex[end].name);
        printf("尚未建立通路\n");
        return;
    }
    for (i = 1; i <= Max_num; i++) {
        visited[i] = 0;
    }
    visited[start] = 1;  // 访问过则标记为1
    pre[1] = start;
    printf("%s---->%s的所有路径为：\n", G->vex[start].name, G->vex[end].name);
    Path(G, start, end, 1, dist);
}


//存储地点及路径信息到message。txt文件中
void Store(AdjMatrix* G)
{
    FILE* fp;
    char* str = NULL;
    if ((fp = fopen("message.txt", "w")) == NULL) {
        printf("\t\t\t\t\t抱歉，无法正常存储!\n");
        return;
    }

    printf("\t\t\t存储信息中...\n");
    //save header
    //sprintf(str,"%d,%d",);
    
    //G->vex[j].NO = 1000000
    fprintf(fp, "%d,%d\n", G->vexnum, G->arcnum);

    //save vex info
    int k;
    for (k = 1; k <= G->vexnum; k++) {
        if (G->vex[k].NO < 1000000) {
            fprintf(fp, "%d %s\n", G->vex[k].NO, G->vex[k].name);
        }
         
    }

    //save arc info
    int i, j;
    for (i = 1; i <= G->vexnum; i++)
        for (j = i; j <= G->vexnum; j++)
        {
            if (G->arcs[i][j] != INFINITY) {
                fprintf(fp, "%s %s %d\n", G->vex[i].name, G->vex[j].name, G->arcs[i][j]);
            }
        }

    fclose(fp);
    printf("\t\t\t\t\t恭喜，存储成功!\n\n");
}



//读取地点及路线信息
//AdjMatrix Read()
int Read(AdjMatrix* G)
{
    FILE* fp;
    char line[1024];
    if ((fp = fopen("message.txt", "r")) == NULL) {
        printf("\t\t\t\t\t抱歉，无法正常读取!\n");
        return 0;
    }
    printf("\t\t\t   读取信息中...\n");


    int position = 0;
    char* p = "";              //定义一个指针
    char* delima = ",";        //第一行分隔符
    
    {
        fgets(line, 1024, fp);  //读取一行

        p = strtok(line, delima);
        G->vexnum = atoi(p); //顶点数
        p = strtok(NULL, delima);
        G->arcnum = atoi(p);//边数
        //printf("%d,%d",G->vexnum,G->arcnum);
        int i, j;
        for (i = 1; i <= G->vexnum; i++)      //边集初始化无穷大
        {
            for (j = 1; j <= G->vexnum; j++)
            {
                G->arcs[i][j] = INFINITY;//边集
                G->arcs[j][i] = INFINITY;
            }
        }

        int k;
        for (k = 0; k < G->vexnum; k++)  //读取地点信息、并写入矩阵
        {
            fgets(line, 1024, fp);
            p = "";
            p = strtok(line, "\n");//除去换行符
            p = strtok(p, " "); //空格为分割符
            G->vex[k + 1].NO = atoi(p);
            p = strtok(NULL, delima);
            strcpy(G->vex[k + 1].name, p);
            //printf("%s",G->vex[k+1].name);
        }

        for (i = 0; i < G->arcnum; i++) //读取边信息、并写入矩阵
        {
            fgets(line, 1024, fp);
            p = "";
            //p = strtok(line, "\n");//除去换行符
            p = strtok(line, " ");
            //printf("%s", p);

            int i = Locate(G, p);
            //printf("%d ", i);
            p = strtok(NULL, " ");
            int j = Locate(G, p);
            //printf("%d", j);
            p = strtok(NULL, " ");
            G->arcs[i][j] = atoi(p);
            G->arcs[j][i] = atoi(p);
            //printf("\n");
        }

    }

    fclose(fp);
    printf("\t\t\t\t\t恭喜,  读取成功!\n\n");

    return 1;
}

//查询地点信息
void plcae(AdjMatrix* G)
{
    system("cls");
    char place[500], name[50], choice = 'y';
    int i;
    FILE* fp;

    printf("\t\t\t\t\t   地点信息查询...\n\n\n\n\n");
    for (i = 1; i <= G->vexnum; i++)
        printf("%s  ", G->vex[i].name);
    printf("\n");
    while (choice == 'y' || choice == 'Y') {
        printf("\t\t\t\t\t请输入需要了解的景点名：");
        scanf("%s", name);
        if ((fp = fopen(name, "rt")) == NULL) {
            printf("\t\t\t\t\t抱歉，文件未正常打开！\n");
            return;
        }
        while ((fgets(place, 500, fp)) != NULL) {
            printf("%s", place);
        }
        fclose(fp);
        getchar();
        printf("\n\n\t\t\t\t\t是否要继续(y || n)：");
        scanf("%c", &choice);
    }
}

//menu1菜单的对应功能
void switch1(AdjMatrix G)
{

    int choice;
    printf("\n\t\t\t\t\t\t请输入您需要的功能：");
    scanf("%d", &choice);
    sleep(1);
    system("cls");
    switch (choice) {
    case 1:Create_AdjMatrix(&G); break;  //管理员手动输入创建新地图
    case 2:Add_Place(&G);   break;  //添加新地点
    case 3:Del_Place(&G);   break;  //撤销旧地点
    case 4:Add_Route(&G);   break;  //添加新路线
    case 5:Del_Route(&G);   break;  //撤销旧路线
    case 6:DFSTrave(G); break;       //深度优先遍历所有景点
    case 0:menu(G);  break;
    default:
        printf("\033[31m\t\t\t\t\t抱歉，输入有误!!!\n");
    }

    if (choice != 0) {
        getchar();
        printf("\t\t\t\t\t按enter键返回......");
        getchar();
        system("cls");
        menu1();
        switch1(G);
    }
}

//menu2菜单的对应功能
void switch2()
{
    
    int choice, k;
    AdjMatrix G;
    //fread(&G, sizeof(AdjMatrix), 1, fp);
    Read(&G);

    printf("\t\t\t\t\t请输入您需要的功能：");
    scanf("%d", &choice);

    switch (choice) {
    case 1: map(); break; //查看校园平面图
    case 2: plcae(&G); break; //地点信息查询
    case 3: Dij_Short_Path(&G); break; //最短路径
    case 4: All_Path(&G); break;       //所有路径
    case 5: Prim_MiniSpanTree(&G); break; //最短连通图
    case 0: menu(G); break;   //退出
    default:
        printf("\t\t\t\t\t\t抱歉，您的输入有误！！！\n");
    }
    if (choice != 0) {
        getchar();
        printf("\n\n\t\t\t\t\t按enter键返回......\n");
        getchar();
        system("cls");
        menu2();
        switch2();
    }
}
